#ifndef LEGOPATHACTOR_H
#define LEGOPATHACTOR_H

#include "legoactor.h"
#include "misc/legounknown.h"

struct LegoEdge;
struct LegoNamedPlane;
class LegoPathBoundary;
class LegoPathController;
struct LegoPathEdgeContainer;
struct LegoUnknown100db7f4;
class LegoWEEdge;

extern MxLong g_unk0x100f3308;
extern const char* g_strHIT_WALL_SOUND;

class LegoPathActor : public LegoActor {
public:
	enum ActorState {
		// States
		c_initial = 0,
		c_one = 1,
		c_two = 2,
		c_three = 3,
		c_disabled = 4,
		c_maxState = 255,

		// Flags
		c_noCollide = 0x100
	};

	LegoPathActor();
	~LegoPathActor() override;

	void ParseAction(char* p_extra) override;
	virtual MxS32 VTable0x68(Vector3& p_v1, Vector3& p_v2, Vector3& p_v3);
	virtual MxU32 VTable0x6c(
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	);
	virtual void Animate(float p_time);
	virtual void VTable0x74(Matrix4& p_transform);

	virtual void SetUserNavFlag(MxBool p_userNavFlag) {
		m_userNavFlag = p_userNavFlag;
	}

	virtual MxBool GetUserNavFlag() { return m_userNavFlag; }

	virtual MxResult VTable0x80(
		const Vector3& p_point1,
		Vector3& p_point2,
		Vector3& p_point3,
		Vector3& p_point4
	);
	virtual MxResult VTable0x84(
		LegoPathBoundary* p_boundary,
		float p_time,
		Vector3& p_p1,
		Vector3& p_p4,
		LegoUnknown100db7f4& p_destEdge,
		float p_destScale
	);
	virtual MxResult VTable0x88(
		LegoPathBoundary* p_boundary,
		float p_time,
		LegoEdge& p_srcEdge,
		float p_srcScale,
		LegoUnknown100db7f4& p_destEdge,
		float p_destScale
	);
	virtual MxS32 VTable0x8c(float p_time, MxMatrix& p_transform);

	virtual MxU32 VTable0x90(float, Matrix4&) { return FALSE; }

	virtual MxResult HitActor(LegoPathActor*, MxBool) { return 0; }

	virtual void SwitchBoundary(
		LegoPathBoundary*& p_boundary,
		LegoUnknown100db7f4*& p_edge,
		float& p_unk0xe4
	);
	virtual MxResult VTable0x9c();

	virtual MxS32 VTable0xa0() { return 0; }

	virtual void VTable0xa4(MxBool& p_und1, MxS32& p_und2);
	virtual void VTable0xa8();

	virtual void SetMaxLinearVel(MxFloat p_maxLinearVel) {
		m_maxLinearVel = p_maxLinearVel;
	}

	virtual MxFloat GetMaxLinearVel() { return m_maxLinearVel; }

	virtual MxFloat VTable0xb4() { return m_unk0x140; }

	virtual MxFloat VTable0xb8() { return m_unk0x144; }

	virtual void VTable0xbc(MxFloat p_unk0x140) { m_unk0x140 = p_unk0x140; }

	virtual void VTable0xc0(MxFloat p_unk0x144) { m_unk0x144 = p_unk0x144; }

	virtual void VTable0xc4() {}

	virtual void VTable0xc8(MxU8 p_unk0x148) { m_unk0x148 = p_unk0x148; }

	const char* ClassName() const override { return "LegoPathActor"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoPathActor::ClassName()) ||
			   LegoActor::IsA(p_name);
	}

	LegoPathBoundary* GetBoundary() { return m_boundary; }

	MxU32 GetActorState() { return m_actorState; }

	LegoPathController* GetController() { return m_pathController; }
	MxBool GetCollideBox() { return m_collideBox; }
	MxFloat GetLastTime() { return m_lastTime; }
	MxFloat GetActorTime() { return m_actorTime; }

	void SetBoundary(LegoPathBoundary* p_boundary) { m_boundary = p_boundary; }

	void SetActorState(MxU32 p_actorState) { m_actorState = p_actorState; }

	void SetController(LegoPathController* p_pathController) {
		m_pathController = p_pathController;
	}
	void SetLastTime(MxFloat p_lastTime) { m_lastTime = p_lastTime; }
	void SetActorTime(MxFloat p_actorTime) { m_actorTime = p_actorTime; }

	void UpdatePlane(LegoNamedPlane& p_namedPlane);
	void PlaceActor(LegoNamedPlane& p_namedPlane);

	// LegoPathActor::`scalar deleting destructor'

protected:
	inline MxU32 FUN_1002edd0(
		list<LegoPathBoundary*>& p_boundaries,
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3,
		MxS32 p_und
	);

	MxFloat m_BADuration;
	MxFloat m_unk0x7c;
	MxFloat m_actorTime;
	MxFloat m_lastTime;
	LegoPathBoundary* m_boundary;
	LegoUnknown m_unk0x8c;
	MxU32 m_actorState;
	LegoUnknown100db7f4* m_destEdge;
	MxFloat m_unk0xe4;
	MxBool m_collideBox;
	MxBool m_unk0xe9;
	MxBool m_userNavFlag;
	MxMatrix m_unk0xec;
	LegoPathEdgeContainer* m_grec;
	LegoPathController* m_pathController;
	MxFloat m_maxLinearVel;
	MxFloat m_unk0x140;
	MxFloat m_unk0x144;
	MxU8 m_unk0x148;
	MxS32 m_unk0x14c;
	MxFloat m_unk0x150;
};

// LegoPathActor::FUN_1002edd0

// List<LegoBoundaryEdge>::~List<LegoBoundaryEdge>

// list<LegoBoundaryEdge,allocator<LegoBoundaryEdge>
// >::~list<LegoBoundaryEdge,allocator<LegoBoundaryEdge> >

// list<LegoPathBoundary *,allocator<LegoPathBoundary *>
// >::~list<LegoPathBoundary *,allocator<LegoPathBoundary *> >

// list<LegoPathBoundary *,allocator<LegoPathBoundary *> >::insert

// List<LegoPathBoundary *>::~List<LegoPathBoundary *>

#endif // LEGOPATHACTOR_H
