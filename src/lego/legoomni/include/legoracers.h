#ifndef LEGORACERS_H
#define LEGORACERS_H

// clang-format off
#include "legoracespecial.h"
// clang-format on
#include "legoracemap.h"

#define LEGORACECAR_UNKNOWN_0 0
#define LEGORACECAR_UNKNOWN_1 1
#define LEGORACECAR_KICK1 2 // name guessed
#define LEGORACECAR_KICK2 4 // name validated by BETA10 0x100cb659

struct EdgeReference {
	const char* m_name; // name verified by BETA10 0x100cbee6
	LegoPathBoundary* m_b;
};

struct SkeletonKickPhase {
	EdgeReference* m_edgeRef;
	float m_lower;
	float m_upper;
	MxU8 m_userState;
};

class LegoJetski : public LegoJetskiRaceActor, public LegoRaceMap {
public:
	LegoJetski();
	~LegoJetski() override;

	MxLong Notify(MxParam& p_param) override;

	const char* ClassName() const override { return "LegoJetski"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoJetski::ClassName()) ||
			   LegoJetskiRaceActor::IsA(p_name);
	}

	void ParseAction(char* p_extra) override;
	void SetWorldSpeed(MxFloat p_worldSpeed) override;

	MxU32 VTable0x6c(
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	) override {
		return LegoJetskiRaceActor::VTable0x6c(
			p_boundary,
			p_v1,
			p_v2,
			p_f1,
			p_f2,
			p_v3
		);
	}

	void Animate(float p_time) override;
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override;

	void SwitchBoundary(
		LegoPathBoundary*& p_boundary,
		LegoUnknown100db7f4*& p_edge,
		float& p_unk0xe4
	) override {
		LegoJetskiRaceActor::SwitchBoundary(p_boundary, p_edge, p_unk0xe4);
	}

	MxResult VTable0x9c() override { return LegoJetskiRaceActor::VTable0x9c(); }

	virtual void FUN_100136f0(float p_worldSpeed);

	static void InitSoundIndices();

	// LegoJetski::`scalar deleting destructor'
};

class LegoRaceCar : public LegoCarRaceActor, public LegoRaceMap {
public:
	LegoRaceCar();
	~LegoRaceCar() override;

	MxLong Notify(MxParam& p_param) override;

	const char* ClassName() const override { return "LegoRaceCar"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoRaceCar::ClassName()) ||
			   LegoCarRaceActor::IsA(p_name);
	}

	void ParseAction(char* p_extra) override;
	void SetWorldSpeed(MxFloat p_worldSpeed) override;

	MxU32 VTable0x6c(
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	) override {
		return LegoCarRaceActor::VTable0x6c(
			p_boundary,
			p_v1,
			p_v2,
			p_f1,
			p_f2,
			p_v3
		);
	}

	void Animate(float p_time) override;
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override;

	void SwitchBoundary(
		LegoPathBoundary*& p_boundary,
		LegoUnknown100db7f4*& p_edge,
		float& p_unk0xe4
	) override {
		LegoCarRaceActor::SwitchBoundary(p_boundary, p_edge, p_unk0xe4);
	}

	MxResult VTable0x9c() override;

	virtual void SetMaxLinearVelocity(float p_maxLinearVelocity);
	virtual void FUN_10012ff0(float p_param);
	virtual MxU32 HandleSkeletonKicks(float p_param1);

	static void FUN_10012de0();
	static void InitSoundIndices();

	// LegoRaceCar::`scalar deleting destructor'

private:
	undefined m_userState;
	float m_unk0x58;
	Mx3DPointFloat m_unk0x5c;
	// Names verified by BETA10 0x100cb4a9
	LegoAnimActorStruct* m_skelKick1Anim;
	LegoAnimActorStruct* m_skelKick2Anim;
	// Name verified by BETA10 0x100cb4f0
	LegoPathBoundary* m_kick1B;
	// Name verified by BETA10 0x100cb537
	LegoPathBoundary* m_kick2B;
};

// LegoRaceCar::`vbtable'{for `LegoCarRaceActor'}

// LegoRaceCar::`vbtable'{for `LegoRaceMap'}

// LegoRaceCar::`vbtable'{for `LegoAnimActor'}

// LegoRaceCar::`vbtable'{for `LegoRaceActor'}

// LegoJetski::`vbtable'{for `LegoCarRaceActor'}

// LegoJetski::`vbtable'{for `LegoRaceActor'}

// LegoJetski::`vbtable'{for `LegoAnimActor'}

// LegoJetski::`vbtable'

// LegoJetski::`vbtable'{for `LegoJetskiRaceActor'}

#endif // LEGORACERS_H
