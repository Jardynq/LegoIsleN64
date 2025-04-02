#ifndef ISLEPATHACTOR_H
#define ISLEPATHACTOR_H

#include "legogamestate.h"
#include "legopathactor.h"
#include "roi/legoroi.h"

class LegoControlManagerNotificationParam;
class LegoEndAnimNotificationParam;
class LegoWorld;
class LegoPathStructNotificationParam;

class IslePathActor : public LegoPathActor {
public:
	enum { c_LOCATIONS_NUM = 29 };

	enum { c_spawnBit1 = 0x01, c_playMusic = 0x02, c_spawnBit3 = 0x04 };

	struct SpawnLocation {

		SpawnLocation() {}

		SpawnLocation(
			LegoGameState::Area p_area,
			MxAtomId* p_script,
			MxS32 p_entityId,
			const char* p_name,
			MxS16 p_src,
			float p_srcScale,
			MxS16 p_dest,
			float p_destScale,
			MxU32 p_location,
			JukeboxScript::Script p_music
		) {
			m_area = p_area;
			m_script = p_script;
			m_entityId = p_entityId;
			strcpy(m_name, p_name);
			m_src = p_src;
			m_srcScale = p_srcScale;
			m_dest = p_dest;
			m_destScale = p_destScale;
			m_location = p_location;
			m_music = p_music;
		}

		SpawnLocation& operator=(const SpawnLocation& p_location) {
			m_area = p_location.m_area;
			m_script = p_location.m_script;
			m_entityId = p_location.m_entityId;
			strcpy(m_name, p_location.m_name);
			m_src = p_location.m_src;
			m_srcScale = p_location.m_srcScale;
			m_dest = p_location.m_dest;
			m_destScale = p_location.m_destScale;
			m_location = p_location.m_location;
			m_music = p_location.m_music;
			return *this;
		}

		LegoGameState::Area m_area;
		MxAtomId* m_script;
		MxS32 m_entityId;
		char m_name[20];
		MxS16 m_src;
		float m_srcScale;
		MxS16 m_dest;
		float m_destScale;
		MxU32 m_location;
		JukeboxScript::Script m_music;
	};

	IslePathActor();

	virtual MxLong HandleClick() { return 0; }

	virtual MxLong HandleNotification0() { return 0; }

	virtual MxLong HandleControl(LegoControlManagerNotificationParam&) {
		return 0;
	}

	virtual MxLong HandleEndAnim(LegoEndAnimNotificationParam&) { return 0; }

	virtual MxLong HandlePathStruct(LegoPathStructNotificationParam&) {
		return 0;
	}

	virtual void Enter();
	virtual void Exit();
	virtual void
	SpawnPlayer(LegoGameState::Area p_area, MxBool p_enter, MxU8 p_flags);
	virtual void VTable0xec(
		MxMatrix p_transform,
		LegoPathBoundary* p_boundary,
		MxBool p_reset
	);

	~IslePathActor() override { IslePathActor::Destroy(TRUE); }

	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "IslePathActor"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, IslePathActor::ClassName()) ||
			   LegoPathActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void Destroy(MxBool p_fromDestructor) override;

	void FUN_1001b660();

	void SetWorld(LegoWorld* p_world) { m_world = p_world; }

	static void RegisterSpawnLocations();

	// IslePathActor::`scalar deleting destructor'

protected:
	LegoWorld* m_world;
	LegoPathActor* m_previousActor;
	MxFloat m_previousVel;
};

#endif // ISLEPATHACTOR_H
