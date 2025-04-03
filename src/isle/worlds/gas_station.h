#pragma once

#include "gamestate.h"
#include "state.h"
#include "world.h"
#include "radio.h"

class MxStillPresenter;

class GasStationState : public LegoState {
public:
	GasStationState();

	static const char* ClassName() { return "GasStationState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, GasStationState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxResult Serialize(LegoStorage* p_storage) override;

	// GasStationState::`scalar deleting destructor'

	void PlayAction(GarageScript::Script p_objectId);
	void StopAction(GarageScript::Script p_objectId);
	void StopActions();

	// TODO: Most likely getters/setters are not used according to BETA.

	GarageScript::Script m_actions[3];
	undefined4 m_unk0x14;
	MxS16 m_pepperAction;
	MxS16 m_mamaAction;
	MxS16 m_papaAction;
	MxS16 m_nickAction;
	MxS16 m_lauraAction;
};

class GasStation : public LegoWorld {
public:
	GasStation();
	~GasStation() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	MxBool VTable0x5c() override { return TRUE; }

	static const char* ClassName() { return "GasStation"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, GasStation::ClassName()) ||
			   LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;
	virtual MxLong HandleControl(LegoControlManagerNotificationParam& p_param);

	// GasStation::`scalar deleting destructor'

private:
	inline void PlayAction(GarageScript::Script p_objectId);
	inline void StopAction(GarageScript::Script p_objectId);

	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);
	MxLong HandleKeyPress(MxS8 p_key);
	MxLong HandleButtonDown(LegoControlManagerNotificationParam& p_param);

	MxS16 m_currentActorId;
	undefined2 m_unk0xfa;
	LegoGameState::Area m_destLocation;
	GasStationState* m_state;
	undefined2 m_unk0x104;
	undefined2 m_unk0x106;
	MxStillPresenter* m_trackLedBitmap;
	MxLong m_unk0x10c;
	MxLong m_trackLedTimer;
	MxBool m_unk0x114;
	MxBool m_unk0x115;
	Radio m_radio;
};

