#ifndef LEGOEXTRAACTOR_H
#define LEGOEXTRAACTOR_H

#include "legoanimactor.h"

class LegoExtraActor : public virtual LegoAnimActor {
public:
	enum Axis { e_posz, e_negz, e_posx, e_negx };

	LegoExtraActor();
	~LegoExtraActor() override;

	const char* ClassName() const override { return "LegoExtraActor"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoExtraActor::ClassName()) ||
			   LegoAnimActor::IsA(p_name);
	}

	void SetWorldSpeed(MxFloat p_worldSpeed) override;
	MxS32 VTable0x68(Vector3& p_point1, Vector3& p_point2, Vector3& p_point3)
		override;
	inline MxU32 VTable0x6c(
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	) override;
	void Animate(float p_time) override;
	void VTable0x74(Matrix4& p_transform) override;
	MxU32 VTable0x90(float p_time, Matrix4& p_matrix) override;
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override;
	MxResult VTable0x9c() override;
	void VTable0xa4(MxBool& p_und1, MxS32& p_und2) override;
	void VTable0xc4() override;

	virtual MxResult FUN_1002aae0();

	void Restart();
	inline void FUN_1002ad8a();

	void SetUnknown0x0c(undefined p_unk0x0c) { m_unk0x0c = p_unk0x0c; }

	// LegoExtraActor::`scalar deleting destructor'

private:
	MxFloat m_scheduledTime;
	undefined m_unk0x0c;
	MxU8 m_axis;
	undefined m_unk0x0e;
	MxFloat m_prevWorldSpeed;
	MxU8 m_whichAnim;
	MxU8 m_unk0x15;
	MxMatrix m_unk0x18;
	LegoAnimActorStruct* m_assAnim;
	LegoAnimActorStruct* m_disAnim;
};

// LegoExtraActor::`vbtable'{for `LegoAnimActor'}

// LegoExtraActor::`vbtable'{for `LegoExtraActor'}

// vector<unsigned char *,allocator<unsigned char *> >::vector<unsigned char
// *,allocator<unsigned char *> >

// vector<unsigned char *,allocator<unsigned char *> >::size

// ?uninitialized_copy@@YAPAPAEPAPAE00@Z

#endif // LEGOEXTRAACTOR_H
