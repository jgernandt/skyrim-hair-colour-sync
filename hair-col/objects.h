#pragma once
#include <cstddef>
#include <cstdint>

//A lazy minimal definition of the NI types we need

namespace sse
{
struct NiRTTI
{
	const char* name;
	NiRTTI* base;
};
static_assert(sizeof(NiRTTI) == 0x10);

class BSShaderMaterial
{
public:
	enum class Type
	{
		kHairTint = 6,
	};

	virtual ~BSShaderMaterial();

	virtual BSShaderMaterial* create();
	virtual void copyData(BSShaderMaterial* other);
	virtual void BSShaderMaterial_03();
	virtual void BSShaderMaterial_04();
	virtual void BSShaderMaterial_05();
	virtual Type getType();
	virtual void BSShaderMaterial_07();

	std::byte data_08[0x24];
	std::uint32_t hashKey;
	std::byte data_30[8];
};
static_assert(offsetof(BSShaderMaterial, hashKey) == 0x2c);
static_assert(sizeof(BSShaderMaterial) == 0x38);

//This should be an abstract class, not the actual BSLightingShaderMaterial?
class BSLightingShaderMaterial : public BSShaderMaterial
{
public:
	~BSLightingShaderMaterial() override;

	virtual void BSLightingShaderMaterial_08();
	virtual void BSLightingShaderMaterial_09();
	virtual void BSLightingShaderMaterial_0a();
	virtual void BSLightingShaderMaterial_0b();
	virtual void BSLightingShaderMaterial_0c();
	virtual void BSLightingShaderMaterial_0d();

	std::byte data_38[0x68];
};
static_assert(sizeof(BSLightingShaderMaterial) == 0xa0);

class BSLightingShaderMaterialHairTint : public BSLightingShaderMaterial
{
public:
	~BSLightingShaderMaterialHairTint() override;

	struct {
		float red;
		float green;
		float blue;
	} tintColor;

	std::byte pad_ac[4];
};
static_assert(sizeof(BSLightingShaderMaterialHairTint) == 0xb0);


class NiRefObject
{
public:
	virtual ~NiRefObject();

	virtual void NiRefObject_01();

	std::byte data_08[8];
};
static_assert(sizeof(NiRefObject) == 0x10);

class BSTriShape;
class NiNode;
class NiTriShape;

class NiObject : public NiRefObject
{
public:
	~NiObject() override;

	virtual void NiObject_02();
	virtual NiNode* asNiNode();
	virtual void NiObject_04();
	virtual void NiObject_05();
	virtual void NiObject_06();
	virtual void NiObject_07();
	virtual void NiObject_08();
	virtual BSTriShape* asBSTriShape();
	virtual void NiObject_0a();
	virtual void NiObject_0b();
	virtual void NiObject_0c();
	virtual void NiObject_0d();
	virtual void NiObject_0e();
	virtual NiTriShape* asNiTriShape();
	virtual void NiObject_10();
	virtual void NiObject_11();
	virtual void NiObject_12();
	virtual void NiObject_13();
	virtual void NiObject_14();
	virtual void NiObject_15();
	virtual void NiObject_16();
	virtual void NiObject_17();
	virtual void NiObject_18();
	virtual void NiObject_19();
	virtual void NiObject_1a();
	virtual void NiObject_1b();
	virtual void NiObject_1c();
	virtual void NiObject_1d();
	virtual void NiObject_1e();
	virtual void NiObject_1f();
	virtual void NiObject_20();
	virtual void NiObject_21();
	virtual void NiObject_22();
	virtual void NiObject_23();
	virtual void NiObject_24();
};
static_assert(sizeof(NiObject) == 0x10);

class NiObjectNET : public NiObject
{
public:
	~NiObjectNET() override;

	std::byte data_10[0x20];
};
static_assert(sizeof(NiObjectNET) == 0x30);

class NiProperty : public NiObjectNET
{
public:
	enum class Type
	{
		kAlpha = 0,
		kShade = 1
	};

	~NiProperty() override;

	virtual Type getType();
	virtual void NiProperty_26();
};
static_assert(sizeof(NiProperty) == 0x30);

class NiShadeProperty : public NiProperty
{
public:
	~NiShadeProperty() override;

