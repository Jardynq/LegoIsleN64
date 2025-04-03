#pragma once

#include "gamestate.h"
#include "race_actor.h"
#include "race_map.h"
#include "state.h"
#include "world.h"
#include "mx_rect32.h"

class Act1State;
class LegoEventNotificationParam;
class LegoPathActor;
class MxEndActionNotificationParam;
class MxNotificationParam;
class LegoPathStructNotificationParam;

class RaceState : public LegoState {
public:
	struct Entry {
	public:
		Entry() {
			m_id = 0;
			m_unk0x02 = 0;
			m_score = 0;
		}

		MxS16 GetUnknown0x02() { return m_unk0x02; }

		MxS16 GetHighScore() { return m_score; }

		MxResult Serialize(LegoStorage* p_storage) {
			if (p_storage->IsReadMode()) {
				p_storage->ReadU8(m_id);
				p_storage->ReadS16(m_unk0x02);
				p_storage->ReadS16(m_score);
			} else if (p_storage->IsWriteMode()) {
				p_storage->WriteU8(m_id);
				p_storage->WriteS16(m_unk0x02);
				p_storage->WriteS16(m_score);
			} else {
				return FAILURE;
			}

			return SUCCESS;
		}

		// TODO: Possibly private
		MxU8 m_id;
		MxS16 m_unk0x02;
		MxS16 m_score;
	};

	RaceState();

	static const char* ClassName() { return "RaceState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, RaceState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxResult Serialize(LegoStorage* p_storage) override;

	Entry* GetState(MxU8 p_id);

	// RaceState::~RaceState

	// RaceState::`scalar deleting destructor'

	// TODO: Most likely getters/setters are not used according to BETA.

	Entry m_state[5];
	undefined4 m_unk0x28;
};

class LegoRace : public LegoWorld {
public:
	LegoRace();
	~LegoRace() override;

	MxLong Notify(MxParam& p_param) override;

	static const char* HandlerClassName() { return "LegoRace"; }

	MxResult Create(MxDSAction& p_dsAction) override;

	virtual MxLong HandleClick(LegoEventNotificationParam&) = 0;

	virtual MxLong HandlePathStruct(LegoPathStructNotificationParam&) {
		return 0;
	}

	virtual MxLong HandleEndAction(MxEndActionNotificationParam&) { return 0; }

	MxBool Escape() override { return FALSE; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoRace::ClassName()) || LegoWorld::IsA(p_name);
	}

	virtual MxLong HandleType0Notification(MxNotificationParam&) { return 0; }

	virtual void VTable0x7c(LegoRaceMap* p_map, MxU32 p_index) {
		m_maps[p_index] = p_map;
	}

	MxBool VTable0x5c() override { return TRUE; }

	void Enable(MxBool p_enable) override;

	// LegoRace::`scalar deleting destructor'

protected:
	MxS32 m_unk0xf8;
	MxS32 m_unk0xfc;
	MxS32 m_unk0x100;
	MxS32 m_unk0x104;
	MxS32 m_unk0x108;
	MxS32 m_unk0x10c;
	LegoRaceMap* m_maps[3];
	LegoGameState::Area m_destLocation;
	LegoPathActor* m_pathActor;
	Act1State* m_act1State;
	MxStillPresenter* m_unk0x128;
	MxStillPresenter* m_unk0x12c;
	MxRect32 m_unk0x130;
	RaceState* m_raceState;
};

