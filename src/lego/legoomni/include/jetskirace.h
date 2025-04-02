#ifndef JETSKIRACE_H
#define JETSKIRACE_H

#include "legorace.h"

class JetskiRace : public LegoRace {
public:
	static const char* HandlerClassName() { return "JetskiRace"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, JetskiRace::ClassName()) ||
			   LegoRace::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	MxLong HandleClick(LegoEventNotificationParam&) override;
	MxLong HandlePathStruct(LegoPathStructNotificationParam&) override;
	MxLong HandleEndAction(MxEndActionNotificationParam&) override;

	void FUN_10016930(MxS32 p_param1, MxS16 p_param2);

private:
	static MxS32 g_unk0x100f0c78;
};

class JetskiRaceState : public RaceState {
public:
	static const char* ClassName() { return "JetskiRaceState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, JetskiRaceState::ClassName()) ||
			   RaceState::IsA(p_name);
	}

	// JetskiRaceState::`scalar deleting destructor'
};

// JetskiRace::`scalar deleting destructor'

// JetskiRace::~JetskiRace

#endif // JETSKIRACE_H
