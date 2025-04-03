#ifndef ACT3ACTORS_H
#define ACT3ACTORS_H

#include "legoanimactor.h"

// File name verified by multiple assertions, e.g. BETA10 0x10018391

class Act3Ammo;
struct LegoBuildingInfo;
struct LegoPlantInfo;
class LegoWorld;

class Act3Shark : public LegoAnimActor {
public:
	Act3Shark();

	void ParseAction(char*) override;
	void Animate(float p_time) override;

	// LegoAnimActor vtable
	virtual MxResult EatPizza(Act3Ammo* p_ammo);

	static const char* ClassName() {
		// Does not exist in BETA10

		return "Act3Shark";
	}

	MxFloat GetUnknown0x2c() { return m_unk0x2c; }

	void SetUnknown0x2c(MxFloat p_unk0x2c) { m_unk0x2c = p_unk0x2c; }

	// Act3Shark::`scalar deleting destructor'

private:
	list<Act3Ammo*> m_eatPizzas;
	Act3Ammo* m_nextPizza;
	MxFloat m_unk0x2c;
	LegoWorld* m_world;
	LegoAnimActorStruct* m_unk0x34;
	LegoROI* m_unk0x38;
	Mx3DPointFloat m_unk0x3c;
};

class Act3Actor : public LegoAnimActor {
public:
	Act3Actor();

	MxU32 VTable0x90(float p_time, Matrix4& p_transform) override;
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override;

	static const char* ClassName() { return "Act3Actor"; }

	MxFloat GetUnknown0x1c() { return m_unk0x1c; }

	void SetUnknown0x1c(MxFloat p_unk0x1c) { m_unk0x1c = p_unk0x1c; }

	// Act3Actor::`scalar deleting destructor'

	// Act3Actor::~Act3Actor

private:
	static Mx3DPointFloat g_unk0x10104ef0;

	MxFloat m_unk0x1c;
};

class Act3Cop : public Act3Actor {
public:
	struct Act3CopDest {
		// name verified by BETA10 0x10018776
		const char* m_bName;
		// name verified by BETA10 0x100187cb
		LegoPathBoundary* m_boundary;
		MxFloat m_unk0x08[3];
		MxFloat m_unk0x14[3];
	};

	Act3Cop();

	void ParseAction(char* p_extra) override;
	void Animate(float p_time) override;
	MxResult HitActor(LegoPathActor*, MxBool) override;
	MxResult VTable0x9c() override;

	MxFloat GetUnknown0x20() { return m_unk0x20; }

	void SetUnknown0x20(MxFloat p_unk0x20) { m_unk0x20 = p_unk0x20; }

	MxResult FUN_10040350(Act3Ammo& p_ammo, const Vector3&);
	MxResult FUN_10040360();

	// Act3Cop::`scalar deleting destructor'

private:
	MxFloat m_unk0x20;
	LegoWorld* m_world;
	// name verified by BETA10 0x10018aa1
	LegoAnimActorStruct* m_eatAnim;
	undefined4 m_unk0x2c;
};

class Act3Brickster : public Act3Actor {
public:
	Act3Brickster();
	~Act3Brickster() override;

	void ParseAction(char* p_extra) override;
	void Animate(float p_time) override;
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override;
	void SwitchBoundary(
		LegoPathBoundary*& p_boundary,
		LegoUnknown100db7f4*& p_edge,
		float& p_unk0xe4
	) override;
	MxResult VTable0x9c() override;

	MxFloat GetUnknown0x20() { return m_unk0x20; }
	MxFloat GetUnknown0x24() { return m_unk0x24; }
	MxFloat GetUnknown0x50() { return m_unk0x50; }

	void SetUnknown0x20(MxFloat p_unk0x20) { m_unk0x20 = p_unk0x20; }
	void SetUnknown0x24(MxFloat p_unk0x24) { m_unk0x24 = p_unk0x24; }
	void SetUnknown0x50(MxFloat p_unk0x50) { m_unk0x50 = p_unk0x50; }

	MxResult FUN_100417a0(Act3Ammo& p_ammo, const Vector3&);
	MxResult FUN_100417c0();

	// Act3Brickster::`scalar deleting destructor'

private:
	MxS32 FUN_10042300();

	MxFloat m_unk0x20;
	MxFloat m_unk0x24;
	LegoWorld* m_world;
	LegoPlantInfo* m_pInfo;
	LegoBuildingInfo* m_bInfo;
	LegoAnimActorStruct* m_shootAnim;
	undefined4 m_unk0x38;
	Mx3DPointFloat m_unk0x3c;
	MxFloat m_unk0x50;
	MxFloat m_unk0x54;
	MxU8 m_unk0x58;
};

// Act3Actor::`vbase destructor'

// list<Act3Ammo *,allocator<Act3Ammo *> >::~list<Act3Ammo *,allocator<Act3Ammo
// *> >

// List<Act3Ammo *>::~List<Act3Ammo *>

// list<Act3Ammo *,allocator<Act3Ammo *> >::erase

// Act3Actor::`vbtable'

// Act3Cop::`vbtable'

// Act3Brickster::`vbtable'

// Act3Shark::`vbtable'

#endif // ACT3ACTORS_H
