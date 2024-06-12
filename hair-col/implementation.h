#pragma once
#include "objects.h"
#include "relocation.h"

namespace sse
{
	class Biped;
}

using Biped__AttachArmor = sse_ptr<sse::NiAVObject* (*)(sse::Biped*, sse::NiNode*, sse::NiNode*, void*, char, char, void*), 15712, 0x217890>;
using BSShaderProperty__SetMaterial = sse_ptr<void(*)(sse::BSShaderProperty*, sse::BSShaderMaterial*, bool), 105544, 0x147bff0>;

extern Biped__AttachArmor::type Biped__AttachArmor_trampoline;

sse::NiAVObject* Biped__AttachArmor_detour(sse::Biped* this_, sse::NiNode* armor, sse::NiNode* skeleton,
	void* param4, char param5, char param6, void* param7);

static_assert(std::is_same_v<decltype(&Biped__AttachArmor_detour), Biped__AttachArmor::type>);
