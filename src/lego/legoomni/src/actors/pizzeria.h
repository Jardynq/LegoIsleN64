#ifndef PIZZERIA_H
#define PIZZERIA_H

#include "actionsfwd.h"
#include "isleactor.h"
#include "legostate.h"

class PizzaMissionState;

class PizzeriaState : public LegoState {
public:
	PizzeriaState();

	static const char* ClassName() { return "PizzeriaState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, PizzeriaState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxResult Serialize(LegoStorage* p_storage) override;

	// PizzeriaState::`scalar deleting destructor'

	MxS16 FUN_10017d50();
	MxU32 NextAction();

	Playlist m_unk0x08[5];
	MxS32 m_unk0x44[5];
	static IsleScript::Script g_pepperActions[];
	static IsleScript::Script g_mamaActions[];
	static IsleScript::Script g_papaActions[];
	static IsleScript::Script g_nickActions[];
	static IsleScript::Script g_lauraActions[];
};

class Pizzeria : public IsleActor {
public:
	Pizzeria() : m_pizzeriaState(NULL) {}

	static const char* ClassName() { return "Pizzeria"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, Pizzeria::ClassName()) || IsleActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	MxLong HandleClick() override;

	void CreateState();

	// Pizzeria::`scalar deleting destructor'

private:
	PizzeriaState* m_pizzeriaState;
	PizzaMissionState* m_pizzaMissionState;
};

#endif // PIZZERIA_H
