#ifndef AMBULANCE_H
#define AMBULANCE_H

#include "islepathactor.h"
#include "legostate.h"

class MxEndActionNotificationParam;

class AmbulanceMissionState : public LegoState {
public:
	AmbulanceMissionState();

	MxResult Serialize(LegoStorage* p_storage) override {
		LegoState::Serialize(p_storage);

		if (p_storage->IsReadMode()) {
			p_storage->ReadS16(m_peScore);
			p_storage->ReadS16(m_maScore);
			p_storage->ReadS16(m_paScore);
			p_storage->ReadS16(m_niScore);
			p_storage->ReadS16(m_laScore);
			p_storage->ReadS16(m_peHighScore);
			p_storage->ReadS16(m_maHighScore);
			p_storage->ReadS16(m_paHighScore);
			p_storage->ReadS16(m_niHighScore);
			p_storage->ReadS16(m_laHighScore);
		} else if (p_storage->IsWriteMode()) {
			p_storage->WriteS16(m_peScore);
			p_storage->WriteS16(m_maScore);
			p_storage->WriteS16(m_paScore);
			p_storage->WriteS16(m_niScore);
			p_storage->WriteS16(m_laScore);
			p_storage->WriteS16(m_peHighScore);
			p_storage->WriteS16(m_maHighScore);
			p_storage->WriteS16(m_paHighScore);
			p_storage->WriteS16(m_niHighScore);
			p_storage->WriteS16(m_laHighScore);
		}

		return SUCCESS;
	}

	static const char* ClassName() { return "AmbulanceMissionState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, AmbulanceMissionState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxS16 GetHighScore(MxU8 p_actorId) {
		switch (p_actorId) {
		case LegoActor::c_pepper:
			return m_peHighScore;
			break;
		case LegoActor::c_mama:
			return m_maHighScore;
			break;
		case LegoActor::c_papa:
			return m_paHighScore;
			break;
		case LegoActor::c_nick:
			return m_niHighScore;
			break;
		case LegoActor::c_laura:
			return m_laHighScore;
			break;
		}

		return 0;
	}

	void UpdateScore(ScoreColor p_score, MxS16 p_actorId) {
		switch (p_actorId) {
		case LegoActor::c_pepper:
			m_peScore = p_score;
			if (m_peHighScore < p_score) {
				m_peHighScore = p_score;
			}
			break;
		case LegoActor::c_mama:
			m_maScore = p_score;
			if (m_maHighScore < p_score) {
				m_maHighScore = p_score;
			}
			break;
		case LegoActor::c_papa:
			m_paScore = p_score;
			if (m_paHighScore < p_score) {
				m_paHighScore = p_score;
			}
			break;
		case LegoActor::c_nick:
			m_niScore = p_score;
			if (m_niHighScore < p_score) {
				m_niHighScore = p_score;
			}
			break;
		case LegoActor::c_laura:
			m_laScore = p_score;
			if (m_laHighScore < p_score) {
				m_laHighScore = p_score;
			}
			break;
		}
	}

	// AmbulanceMissionState::`scalar deleting destructor'

	undefined4 m_unk0x08;
	MxLong m_startTime;
	MxS16 m_peScore;
	MxS16 m_maScore;
	MxS16 m_paScore;
	MxS16 m_niScore;
	MxS16 m_laScore;
	MxS16 m_peHighScore;
	MxS16 m_maHighScore;
	MxS16 m_paHighScore;
	MxS16 m_niHighScore;
	MxS16 m_laHighScore;
};

class Ambulance : public IslePathActor {
public:
	Ambulance();
	~Ambulance() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	void Destroy(MxBool p_fromDestructor) override {}

	static const char* ClassName() { return "Ambulance"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, Ambulance::ClassName()) ||
			   IslePathActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void Animate(float p_time) override;
	MxLong HandleClick() override;
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param) override;
	void Exit() override;
	virtual MxLong HandleButtonDown(LegoControlManagerNotificationParam& p_param
	);
	virtual MxLong HandleEndAction(MxEndActionNotificationParam& p_param);

	void CreateState();
	void FUN_10036e60();
	void ActivateSceneActions();
	void StopActions();
	void FUN_10037250();

	// Ambulance::`scalar deleting destructor'

private:
	void PlayAnimation(IsleScript::Script p_objectId);
	void PlayFinalAnimation(IsleScript::Script p_objectId);
	void StopAction(IsleScript::Script p_objectId);
	void PlayAction(IsleScript::Script p_objectId);
	void Leave();

	undefined m_unk0x160[4];
	AmbulanceMissionState* m_state;
	MxS16 m_unk0x168;
	MxS16 m_actorId;
	MxS16 m_unk0x16c;
	MxS16 m_unk0x16e;
	MxS16 m_unk0x170;
	MxS16 m_unk0x172;
	IsleScript::Script m_lastAction;
	IsleScript::Script m_lastAnimation;
	MxFloat m_fuel;
	MxFloat m_time;
};

#endif // AMBULANCE_H
