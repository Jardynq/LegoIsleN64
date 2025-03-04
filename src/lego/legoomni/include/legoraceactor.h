#ifndef LEGORACEACTOR_H
#define LEGORACEACTOR_H

#include "legoanimactor.h"

class Matrix4;

class LegoRaceActor : public virtual LegoAnimActor {
public:
	LegoRaceActor();

	const char* ClassName() const override { return "LegoRaceActor"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoRaceActor::ClassName()) ||
			   LegoAnimActor::IsA(p_name);
	}

	MxS32 VTable0x68(Vector3& p_v1, Vector3& p_v2, Vector3& p_v3) override;
	MxU32 VTable0x90(float p_time, Matrix4& p_matrix) override;
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override;

	virtual MxResult FUN_10014aa0();

	// LegoRaceActor::`vbase destructor'

	// LegoRaceActor::`scalar deleting destructor'

private:
	MxFloat m_unk0x08;
	static Mx3DPointFloat g_unk0x10102b08;
};

// LegoRaceActor::`vbtable'{for `LegoRaceActor'}

// LegoRaceActor::`vbtable'{for `LegoAnimActor'}

#endif // LEGORACEACTOR_H
