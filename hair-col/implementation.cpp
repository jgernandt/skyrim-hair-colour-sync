#include "pch.h"
#include "implementation.h"

#include <cassert>

#include "objects.h"
#include "forms.h"
#include "relocation.h"

Biped__AttachArmor::type Biped__AttachArmor_trampoline = nullptr;

static void appendHairShader(sse::NiProperty* prop, std::vector<sse::BSShaderProperty*>& shaders)
{
	if (prop && prop->getType() == sse::NiProperty::Type::kShade) {

		auto shader = static_cast<sse::BSShaderProperty*>(prop);

		if (shader->material && shader->material->getType() == sse::BSShaderMaterial::Type::kHairTint) {
			shaders.push_back(shader);
		}
	}
}

static void findHairShaders(sse::NiAVObject* av, std::vector<sse::BSShaderProperty*>& shaders)
{
	assert(av);

	if (sse::BSTriShape* shape = av->asBSTriShape()) {
		appendHairShader(shape->shaderProperty, shaders);
	}
	else if (sse::NiTriShape* shape = av->asNiTriShape()) {
		appendHairShader(shape->shaderProperty, shaders);
	}
	else if (sse::NiNode* node = av->asNiNode()) {
		for (int i = 0; i < node->children.size; i++) {
			if (node->children.data[i])
				findHairShaders(node->children.data[i], shaders);
		}
	}
}

static sse::BGSColorForm* getHairColor(sse::TESNPC* base)
{
	assert(base);

	sse::BGSColorForm* result = nullptr;

	//Check in this record first
	if (base->headData && base->headData->hairColor) {
		result = base->headData->hairColor;
	}
	//If no hair col, check template(s)
	else if (base->templateActor) {
		result = getHairColor(base->templateActor);
	}
	//If still no hair col, use race default
	else if (base->race) {
		int gender = base->flags & sse::TESNPC::kFlag_Female ? 1 : 0;
		if (base->race->chargenData[gender]) {
			result = base->race->chargenData[gender]->defaultColor;
		}
	}

	return result;
}

static void attach(sse::NiNode* root, sse::TESNPC* npc)
{
	//This will look at every HairTint material under root and,
	//if its tint color does not match the colour of npc's hair,
	//replace it with a new material.

	if (sse::BGSColorForm* hairColor = getHairColor(npc)) {

		std::vector<sse::BSShaderProperty*> shaders;
		findHairShaders(root, shaders);

		for (auto&& shader : shaders) {

			//shaders should only contain HairTint materials at this point
			assert(shader->material && shader->material->getType() == sse::BSShaderMaterial::Type::kHairTint);
			auto oldMaterial = static_cast<sse::BSLightingShaderMaterialHairTint*>(shader->material);

			//I don't see exactly why this works (dividing by 128 instead of 255),
			//but it definitely does give us the right colour in game.
			if (oldMaterial->tintColor.red != hairColor->color.red / 128.0f ||
				oldMaterial->tintColor.green != hairColor->color.green / 128.0f ||
				oldMaterial->tintColor.blue != hairColor->color.blue / 128.0f)
			{
				auto newMaterial = static_cast<sse::BSLightingShaderMaterialHairTint*>(shader->material->create());
				if (newMaterial) {
					newMaterial->copyData(shader->material);

					newMaterial->tintColor.red = hairColor->color.red / 128.0f;
					newMaterial->tintColor.green = hairColor->color.green / 128.0f;
					newMaterial->tintColor.blue = hairColor->color.blue / 128.0f;

					//If newMaterial is not yet hashed (key == -1), BSShaderProperty::SetMaterial will 
					//compute the key, search the database for a match and use that material.
					//If no match is found, it will duplicate newMaterial, 
					//add the duplicate to the database and assign it to the shader.
					//The only way the shader ends up actually using newMaterial is if
					// a) newMaterial is hashed (key != -1) AND
					// b) param3 == false.
					//(param3 seems to indicate a material that might change over time)

					//The hash key is inited to -1 and not copied
					assert(newMaterial->hashKey == -1);

					//So this will actually assign a duplicate of newMaterial to the shader,
					//which may or may not have existed in the database prior to the call.
					BSShaderProperty__SetMaterial::invoke(shader, newMaterial, false);

					//Thus, newMaterial will be unused at this point and must be cleaned up by us.
					//(note: the virtual dtor calls the Skyrim memory manager as appropriate)
					assert(shader->material != newMaterial);
					delete newMaterial;

					//The duplicate material assigned to the shader is managed by the resource handler 
					//and will be cleaned up by them when appropriate.
				}
			}
		}
	}
}

sse::NiAVObject* Biped__AttachArmor_detour(sse::Biped* this_, sse::NiNode* armor, sse::NiNode* skeleton,
	void* param4, char param5, char param6, void* param7)
{
	if (armor && skeleton && skeleton->owner && skeleton->owner->baseForm
		&& skeleton->owner->baseForm->type == sse::TESForm::kFormType_NPC) {
		attach(armor, static_cast<sse::TESNPC*>(skeleton->owner->baseForm));
	}

	return Biped__AttachArmor_trampoline(this_, armor, skeleton, param4, param5, param6, param7);
}
