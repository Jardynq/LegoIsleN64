#ifndef POLICE_H
#define POLICE_H

#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"
#include "radio.h"

class LegoControlManagerNotificationParam;
class LegoEventNotificationParam;
class MxDSAction;

class PoliceState : public LegoState {
public:
	PoliceState();
	~PoliceState() override {}

	const char* ClassName() const override { return "PoliceState"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, PoliceState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxResult Serialize(LegoStorage* p_storage) override;

	// PoliceState::`scalar deleting destructor'

	undefined4 GetUnknown0x0c() { return m_unk0x0c; }
	void SetUnknown0x0c(undefined4 p_unk0x0c) { m_unk0x0c = p_unk0x0c; }

	void FUN_1005ea40();

	// TODO: Most likely getters/setters are not used according to BETA.

	PoliceScript::Script m_policeScript;
	undefined4 m_unk0x0c;
};

class Police : public LegoWorld {
public:
	Police();
	~Police() override;

	MxLong Notify(MxParam& p_param) override;

	MxBool VTable0x5c() override { return TRUE; }

	const char* ClassName() const override { return "Police"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, Police::ClassName()) || LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;

	// Police::`scalar deleting destructor'

private:
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);
	MxLong HandleKeyPress(LegoEventNotificationParam& p_param);

	Radio m_radio;
	PoliceState* m_policeState;
	LegoGameState::Area m_destLocation;
};

#endif // POLICE_H
