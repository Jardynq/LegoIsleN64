#ifndef LEGOCARRACEACTOR_H
#define LEGOCARRACEACTOR_H

#include "legoraceactor.h"

extern const char* g_raceState;
extern const char* g_fuel;
extern const char* g_racing;

class LegoCarRaceActor : public virtual LegoRaceActor {
public:
	LegoCarRaceActor();

	static const char* ClassName() { return "LegoCarRaceActor"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoCarRaceActor::ClassName()) ||
			   LegoRaceActor::IsA(p_name);
	}

	inline MxU32 VTable0x6c(
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	) override;
	void Animate(float p_time) override;
	void SwitchBoundary(
		LegoPathBoundary*& p_boundary,
		LegoUnknown100db7f4*& p_edge,
		float& p_unk0xe4
	) override;
	MxResult VTable0x9c() override;

	// LegoCarRaceActor vtable

	virtual void FUN_10080590(float p_time);

	virtual void FUN_10012bb0(float p_unk0x14) { m_unk0x14 = p_unk0x14; }

	virtual float FUN_10012bc0() { return m_unk0x14; }

	virtual void FUN_10012bd0(float p_unk0x10) { m_unk0x10 = p_unk0x10; }

	virtual float FUN_10012be0() { return m_unk0x10; }

	virtual void FUN_10012bf0(float p_unk0x18) { m_unk0x18 = p_unk0x18; }

	virtual float FUN_10012c00() { return m_unk0x18; }

	virtual MxS32 VTable0x1c(LegoPathBoundary* p_boundary, LegoEdge* p_edge);

	// LegoCarRaceActor::`vbase destructor'

	// LegoCarRaceActor::`scalar deleting destructor'

	// LegoCarRaceActor::~LegoCarRaceActor

protected:
	MxFloat m_unk0x08;
	MxU8 m_unk0x0c;
	// Could be a multiplier for the maximum speed when going straight
	MxFloat m_unk0x10;
	// Could be the acceleration
	MxFloat m_unk0x14;
	MxFloat m_unk0x18;
	// Could be the current timestamp for time-based movement
	MxFloat m_unk0x1c;
	static MxFloat g_unk0x100f7aec;
};

class LegoJetskiRaceActor : public virtual LegoCarRaceActor {
public:
	LegoJetskiRaceActor();

	static const char* ClassName() { return "LegoJetskiRaceActor"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoJetskiRaceActor::ClassName()) ||
			   LegoCarRaceActor::IsA(p_name);
	}

	inline MxU32 VTable0x6c(
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	) override;
	void Animate(float p_time) override;
	MxS32 VTable0x1c(LegoPathBoundary* p_boundary, LegoEdge* p_edge) override;

	// LegoJetskiRaceActor::`vbase destructor'

	// LegoJetskiRaceActor::`scalar deleting destructor'

	// LegoJetskiRaceActor::~LegoJetskiRaceActor
};

// LegoCarRaceActor::`vbtable'

// LegoCarRaceActor::`vbtable'{for `LegoAnimActor'}

// LegoCarRaceActor::`vbtable'{for `LegoRaceActor'}

// LegoJetskiRaceActor::`vbtable'{for `LegoJetskiRaceActor'}

// LegoJetskiRaceActor::`vbtable'{for `LegoAnimActor'}

// LegoJetskiRaceActor::`vbtable'{for `LegoRaceActor'}

// LegoJetskiRaceActor::`vbtable'{for `LegoCarRaceActor'}

#endif // LEGOCARRACEACTOR_H
