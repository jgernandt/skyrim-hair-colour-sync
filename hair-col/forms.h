#pragma once
#include <cstddef>
#include <cstdint>

//A lazy minimal definition of the TES types we need

namespace sse
{
class BaseFormComponent
{
public:
	virtual ~BaseFormComponent();

	virtual void BaseFormComponent_01();
	virtual void BaseFormComponent_02();
	virtual void BaseFormComponent_03();
};
static_assert(sizeof(BaseFormComponent) == 8);

class TESForm : public BaseFormComponent
{
public:
	enum FormType
	{
		kFormType_NPC = 43,
		kFormType_Character = 62,
	};

	~TESForm() override;

	virtual void TESForm_01();
	virtual void TESForm_02();
	virtual void TESForm_03();
	virtual void TESForm_04();
	virtual void TESForm_05();
	virtual void TESForm_06();
	virtual void TESForm_07();
	virtual void TESForm_08();
	virtual void TESForm_09();
	virtual void TESForm_0a();
	virtual void TESForm_0b();
	virtual void TESForm_0c();
	virtual void TESForm_0d();
	virtual void TESForm_0e();
	virtual void TESForm_0f();
	virtual void TESForm_10();
	virtual void TESForm_11();
	virtual void TESForm_12();
	virtual void TESForm_13();
	virtual void TESForm_14();
	virtual void TESForm_15();
	virtual void TESForm_16();
	virtual void TESForm_17();
	virtual void TESForm_18();
	virtual void TESForm_19();
	virtual void TESForm_1a();
	virtual void TESForm_1b();
	virtual void TESForm_1c();
	virtual void TESForm_1d();
	virtual void TESForm_1e();
	virtual void TESForm_1f();
	virtual void TESForm_20();
	virtual void TESForm_21();
	virtual void TESForm_22();
	virtual void TESForm_23();
	virtual void TESForm_24();
	virtual void TESForm_25();
	virtual void TESForm_26();
	virtual void TESForm_27();
	virtual void TESForm_28();
	virtual void TESForm_29();
	virtual void TESForm_2a();
	virtual void TESForm_2b();
	virtual void TESForm_2c();
	virtual void TESForm_2d();
	virtual void TESForm_2e();
	virtual void TESForm_2f();
	virtual void TESForm_30();
	virtual void TESForm_31();
	virtual void TESForm_32();
	virtual void TESForm_33();
	virtual void TESForm_34();
	virtual void TESForm_35();
	virtual void TESForm_36();
	virtual void TESForm_37();
	virtual void TESForm_38();
	virtual void TESForm_39();
	virtual void TESForm_3a();

	std::byte data_08[0x12];
	std::uint8_t type;
	std::byte data_1b[5];
};
static_assert(offsetof(TESForm, type) == 0x1a);
static_assert(sizeof(TESForm) == 0x20);

class BGSColorForm : public TESForm
{
public:
	~BGSColorForm() override;

	std::byte data_20[0x10];

	struct {
		std::uint8_t red;
		std::uint8_t green;
		std::uint8_t blue;
		std::uint8_t alpha;
	} color;

	std::byte data_34[4];
};
static_assert(sizeof(BGSColorForm) == 0x38);

class TESObject : public TESForm
{
public:
	~TESObject() override;

	virtual void TESObject_3b();
	virtual void TESObject_3c();
	virtual void TESObject_3d();
	virtual void TESObject_3e();
	virtual void TESObject_3f();
	virtual void TESObject_40();
	virtual void TESObject_41();
	virtual void TESObject_42();
	virtual void TESObject_43();
	virtual void TESObject_44();
	virtual void TESObject_45();
	virtual void TESObject_46();
	virtual void TESObject_47();
};
static_assert(sizeof(TESObject) == 0x20);

class TESBoundObject : public TESObject
{
public:
	~TESBoundObject() override;

	virtual void TESBoundObject_48();
	virtual void TESBoundObject_49();
	virtual void TESBoundObject_4a();
	virtual void TESBoundObject_4b();
	virtual void TESBoundObject_4c();
	virtual void TESBoundObject_4d();
	virtual void TESBoundObject_4e();
	virtual void TESBoundObject_4f();
	virtual void TESBoundObject_50();
	virtual void TESBoundObject_51();
	virtual void TESBoundObject_52();

	std::byte data_20[0x10];
};
static_assert(sizeof(TESBoundObject) == 0x30);

class TESBoundAnimObject : public TESBoundObject
{
public:
	~TESBoundAnimObject() override;
};
static_assert(sizeof(TESBoundAnimObject) == 0x30);

class TESActorBaseData : public BaseFormComponent
{
public:
	enum Flags
	{
		kFlag_Female = 1
	};

	~TESActorBaseData() override;

	virtual void TESActorBaseData_04();
	virtual void TESActorBaseData_05();
	virtual void TESActorBaseData_06();
	virtual void TESActorBaseData_07();
	virtual void TESActorBaseData_08();

	std::uint32_t flags;
	std::byte data_0c[0x4c];
};
static_assert(offsetof(TESActorBaseData, flags) == 8);
static_assert(sizeof(TESActorBaseData) == 0x58);

class TESActorBase : public TESBoundAnimObject, public TESActorBaseData
{
public:
	~TESActorBase() override;

	virtual void TESActorBase_53();
	virtual void TESActorBase_54();
	virtual void TESActorBase_55();
	virtual void TESActorBase_56();

	std::byte base_30[0xc8];
};
static_assert(sizeof(TESActorBase) == 0x150);

class TESRace : public TESForm
{
public:
	struct CharGenData
	{
		std::byte data_00[0xb8];
		BGSColorForm* defaultColor;
		std::byte data_c0[8];
	};

	~TESRace() override;

	std::byte data_20[0x488];
	CharGenData* chargenData[2];
};
static_assert(offsetof(TESRace, chargenData) == 0x4a8);
static_assert(sizeof(TESRace::CharGenData) == 0xc8);
static_assert(sizeof(TESRace) == 0x4B8);

class TESRaceForm : public BaseFormComponent
{
public:
	~TESRaceForm() override;

	TESRace* race;
};
static_assert(sizeof(TESRaceForm) == 0x10);

class TESNPC : public TESActorBase, public TESRaceForm
{
public:
	~TESNPC() override;

	struct HeadData {
		BGSColorForm* hairColor;
		std::byte data_08[8];
	};

	std::byte data_160[0x68];
	HeadData* headData;
	std::byte data_1d0[0x20];
	TESNPC* templateActor;
	std::byte data_1f8[0x70];
};
static_assert(offsetof(TESNPC, headData) == 0x1c8);
static_assert(offsetof(TESNPC, templateActor) == 0x1f0);
static_assert(sizeof(TESNPC) == 0x268);

class TESObjectREFR final : public TESForm
{
public:
	~TESObjectREFR() override;

	//+loads of virtuals, I can't be bothered... we're not using them anyway, or deriving from this class

	std::byte data_20[0x20];
	TESBoundObject* baseForm;
	std::byte data_48[0x58];
};
static_assert(offsetof(TESObjectREFR, baseForm) == 0x40);
static_assert(sizeof(TESObjectREFR) == 0xa0);

}//namespace sse
