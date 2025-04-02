#ifndef CARRACE_H
#define CARRACE_H

#include "legorace.h"

class RaceSkel;

class CarRaceState : public RaceState {
public:
	static const char* ClassName() { return "CarRaceState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, CarRaceState::ClassName()) ||
			   RaceState::IsA(p_name);
	}

	// CarRaceState::`scalar deleting destructor'
};

class CarRace : public LegoRace {
public:
	CarRace();

	static const char* ClassName() { return "CarRace"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, CarRace::ClassName()) || LegoRace::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	MxLong HandleClick(LegoEventNotificationParam&) override;
	MxLong HandlePathStruct(LegoPathStructNotificationParam&) override;
	MxLong HandleEndAction(MxEndActionNotificationParam&) override;
	MxLong HandleType0Notification(MxNotificationParam&) override;

	RaceSkel* GetSkeleton() { return m_skeleton; }

	void SetSkeleton(RaceSkel* p_skeleton) { m_skeleton = p_skeleton; }

	void FUN_10017820(MxS32 p_param1, MxS16 p_param2);

	// CarRace::`scalar deleting destructor'

private:
	static MxS32 g_unk0x100d5d10[];
	static MxS32 g_unk0x100d5d30[];
	static MxS32 g_unk0x100d5d40[];
	static MxS32 g_unk0x100d5d50[];
	static MxS32 g_unk0x100d5d60[];

	MxS32 m_unk0x144;
	MxS32 m_unk0x148;
	MxS32 m_unk0x14c;
	RaceSkel* m_skeleton;
};

#endif // CARRACE_H
