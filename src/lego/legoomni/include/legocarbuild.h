#ifndef LEGOCARBUILD_H
#define LEGOCARBUILD_H

#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"
#include "mxgeometry/mxquaternion.h"

class LegoCarBuildAnimPresenter;
class LegoControlManagerNotificationParam;
class LegoEventNotificationParam;
class MxControlPresenter;
class MxStillPresenter;
class MxSoundPresenter;
class MxActionNotificationParam;

class LegoVehicleBuildState : public LegoState {
public:
	enum AnimationState {
		e_unknown0 = 0,
		e_entering = 1,
		e_unknown2 = 2,
		e_cutscene = 3,
		e_unknown4 = 4,
		e_exiting = 6
	};

	LegoVehicleBuildState(const char* p_classType);

	const char* ClassName() const override { return m_className.GetData(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, m_className.GetData()) || LegoState::IsA(p_name);
	}

	MxResult Serialize(LegoStorage* p_storage) override;

	// LegoVehicleBuildState::`scalar deleting destructor'

	Playlist m_unk0x08[4];
	// This can be one of the following:
	// * LegoRaceCarBuildState
	// * LegoCopterBuildState
	// * LegoDuneCarBuildState
	// * LegoJetskiBuildState
	MxString m_className;
	AnimationState m_animationState;
	MxU8 m_unk0x4c;
	MxBool m_unk0x4d;
	MxBool m_unk0x4e;
	MxU8 m_placedPartCount;
};

typedef LegoVehicleBuildState LegoRaceCarBuildState;
typedef LegoVehicleBuildState LegoCopterBuildState;
typedef LegoVehicleBuildState LegoDuneCarBuildState;
typedef LegoVehicleBuildState LegoJetskiBuildState;

class LegoCarBuild : public LegoWorld {
public:
	struct LookupTableActions {
		undefined4 m_unk0x00;
		undefined4 m_unk0x04;
		undefined4 m_unk0x08;
		undefined4 m_unk0x0c;
		undefined4 m_unk0x10;
		undefined4 m_unk0x14;
		undefined4 m_unk0x18;
	};

	enum Unknown0xf8 { c_unknownminusone = -1, c_unknown8 = 8 };

	LegoCarBuild();
	~LegoCarBuild() override;

	MxBool VTable0x5c() override { return TRUE; }

	const char* ClassName() const override { return "LegoCarBuild"; }

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoCarBuild::ClassName()) ||
			   LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;
	virtual void VTable0x6c();
	virtual void VTable0x70();
	virtual void VTable0x74(MxFloat p_param1[2], MxFloat p_param2[3]);
	virtual void VTable0x78(MxFloat p_param1[2], MxFloat p_param2[3]);
	virtual void VTable0x7c(MxFloat p_param1[2], MxFloat p_param2[3]);
	virtual void VTable0x80(
		MxFloat p_param1[2],
		MxFloat p_param2[2],
		MxFloat p_param3,
		MxFloat p_param4[2]
	);

	MxS16 GetPlacedPartCount();
	void SetPlacedPartCount(MxU8 p_placedPartCount);
	void InitPresenters();
	void FUN_10022f00();
	void FUN_10022f30();
	void FUN_10023130(MxLong p_x, MxLong p_y);
	void FUN_100236d0();
	undefined4 FUN_10024250(LegoEventNotificationParam* p_param);
	void FUN_100243a0();
	undefined4 FUN_10024480(MxActionNotificationParam* p_param);
	undefined4 FUN_100244e0(MxLong p_x, MxLong p_y);
	undefined4 FUN_100246e0(MxLong p_x, MxLong p_y);
	MxS32 FUN_10024850(MxLong p_x, MxLong p_y);
	undefined4 FUN_10024890(MxParam* p_param);
	undefined4 FUN_10024c20(LegoEventNotificationParam* p_param);
	void FUN_10024ef0();
	void FUN_10024f30();
	void FUN_10024f50();
	void FUN_10024f70(MxBool p_enabled);
	void SetPresentersEnabled(MxBool p_enabled);
	void TogglePresentersEnabled();
	void FUN_100250e0(MxBool p_param);
	void FUN_10025350(MxS32 p_objectId);
	void FUN_10025450();
	void FUN_10025720(undefined4 p_param1);
	void FUN_10025d10(MxS32 p_param);
	MxS32 FUN_10025d70();
	void FUN_10025db0(const char* p_param1, undefined4 p_param2);
	void FUN_10025e40();
	MxS32 FUN_10025ee0(undefined4 p_param1);

	void SetUnknown0x258(LegoCarBuildAnimPresenter* p_unk0x258) {
		m_unk0x258 = p_unk0x258;
	}

	// LegoCarBuild::`scalar deleting destructor'

