#ifndef PIZZA_H
#define PIZZA_H

#include "actionsfwd.h"
#include "isleactor.h"
#include "legostate.h"

class Act1State;
class PizzeriaState;
class SkateBoard;

class PizzaMissionState : public LegoState {
public:
	struct Mission {

		Mission() {}

		Mission(
			MxU8 p_actorId,
			undefined2 p_unk0x04,
			MxLong* p_finishTimes,
			IsleScript::Script* p_actions,
			MxS16 p_numActions
		) {
			m_numActions = p_numActions;
			m_actorId = p_actorId;
			m_unk0x04 = p_unk0x04;
			m_unk0x06 = 1;
			m_unk0x08 = 1;
			m_finishTimes = p_finishTimes;
			m_startTime = INT_MIN;
			m_unk0x14 = 1;
			m_score = LegoState::e_grey;
			m_hiScore = LegoState::e_grey;
			m_actions = p_actions;
		}

		Mission& operator=(const Mission& p_mission) {
			m_actorId = p_mission.m_actorId;
			m_unk0x04 = p_mission.m_unk0x04;
			m_unk0x06 = p_mission.m_unk0x06;
			m_unk0x08 = p_mission.m_unk0x08;
			m_finishTimes = p_mission.m_finishTimes;
			m_startTime = p_mission.m_startTime;
			m_unk0x14 = p_mission.m_unk0x14;
			m_score = p_mission.m_score;
			m_hiScore = p_mission.m_hiScore;
			m_actions = p_mission.m_actions;
			m_numActions = p_mission.m_numActions;
			return *this;
		}

		IsleScript::Script GetRedFinishAction() {
			return m_actions[m_numActions + 6];
		}

		IsleScript::Script GetBlueFinishAction() {
			return m_actions[m_numActions + 7];
		}

		IsleScript::Script GetYellowFinishAction() {
			return m_actions[m_numActions + 8];
		}

		MxLong GetRedFinishTime() { return m_finishTimes[0]; }

		MxLong GetBlueFinishTime() { return m_finishTimes[1]; }

		void UpdateScore(ScoreColor p_score) {
			m_score = p_score;
			if (m_hiScore < p_score) {
				m_hiScore = p_score;
			}
		}

		IsleScript::Script* GetActions() { return m_actions; }

		IsleScript::Script GetUnknownFinishAction() {
			return m_actions[m_numActions + 2];
		}

		MxLong GetTimeoutTime() { return m_finishTimes[3]; }

		MxS16 m_numActions;
		MxU8 m_actorId;
		undefined2 m_unk0x04;
		MxS16 m_unk0x06;
		undefined m_unk0x08;
		MxLong* m_finishTimes;
		MxLong m_startTime;
		MxS16 m_unk0x14;
		MxS16 m_score;
		MxS16 m_hiScore;
		IsleScript::Script* m_actions;
	};

	PizzaMissionState();

	const char* ClassName() const override { return "PizzaMissionState"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, PizzaMissionState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxResult Serialize(LegoStorage* p_storage) override;

	void SetUnknown0xb0(MxU32 p_unk0xb0) { m_unk0xb0 = p_unk0xb0; }

	MxU32 GetUnknown0xb0() { return m_unk0xb0; }

	MxS16 GetHighScore(MxU8 p_actorId) {
		return GetMission(p_actorId)->m_hiScore;
	}

	// PizzaMissionState::`scalar deleting destructor'

	Mission* GetMission(MxU8 p_actorId);
	MxS16 FUN_10039540();

	PizzeriaState* m_pizzeriaState;
	undefined4 m_unk0x0c;
	Mission m_missions[5];
	MxU32 m_unk0xb0;
	static IsleScript::Script g_pepperActions[];
	static IsleScript::Script g_mamaActions[];
	static IsleScript::Script g_papaActions[];
	static IsleScript::Script g_nickActions[];
	static IsleScript::Script g_lauraActions[];

	static MxLong g_pepperFinishTimes[];
	static MxLong g_mamaFinishTimes[];
	static MxLong g_papaFinishTimes[];
	static MxLong g_nickFinishTimes[];
	static MxLong g_lauraFinishTimes[];
};

class Pizza : public IsleActor {
public:
	Pizza();
	~Pizza() override;

	MxResult Tickle() override;

	const char* ClassName() const override { return "Pizza"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, Pizza::ClassName()) || IsleActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	MxLong HandleClick() override;
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param) override;
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param) override;

	void CreateState();
	void FUN_10038220(IsleScript::Script p_objectId);
	void FUN_100382b0();
	void StopActions();
	void PlayAction(MxU32 p_objectId, MxBool p_param7);

	void SetSkateboard(SkateBoard* p_skateBoard) {
		m_skateBoard = p_skateBoard;
	}

	// Pizza::`scalar deleting destructor'

private:
	PizzaMissionState* m_state;
	PizzaMissionState::Mission* m_mission;
	SkateBoard* m_skateBoard;
	Act1State* m_act1state;
	IsleScript::Script m_unk0x8c;
	MxLong m_unk0x90;
	MxLong m_unk0x94;
	MxBool m_unk0x98;
};

#endif // PIZZA_H
