#pragma once

#include "mx_core.h"

class LegoEntity;
class LegoROI;
class LegoStorage;
class LegoWorld;
class LegoCacheSound;
class LegoPathBoundary;

struct LegoBuildingInfo {
	enum {
		c_hasVariants = 0x01,
		c_hasSounds = 0x02,
		c_hasMoves = 0x04,
		c_hasMoods = 0x08
	};

	LegoEntity* m_entity;
	const char* m_variant;
	MxU32 m_sound;
	MxU32 m_move;
	MxU8 m_mood;
	MxS8 m_unk0x11;
	MxS8 m_initialUnk0x11;
	MxU8 m_flags;
	float m_unk0x14;
	const char* m_boundaryName;
	float m_x;
	float m_y;
	float m_z;
	LegoPathBoundary* m_boundary;
};

class LegoBuildingManager : public MxCore {
public:
	struct AnimEntry {
		LegoEntity* m_entity;
		LegoROI* m_roi;
		MxLong m_time;
		float m_unk0x0c;
		MxBool m_muted;
	};

	LegoBuildingManager();
	~LegoBuildingManager() override;

	MxResult Tickle() override;

	static const char* ClassName() {
		// not in BETA10

		return "LegoBuildingManager";
	}

	static void configureLegoBuildingManager(MxS32);
	static void SetCustomizeAnimFile(const char* p_value);

	void Init();
	void LoadWorldInfo();
	void CreateBuilding(MxS32 p_index, LegoWorld* p_world);
	void Reset();
	MxResult Write(LegoStorage* p_storage);
	MxResult Read(LegoStorage* p_storage);
	LegoBuildingInfo* GetInfo(LegoEntity* p_entity);
	MxBool SwitchVariant(LegoEntity* p_entity);
	MxBool SwitchSound(LegoEntity* p_entity);
	MxBool SwitchMove(LegoEntity* p_entity);
	MxBool SwitchMood(LegoEntity* p_entity);
	MxU32 GetAnimationId(LegoEntity* p_entity);
	MxU32 GetSoundId(LegoEntity* p_entity, MxBool p_state);
	MxBool FUN_10030000(LegoEntity* p_entity);
	MxBool FUN_10030030(MxS32 p_index);
	MxBool FUN_10030110(LegoBuildingInfo* p_data);
	void ScheduleAnimation(
		LegoEntity* p_entity,
		MxLong p_length,
		MxBool p_haveSound,
		MxBool p_unk0x28
	);
	void Reset();
	void AdjustHeight(MxS32 p_index);
	MxResult FUN_10030630();
	LegoBuildingInfo* GetInfoArray(MxS32& p_length);
	void FUN_100307b0(LegoEntity* p_entity, MxS32 p_adjust);
	void FUN_10030800();

	static const char* GetCustomizeAnimFile() { return g_customizeAnimFile; }

	// LegoBuildingManager::`scalar deleting destructor'

private:
	static char* g_customizeAnimFile;
	static MxS32 g_maxMove[16];
	static MxU32 g_maxSound;

	MxU8 m_nextVariant;
	MxBool m_unk0x09;
	AnimEntry* m_entries[5];
	MxS8 m_numEntries;
	LegoCacheSound* m_sound;
	MxBool m_unk0x28;
	LegoWorld* m_world;
};