private:
	// inline functions
	MxU32 Beta0x10070520();
	void StopActionIn0x344();

	Unknown0xf8 m_unk0xf8;
	MxS16 m_unk0xfc;
	MxS32 m_unk0x100;
	undefined4 m_unk0x104;
	// name verified by BETA10 0x1006ebba
	MxS8 m_numAnimsRun;
	MxU8 m_unk0x109;
	MxU16 m_unk0x10a;
	DWORD m_unk0x10c;
	LegoROI* m_unk0x110;
	BoundingSphere m_unk0x114;
	MxMatrix m_unk0x12c;
	undefined m_unk0x174;
	MxMatrix m_unk0x178;
	MxMatrix m_unk0x1c0;
	MxMatrix m_unk0x208;
	// This is likely a location in pixel space
	MxS32 m_unk0x250[2];
	LegoCarBuildAnimPresenter* m_unk0x258;
	MxQuaternionTransformer m_unk0x25c;
	// These two are likely locations in pixel space
	MxS32 m_unk0x290[2];
	MxS32 m_unk0x298[2];
	MxFloat m_unk0x2a0;
	Mx4DPointFloat m_unk0x2a4;
	Mx4DPointFloat m_unk0x2bc;
	MxBool m_unk0x2d4;
	// variable names verified by BETA10 0x1006b27a
	MxStillPresenter* m_ColorBook_Bitmap;
	MxControlPresenter* m_Yellow_Ctl;
	MxControlPresenter* m_Red_Ctl;
	MxControlPresenter* m_Blue_Ctl;
	MxControlPresenter* m_Green_Ctl;
	MxControlPresenter* m_Gray_Ctl;
	MxControlPresenter* m_Black_Ctl;
	MxSoundPresenter* m_Shelf_Sound;
	MxSoundPresenter* m_PlaceBrick_Sound;
	MxSoundPresenter* m_GetBrick_Sound;
	MxSoundPresenter* m_Paint_Sound;
	MxSoundPresenter* m_Decal_Sound;
	MxStillPresenter* m_Decal_Bitmap;
	MxControlPresenter* m_Decals_Ctl;
	MxControlPresenter* m_Decals_Ctl1;
	MxControlPresenter* m_Decals_Ctl2;
	MxControlPresenter* m_Decals_Ctl3;
	MxControlPresenter* m_Decals_Ctl4;
	MxControlPresenter* m_Decals_Ctl5;
	MxControlPresenter* m_Decals_Ctl6;
	MxControlPresenter* m_Decals_Ctl7;
	// variable name verified by BETA10 0x1006b219
	LegoVehicleBuildState* m_buildState;
	// variable name verified by BETA10 0x1006d742
	undefined4 m_carId;
	// variable name verified by BETA10 0x1006cba7
	LegoGameState::Area m_destLocation;
	MxPresenter* m_unk0x338;
	MxControlPresenter* m_unk0x33c;
	undefined4 m_unk0x340;
	undefined4 m_unk0x344;
	MxU8 m_presentersEnabled;
	static MxS16 g_unk0x100f11cc;
	static MxFloat g_unk0x100d65a4;
	static MxFloat g_rotationAngleStepYAxis;
	static LookupTableActions g_unk0x100d65b0[];
};

#endif // LEGOCARBUILD_H
