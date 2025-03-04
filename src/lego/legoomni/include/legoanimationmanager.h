#ifndef LEGOANIMATIONMANAGER_H
#define LEGOANIMATIONMANAGER_H

#include "legolocations.h"
#include "legomain.h"
#include "legostate.h"
#include "legotraninfolist.h"
#include "mxcore.h"
#include "mxgeometry/mxquaternion.h"

class LegoAnimPresenter;
class LegoEntity;
class LegoExtraActor;
class LegoFile;
class LegoPathActor;
class LegoPathBoundary;
class LegoROIList;
struct LegoUnknown100db7f4;
class LegoWorld;
class MxDSAction;

struct ModelInfo {
	char* m_name;
	MxU8 m_unk0x04;
	float m_location[3];
	float m_direction[3];
	float m_up[3];
	MxU8 m_unk0x2c;
};

struct AnimInfo {
	char* m_name;
	MxU32 m_objectId;
	MxS16 m_location;
	MxBool m_unk0x0a;
	MxU8 m_unk0x0b;
	MxU8 m_unk0x0c;
	MxU8 m_unk0x0d;
	float m_unk0x10[4];
	MxU8 m_modelCount;
	MxU16 m_unk0x22;
	ModelInfo* m_models;
	MxS8 m_unk0x28;
	MxBool m_unk0x29;
	MxS8 m_unk0x2a[3];
};

class AnimState : public LegoState {
public:
	AnimState();
	~AnimState() override;

	const char* ClassName() const override { return "AnimState"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, AnimState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxBool Reset() override;
	MxResult Serialize(LegoStorage* p_storage) override;

	void CopyToAnims(MxU32, AnimInfo* p_anims, MxU32& p_outExtraCharacterId);
	void InitFromAnims(
		MxU32 p_animsLength,
		AnimInfo* p_anims,
		MxU32 p_extraCharacterId
	);

	// AnimState::`scalar deleting destructor'

private:
	MxU32 m_extraCharacterId;
	// appears to store the length of m_unk0x10
	MxU32 m_unk0x0c; // dynamically sized array of MxU16, corresponding to
					 // AnimInfo::m_unk0x22
	MxU16* m_unk0x10;
	MxU32 m_locationsFlagsLength; // dynamically sized array of bools,
								  // corresponding to LegoLocation.m_unk0x5c
	MxBool* m_locationsFlags;
};

class LegoAnimationManager : public MxCore {
public:
	struct Character {
		const char* m_name;
		MxBool m_inExtras;
		MxS8 m_vehicleId;
		undefined m_unk0x06;
		MxBool m_unk0x07;
		MxBool m_unk0x08;
		MxBool m_unk0x09;
		MxS32 m_unk0x0c;
		MxS32 m_unk0x10;
		MxBool m_active;
		MxU8 m_unk0x15;
		MxS8 m_unk0x16;
	};

	struct Vehicle {
		const char* m_name;
		MxBool m_unk0x04;
		MxBool m_unk0x05;
	};

	struct Extra {
		LegoROI* m_roi;
		MxS32 m_characterId;
		MxLong m_unk0x08;
		MxBool m_unk0x0c;
		MxBool m_unk0x0d;
		float m_speed;
		MxBool m_unk0x14;
	};

	enum PlayMode { e_unk0 = 0, e_unk1, e_unk2 };

	LegoAnimationManager();
	~LegoAnimationManager() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	const char* ClassName() const override { return "LegoAnimationManager"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, ClassName()) || MxCore::IsA(p_name);
	}

	void Reset(MxBool p_und);
	void Suspend();
	void Resume();
	void FUN_1005f6d0(MxBool p_unk0x400);
	void EnableCamAnims(MxBool p_enableCamAnims);
	MxResult LoadWorldInfo(LegoOmni::World p_worldId);
	MxBool FindVehicle(const char* p_name, MxU32& p_index);
	MxResult ReadAnimInfo(LegoStorage* p_storage, AnimInfo* p_info);
	MxResult ReadModelInfo(LegoStorage* p_storage, ModelInfo* p_info);
	void
	FUN_10060480(const LegoChar* p_characterNames[], MxU32 p_numCharacterNames);
	void FUN_100604d0(MxBool p_unk0x08);
	void FUN_100604f0(MxS32 p_objectIds[], MxU32 p_numObjectIds);
	void FUN_10060540(MxBool p_unk0x29);
	void FUN_10060570(MxBool p_unk0x1a);
	MxResult StartEntityAction(MxDSAction& p_dsAction, LegoEntity* p_entity);
	MxResult FUN_10060dc0(
		MxU32 p_objectId,
		MxMatrix* p_matrix,
		MxBool p_param3,
		MxU8 p_param4,
		LegoROI* p_roi,
		MxBool p_param6,
		MxBool p_param7,
		MxBool p_param8,
		MxBool p_param9
	);
	void CameraTriggerFire(
		LegoPathActor* p_actor,
		MxBool,
		MxU32 p_location,
		MxBool p_bool
	);
	void FUN_10061010(MxBool p_und);
	LegoTranInfo* GetTranInfo(MxU32 p_index);
	void FUN_10062770();
	void PurgeExtra(MxBool p_und);
	void AddExtra(MxS32 p_location, MxBool p_und);
	void FUN_10063270(LegoROIList* p_list, LegoAnimPresenter* p_presenter);
	void FUN_10063780(LegoROIList* p_list);
	MxResult FUN_10064670(Vector3* p_position);
	MxResult FUN_10064740(Vector3* p_position);
	MxResult FUN_10064880(const char* p_name, MxS32 p_unk0x0c, MxS32 p_unk0x10);
	MxBool FUN_10064ee0(MxU32 p_objectId);

