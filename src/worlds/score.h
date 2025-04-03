#ifndef SCORE_H
#define SCORE_H

#include "gamestate.h"
#include "state.h"
#include "world.h"

class LegoControlManagerNotificationParam;
class MxEndActionNotificationParam;

class ScoreState : public LegoState {
public:
	ScoreState() : m_playCubeTutorial(TRUE) {}

	MxBool IsSerializable() override { return FALSE; }

	MxBool Reset() override {
		m_playCubeTutorial = TRUE;
		return TRUE;
	}

	static const char* ClassName() { return "ScoreState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, ScoreState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxBool GetTutorialFlag() { return m_playCubeTutorial; }
	void SetTutorialFlag(MxBool p_playCubeTutorial) {
		m_playCubeTutorial = p_playCubeTutorial;
	}

	// ScoreState::`scalar deleting destructor'

	// TODO: Most likely getters/setters are not used according to BETA.

	MxBool m_playCubeTutorial;
};

class Score : public LegoWorld {
public:
	Score();
	~Score() override;
	MxLong Notify(MxParam& p_param) override;

	MxBool VTable0x5c() override { return TRUE; }

	static const char* ClassName() { return "Score"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, Score::ClassName()) || LegoWorld::IsA(p_name);
	}

	// Score::`scalar deleting destructor'

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;

	void Paint();
	MxLong FUN_10001510(MxEndActionNotificationParam& p_param);
	MxLong FUN_100016d0(LegoControlManagerNotificationParam& p_param);
	void FillArea(MxS32 i_activity, MxS32 i_actor, MxS16 score);

protected:
	void DeleteScript();

	LegoGameState::Area m_destLocation;
	ScoreState* m_state;
	MxU8* m_surface;
};

#endif // SCORE_H
