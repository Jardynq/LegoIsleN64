#ifndef ACT2ACTOR_H
#define ACT2ACTOR_H

#include "anim_actor.h"

class Act2Actor : public LegoAnimActor {
public:
	struct Location {
		MxFloat m_position[3];
		MxFloat m_direction[3];
		const char* m_boundary;
		MxBool m_unk0x1c;
	};

	Act2Actor();

	void SetROI(LegoROI* p_roi, MxBool p_bool1, MxBool p_bool2) override;
	void SetWorldSpeed(MxFloat p_worldSpeed) override;

	MxS32 VTable0x68(Vector3& p_v1, Vector3& p_v2, Vector3& p_v3) override {
		if (m_unk0x1f) {
			return 0;
		}

		return LegoAnimActor::VTable0x68(p_v1, p_v2, p_v3);
	}

	void Animate(float p_time) override;
	MxResult HitActor(LegoPathActor*, MxBool) override;
	MxResult VTable0x9c() override;
	MxS32 VTable0xa0() override;

	void FUN_10018980();
	void FUN_10019250(MxFloat p_speed, MxFloat p_param2);
	void FUN_10019520();
	void FUN_10019560();
	MxU32 FUN_10019700(MxFloat p_param);
	void FUN_100199f0(MxS8 p_param);
	void FUN_100192a0(undefined4 p_location);
	LegoEntity* FUN_10019b90(MxBool* p_param);

	// Act2Actor::`scalar deleting destructor'

	// `vbtable'

private:
	undefined m_unk0x1c;
	MxS8 m_unk0x1d;
	undefined m_unk0x1e;
	MxBool m_unk0x1f;
	MxFloat m_unk0x20;
	MxFloat m_unk0x24;
	MxS8 m_unk0x28;
	MxFloat m_unk0x2c;
	MxFloat m_unk0x30;
	LegoAnimActorStruct* m_shootAnim;
	LegoCacheSound* m_unk0x38;
	undefined4 m_unk0x3c;
	undefined m_unk0x40;
	MxFloat m_unk0x44;
	MxS8 m_unk0x48;
	LegoEntity* m_unk0x4c;
};

// list<LegoBoundaryEdge,allocator<LegoBoundaryEdge>
// >::list<LegoBoundaryEdge,allocator<LegoBoundaryEdge> >

#endif // ACT2ACTOR_H