	static void configureLegoAnimationManager(MxS32 p_legoAnimationManagerConfig
	);

	// LegoAnimationManager::`scalar deleting destructor'

private:
	void Init();
	MxResult FUN_100605e0(
		MxU32 p_index,
		MxBool p_unk0x0a,
		MxMatrix* p_matrix,
		MxBool p_bool1,
		LegoROI* p_roi,
		MxBool p_bool2,
		MxBool p_bool3,
		MxBool p_bool4,
		MxBool p_bool5
	);
	MxResult FUN_100609f0(
		MxU32 p_objectId,
		MxMatrix* p_matrix,
		MxBool p_und1,
		MxBool p_und2
	);
	void DeleteAnimations();
	void FUN_10061530();
	MxResult FUN_100617c0(MxS32 p_unk0x08, MxU16& p_unk0x0e, MxU16& p_unk0x10);
	MxU16 FUN_10062110(
		LegoROI* p_roi,
		Vector3& p_direction,
		Vector3& p_position,
		LegoPathBoundary* p_boundary,
		float p_speed,
		MxU8 p_unk0x0c,
		MxBool p_unk0x14
	);
	MxS8 GetCharacterIndex(const char* p_name);
	MxBool FUN_100623a0(AnimInfo& p_info);
	MxBool ModelExists(AnimInfo& p_info, const char* p_name);
	void FUN_10062580(AnimInfo& p_info);
	MxBool FUN_10062650(Vector3& p_position, float p_und, LegoROI* p_roi);
	MxBool FUN_10062710(AnimInfo& p_info);
	MxBool FUN_10062e20(LegoROI* p_roi, LegoAnimPresenter* p_presenter);
	void FUN_10063950(LegoROI* p_roi);
	void FUN_10063aa0();
	MxBool FUN_10063b90(
		LegoWorld* p_world,
		LegoExtraActor* p_actor,
		MxU8 p_mood,
		MxU32 p_characterId
	);
	void FUN_10063d10();
	void FUN_10063e40(LegoAnimPresenter* p_presenter);
	MxBool FUN_10063fb0(LegoLocation::Boundary* p_boundary, LegoWorld* p_world);
	MxBool FUN_10064010(
		LegoPathBoundary* p_boundary,
		LegoUnknown100db7f4* p_edge,
		float p_destScale
	);
	MxBool FUN_10064120(
		LegoLocation::Boundary* p_boundary,
		MxBool p_bool1,
		MxBool p_bool2
	);
	MxResult FUN_10064380(
		const char* p_name,
		const char* p_boundaryName,
		MxS32 p_src,
		float p_srcScale,
		MxS32 p_dest,
		float p_destScale,
		MxU32 p_undIdx1,
		MxS32 p_unk0x0c,
		MxU32 p_undIdx2,
		MxS32 p_unk0x10,
		float p_speed
	);
	void FUN_100648f0(LegoTranInfo* p_tranInfo, MxLong p_unk0x404);
	void FUN_10064b50(MxLong p_time);

	LegoOmni::World m_worldId;
	MxU16 m_animCount;
	MxU16 m_unk0x0e;
	MxU16 m_unk0x10;
	AnimInfo* m_anims;
	undefined2 m_unk0x18;
	MxBool m_unk0x1a;
	MxU32 m_unk0x1c;
	LegoTranInfoList* m_tranInfoList;
	LegoTranInfoList* m_tranInfoList2;
	MxPresenter* m_unk0x28[2];
	MxLong m_unk0x30[2];
	MxBool m_unk0x38;
	MxBool m_animRunning;
	MxBool m_enableCamAnims;
	Extra m_extras[40];
	MxU32 m_lastExtraCharacterId;
	MxBool m_unk0x400;
	MxBool m_unk0x401;
	MxBool m_unk0x402;
	MxLong m_unk0x404;
	MxLong m_unk0x408;
	MxLong m_unk0x40c;
	MxLong m_unk0x410;
	MxU32 m_unk0x414;
	MxU32 m_numAllowedExtras;
	undefined4 m_unk0x41c;
	AnimState* m_animState;
	LegoROIList* m_unk0x424;
	MxBool m_suspendedEnableCamAnims;
	MxBool m_unk0x429;
	MxBool m_unk0x42a;
	MxBool m_suspended;
	LegoTranInfo* m_unk0x42c;
	MxBool m_unk0x430;
	MxLong m_unk0x434;
	MxLong m_unk0x438;
	MxMatrix m_unk0x43c;
	MxMatrix m_unk0x484;
	MxQuaternionTransformer m_unk0x4cc;
};

// MxListCursor<LegoTranInfo *>::MxListCursor<LegoTranInfo *>

#endif // LEGOANIMATIONMANAGER_H
