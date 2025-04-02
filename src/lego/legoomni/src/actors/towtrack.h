#ifndef TOWTRACK_H
#define TOWTRACK_H

#include "islepathactor.h"
#include "legostate.h"

class MxEndActionNotificationParam;

class TowTrackMissionState : public LegoState {
public:
	TowTrackMissionState();

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

	static const char* ClassName() { return "TowTrackMissionState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, TowTrackMissionState::ClassName()) ||
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

	// TowTrackMissionState::`scalar deleting destructor'

	undefined4 m_unk0x08;
	MxLong m_startTime;
	MxBool m_unk0x10;
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

class TowTrack : public IslePathActor {
public:
	TowTrack();
	~TowTrack() override;

	static const char* ClassName() { return "TowTrack"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, TowTrack::ClassName()) ||
			   IslePathActor::IsA(p_name);
	}

	MxLong Notify(MxParam& p_param) override;
	MxResult Create(MxDSAction& p_dsAction) override;
	void Animate(float p_time) override;
	MxLong HandleClick() override;
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;
	MxLong HandleEndAnim(LegoEndAnimNotificationParam& p_param) override;
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param) override;
	void Exit() override;
	virtual MxLong HandleEndAction(MxEndActionNotificationParam& p_param);

	void CreateState();
	void FUN_1004dab0();
	void ActivateSceneActions();
	void StopActions();
	void FUN_1004dbe0();

	// TowTrack::`scalar deleting destructor'

private:
	void Leave();
	void PlayFinalAnimation(IsleScript::Script p_objectId);
	void FUN_1004dcb0(IsleScript::Script p_objectId);
	void PlayAction(IsleScript::Script p_objectId);

	undefined4 m_unk0x160;
	TowTrackMissionState* m_state;
	MxS16 m_unk0x168;
	MxS16 m_actorId;
	MxS16 m_unk0x16c;
	MxS16 m_unk0x16e;
	IsleScript::Script m_lastAction;
	IsleScript::Script m_lastAnimation;
	MxFloat m_fuel;
	MxFloat m_time;
};

#endif // TOWTRACK_H
