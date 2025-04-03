#pragma once

#include "gamestate.h"
#include "world.h"

class MxStillPresenter;

class HistoryBook : public LegoWorld {
public:
	HistoryBook();
	~HistoryBook() override;

	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "HistoryBook"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, HistoryBook::ClassName()) ||
			   LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;

	// HistoryBook::`scalar deleting destructor'

private:
	LegoGameState::Area m_destLocation;
	MxStillPresenter* m_alphabet[26];
	// variable name verified by BETA10 0x1002bd27
	MxStillPresenter* m_name[20][7];
	MxStillPresenter* m_scores[20];
};

