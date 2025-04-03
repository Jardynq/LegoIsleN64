#pragma once

#include "path_actor.h"
#include "mx_geometry_3d.h"

class Act3;

class Act3Ammo : public LegoPathActor {
public:
	enum {
		c_pizza = 0x01,
		c_donut = 0x02,
		c_valid = 0x04,
		c_bit4 = 0x08,
		c_sharkFood = 0x10
	};

	Act3Ammo();
	~Act3Ammo() override;

	void Destroy(MxBool p_fromDestructor) override;
	void Animate(float p_time) override;

	MxU32 IsValid() { return m_ammoFlag & c_valid; }

	Mx3DPointFloat* GetUnknown0x160() { return m_eq; }

	MxFloat* GetUnknown0x19c() { return &m_unk0x19c; }

	void SetValid(MxBool p_valid) {
		if (p_valid) {
			m_ammoFlag |= c_valid;
		} else {
			m_ammoFlag &= ~c_valid;
		}
	}

	MxU32 IsPizza() { return m_ammoFlag & c_pizza; }

	MxU32 IsDonut() { return m_ammoFlag & c_donut; }

	void SetBit4(MxBool p_bit4) {
		if (p_bit4) {
			m_ammoFlag |= c_bit4;
		} else {
			m_ammoFlag &= ~c_bit4;
		}
	}

	MxU32 IsBit4() { return m_ammoFlag & c_bit4; }

	void SetSharkFood(MxBool p_sharkFood) {
		if (p_sharkFood) {
			m_ammoFlag |= c_sharkFood;
		} else {
			m_ammoFlag &= ~c_sharkFood;
		}
	}

	MxU32 IsSharkFood() { return m_ammoFlag & c_sharkFood; }

	MxFloat GetUnknown0x158() { return m_unk0x158; }

	void SetUnknown0x158(MxFloat p_unk0x158) { m_unk0x158 = p_unk0x158; }

	MxResult Remove();
	MxResult Create(Act3* p_world, MxU32 p_isPizza, MxS32 p_index);
	MxResult FUN_10053b40(
		const Vector3& p_srcLoc,
		const Vector3& p_srcDir,
		const Vector3& p_srcUp
	);
	MxResult FUN_10053cb0(
		LegoPathController* p_p,
		LegoPathBoundary* p_boundary,
		MxFloat p_unk0x19c
	);
	MxResult FUN_10053d30(LegoPathController* p_p, MxFloat p_unk0x19c);

	// Act3Ammo::`scalar deleting destructor'

private:
	MxResult FUN_10053db0(float p_param1, const Matrix4& p_param2);

	static Mx3DPointFloat g_unk0x10104f08;

	MxU16 m_ammoFlag;
	MxFloat m_unk0x158;
	Act3* m_world;
	Mx3DPointFloat m_eq[3];
	MxFloat m_unk0x19c;
};

