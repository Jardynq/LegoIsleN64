#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "actionsfwd.h"
#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"

class LegoControlManagerNotificationParam;
class MxEndActionNotificationParam;
class MxStillPresenter;

class HospitalState : public LegoState {
public:
	HospitalState();
	~HospitalState() override {}

	const char* ClassName() const override { return "HospitalState"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, HospitalState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxResult Serialize(LegoStorage* p_storage) override;

	// HospitalState::`scalar deleting destructor'

	// TODO: Most likely getters/setters are not used according to BETA.

	undefined4 m_unk0x08;
	MxS16 m_unk0x0c;
	MxS16 m_unk0x0e;
	MxS16 m_unk0x10;
	MxS16 m_unk0x12;
	MxS16 m_unk0x14;
	MxS16 m_unk0x16;
};

class Hospital : public LegoWorld {
public:
	Hospital();
	~Hospital() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	MxBool VTable0x5c() override { return TRUE; }

	const char* ClassName() const override { return "Hospital"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, Hospital::ClassName()) || LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;

	inline void PlayAction(MxU32 p_objectId);

	// Hospital::`scalar deleting destructor'

private:
	MxLong HandleKeyPress(MxS8 p_key);
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);
	MxLong HandleButtonDown(LegoControlManagerNotificationParam& p_param);
	MxBool HandleControl(LegoControlManagerNotificationParam& p_param);

	MxS16 m_currentActorId;
	LegoGameState::Area m_destLocation;
	undefined2 m_unk0x100;
	HospitalState* m_hospitalState;
	undefined2 m_unk0x108;
	HospitalScript::Script m_currentAction;
	MxStillPresenter* m_copLedBitmap;
	MxStillPresenter* m_pizzaLedBitmap;
	undefined m_unk0x118;
	MxLong m_copLedAnimTimer;
	MxLong m_pizzaLedAnimTimer;
	MxLong m_time;
	undefined m_unk0x128;
};

#endif // HOSPITAL_H
