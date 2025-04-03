#pragma once

#include "isle_path_actor.h"

class Motocycle : public IslePathActor {
public:
	Motocycle();

	static const char* ClassName() { return "Motorcycle"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, Motocycle::ClassName()) ||
			   IslePathActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void Animate(float p_time) override;
	MxLong HandleClick() override;
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;
	MxLong HandlePathStruct(LegoPathStructNotificationParam&) override;
	void Exit() override;

	void ActivateSceneActions();

	// Motocycle::`scalar deleting destructor'

private:
	undefined m_unk0x160[4];
	MxFloat m_fuel;
	MxFloat m_time;
};