	virtual void NiShadeProperty_27();
	virtual void NiShadeProperty_28();
	virtual void NiShadeProperty_29();
};
static_assert(sizeof(NiShadeProperty) == 0x30);

class BSShaderProperty : public NiShadeProperty
{
public:
	~BSShaderProperty() override;

	virtual void BSShaderProperty_2a();
	virtual void BSShaderProperty_2b();
	virtual void BSShaderProperty_2c();
	virtual void BSShaderProperty_2d();
	virtual void BSShaderProperty_2e();
	virtual void BSShaderProperty_2f();
	virtual void BSShaderProperty_30();
	virtual void BSShaderProperty_31();
	virtual void BSShaderProperty_32();
	virtual void BSShaderProperty_33();
	virtual void BSShaderProperty_34();
	virtual void BSShaderProperty_35();
	virtual void BSShaderProperty_36();
	virtual void BSShaderProperty_37();
	virtual void BSShaderProperty_38();
	virtual void BSShaderProperty_39();
	virtual void BSShaderProperty_3a();
	virtual void BSShaderProperty_3b();
	virtual void BSShaderProperty_3c();
	virtual void BSShaderProperty_3d();
	virtual void BSShaderProperty_3e();

	std::byte data_30[0x48];
	BSShaderMaterial* material;
	std::byte data_80[8];
};
static_assert(offsetof(BSShaderProperty, material) == 0x78);
static_assert(sizeof(BSShaderProperty) == 0x88);

class TESObjectREFR;

class NiAVObject : public NiObjectNET
{
public:
	~NiAVObject() override;

	virtual void NiAVObject_25();
	virtual void NiAVObject_26();
	virtual void NiAVObject_27();
	virtual void NiAVObject_28();
	virtual void NiAVObject_29();
	virtual void NiAVObject_2a();
	virtual void NiAVObject_2b();
	virtual void NiAVObject_2c();
	virtual void NiAVObject_2d();
	virtual void NiAVObject_2e();
	virtual void NiAVObject_2f();
	virtual void NiAVObject_30();
	virtual void NiAVObject_31();
	virtual void NiAVObject_32();
	virtual void NiAVObject_33();
	virtual void NiAVObject_34();

	std::byte data_30[0xc8];
	TESObjectREFR* owner;
	std::byte data_100[0x10];
};
static_assert(offsetof(NiAVObject, owner) == 0xf8);
static_assert(sizeof(NiAVObject) == 0x110);

class NiNode : public NiAVObject
{
public:
	~NiNode() override;

	virtual void NiNode_35();
	virtual void NiNode_36();
	virtual void NiNode_37();
	virtual void NiNode_38();
	virtual void NiNode_39();
	virtual void NiNode_3a();
	virtual void NiNode_3b();
	virtual void NiNode_3c();
	virtual void NiNode_3d();

	std::byte data_110[8];

	struct {
		NiAVObject** data;
		std::uint16_t capacity;
		std::uint16_t size;
		std::uint16_t count;
		std::uint16_t growth;
	} children;
};
static_assert(offsetof(NiNode, children) == 0x118);
static_assert(sizeof(NiNode) == 0x128);

class BSGeometry : public NiAVObject
{
public:
	~BSGeometry() override;

	virtual void BSGeometry_35();
	virtual void BSGeometry_36();
	virtual void BSGeometry_37();

	std::byte data_110[0x18];
	NiProperty* shaderProperty;
	std::byte data_130[0x28];
};
static_assert(offsetof(BSGeometry, shaderProperty) == 0x128);
static_assert(sizeof(BSGeometry) == 0x158);

class BSTriShape : public BSGeometry
{
public:
	~BSTriShape() override;

	std::byte data_158[8];
};
static_assert(sizeof(BSTriShape) == 0x160);

class NiGeometry : public NiAVObject
{
public:
	~NiGeometry() override;

	virtual void NiGeometry_35();
	virtual void NiGeometry_36();
	virtual void NiGeometry_37();
	virtual void NiGeometry_38();
	virtual void NiGeometry_39();
	virtual void NiGeometry_3a();
	virtual void NiGeometry_3b();

	std::byte data_110[8];
	NiProperty* shaderProperty;
	std::byte data_120[0x18];
};
static_assert(offsetof(NiGeometry, shaderProperty) == 0x118);
static_assert(sizeof(NiGeometry) == 0x138);

class NiTriBasedGeometry : public NiGeometry {};
class NiTriShape : public NiTriBasedGeometry {};

}//namespace sse
