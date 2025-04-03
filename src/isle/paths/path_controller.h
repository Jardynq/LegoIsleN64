#ifndef LEGOPATHCONTROLLER_H
#define LEGOPATHCONTROLLER_H

#include "unkown100db7f4.h"
#include "path_actor.h"
#include "path_boundary.h"
#include "path_struct.h"

class LegoAnimPresenter;
class LegoWorld;
class MxAtomId;
class Vector3;

#if defined(_M_IX86) || defined(__i386__)
#define COMPARE_POINTER_TYPE MxS32
#else
#define COMPARE_POINTER_TYPE MxS32*
#endif

struct LegoPathCtrlEdge : public LegoUnknown100db7f4 {};

struct LegoPathCtrlEdgeCompare {
	MxU32 operator()(
		const LegoPathCtrlEdge* p_lhs,
		const LegoPathCtrlEdge* p_rhs
	) const {
		return (COMPARE_POINTER_TYPE) p_lhs < (COMPARE_POINTER_TYPE) p_rhs;
	}
};

typedef set<LegoPathCtrlEdge*, LegoPathCtrlEdgeCompare> LegoPathCtrlEdgeSet;

class LegoPathController : public MxCore {
public:
	struct CtrlBoundary {

		CtrlBoundary() {
			m_controller = NULL;
			m_boundary = NULL;
		}

		LegoPathController* m_controller;
		LegoPathBoundary* m_boundary;
	};

	struct CtrlEdge {

		CtrlEdge() {
			m_controller = NULL;
			m_edge = NULL;
		}

		LegoPathController* m_controller;
		LegoUnknown100db7f4* m_edge;
	};

	LegoPathController();
	~LegoPathController() override { Destroy(); }

	MxResult Tickle() override;

	static const char* ClassName() { return "LegoPathController"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoPathController::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	// LegoPathController::`scalar deleting destructor'

	virtual MxResult
	Create(MxU8* p_data, const Vector3& p_location, const MxAtomId& p_trigger);
	virtual void Destroy();

	MxResult PlaceActor(
		LegoPathActor* p_actor,
		const char* p_name,
		MxS32 p_src,
		float p_srcScale,
		MxS32 p_dest,
		float p_destScale
	);
	MxResult PlaceActor(
		LegoPathActor* p_actor,
		LegoAnimPresenter* p_presenter,
		Vector3& p_position,
		Vector3& p_direction
	);
	MxResult PlaceActor(LegoPathActor* p_actor);
	MxResult RemoveActor(LegoPathActor* p_actor);
	void FUN_100468f0(LegoAnimPresenter* p_presenter);
	void FUN_10046930(LegoAnimPresenter* p_presenter);
	MxResult FUN_10046b30(LegoPathBoundary*& p_boundaries, MxS32& p_numL);
	LegoPathBoundary* GetPathBoundary(const char* p_name);
	void Enable(MxBool p_enable);
	void FUN_10046bb0(LegoWorld* p_world);
	MxResult FUN_10048310(
		LegoPathEdgeContainer* p_grec,
		const Vector3& p_oldPosition,
		const Vector3& p_oldDirection,
		LegoPathBoundary* p_oldBoundary,
		const Vector3& p_newPosition,
		const Vector3& p_newDirection,
		LegoPathBoundary* p_newBoundary,
		LegoU8 p_mask,
		MxFloat* p_param9
	);
	MxS32 FUN_1004a240(
		LegoPathEdgeContainer& p_grec,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		LegoUnknown100db7f4*& p_edge,
		LegoPathBoundary*& p_boundary
	);
	MxResult FUN_1004a380(
		Vector3& p_param1,
		Vector3& p_param2,
		Mx3DPointFloat* p_param3,
		LegoPathBoundary*& p_boundary,
		MxFloat& p_param5
	);

	MxBool ActorExists(LegoPathActor* p_actor) {
		return m_actors.find(p_actor) != m_actors.end();
	}

	static MxResult Init();
	static MxResult Reset();

	static LegoUnknown100db7f4* GetControlEdgeA(MxS32 p_index) {
		return g_ctrlEdgesA[p_index].m_edge;
	}

	static LegoPathBoundary* GetControlBoundaryA(MxS32 p_index) {
		return g_ctrlBoundariesA[p_index].m_boundary;
	}

	// These two are an educated guess because BETA10 does not have the
	// g_ctrl.*B globals
	static LegoUnknown100db7f4* GetControlEdgeB(MxS32 p_index) {
		return g_ctrlEdgesB[p_index].m_edge;
	}
	static LegoPathBoundary* GetControlBoundaryB(MxS32 p_index) {
		return g_ctrlBoundariesB[p_index].m_boundary;
	}

private:
	void FUN_10046970();
	MxResult Read(LegoStorage* p_storage);
	MxResult ReadStructs(LegoStorage* p_storage);
	MxResult ReadEdges(LegoStorage* p_storage);
	MxResult ReadBoundaries(LegoStorage* p_storage);
	static MxResult ReadVector(LegoStorage* p_storage, Mx3DPointFloat& p_vec);
	static MxResult ReadVector(LegoStorage* p_storage, Mx4DPointFloat& p_vec);

	static MxU32 IsBetween(MxFloat p_v, MxFloat p_a, MxFloat p_b) {
		if (p_a <= p_b) {
			return p_v >= p_a && p_v <= p_b;
		} else {
			return p_v <= p_a && p_v >= p_b;
		}
	}

	static MxU32
	FUN_100c17a0(MxFloat p_v1, MxFloat p_v2, MxFloat p_a, MxFloat p_b) {
		assert(IsBetween(p_v1, p_a, p_b));
		assert(IsBetween(p_v2, p_a, p_b));

		if (p_a <= p_b) {
			return p_v1 < p_v2;
		} else {
			return p_v1 > p_v2;
		}
	}

	LegoPathBoundary* m_boundaries;
	LegoPathCtrlEdge* m_edges;
	Mx3DPointFloat* m_unk0x10;
	LegoPathStruct* m_structs;
	MxU16 m_numL;
	MxU16 m_numE;
	MxU16 m_numN;
	MxU16 m_numT;
	LegoPathCtrlEdgeSet m_pfsE;
	LegoPathActorSet m_actors;
	// Names verified by BETA10
	static CtrlBoundary* g_ctrlBoundariesA;
	static CtrlEdge* g_ctrlEdgesA;

	static const char* g_unk0x100f42f0[];
	static const char* g_unk0x100f4330[];
	static CtrlBoundary* g_ctrlBoundariesB;
	static CtrlEdge* g_ctrlEdgesB;
};

// clang-format off

// _Tree<LegoPathActor *,LegoPathActor *,set<LegoPathActor *,LegoPathActorSetCompare,allocator<LegoPathActor *> >::_Kfn,LegoPathActorSetCompare,allocator<LegoPathActor *> >::_Lbound


// _Tree<LegoPathActor *,LegoPathActor *,set<LegoPathActor *,LegoPathActorSetCompare,allocator<LegoPathActor *> >::_Kfn,LegoPathActorSetCompare,allocator<LegoPathActor *> >::_Buynode


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::~_Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathControl


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::iterator::_Inc


// ?erase@?$_Tree@PAULegoPathCtrlEdge@@PAU1@U_Kfn@?$set@PAULegoPathCtrlEdge@@ULegoPathCtrlEdgeCompare@@V?$allocator@PAULegoPathCtrlEdge@@@@@@ULegoPathCtrlEdgeCompare@@V?$allocator@PAULegoPathCtrlEdge@@@@@@QAE?AViterator@1@V21@@Z


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Erase


// Set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare>::~Set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare>


// set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::~set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >


// _Tree<LegoAnimPresenter *,LegoAnimPresenter *,set<LegoAnimPresenter *,LegoAnimPresenterSetCompare,allocator<LegoAnimPresenter *> >::_Kfn,LegoAnimPresenterSetCompare,allocator<LegoAnimPresenter *> >::find


// _Tree<LegoPathActor *,LegoPathActor *,set<LegoPathActor *,LegoPathActorSetCompare,allocator<LegoPathActor *> >::_Kfn,LegoPathActorSetCompare,allocator<LegoPathActor *> >::_Ubound


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Insert


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::iterator::_Dec


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Buynode


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Lrotate


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Rrotate


// LegoPathCtrlEdge::`vector deleting destructor'


// LegoPathCtrlEdge::LegoPathCtrlEdge


// LegoPathCtrlEdge::~LegoPathCtrlEdge


// LegoUnknown100db7f4::~LegoUnknown100db7f4


// list<LegoBoundaryEdge,allocator<LegoBoundaryEdge> >::begin


// list<LegoBoundaryEdge,allocator<LegoBoundaryEdge> >::insert


// list<LegoBoundaryEdge,allocator<LegoBoundaryEdge> >::erase


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,Le


// ?erase@?$_Tree@PAULegoPathCtrlEdge@@PAU1@U_Kfn@?$set@PAULegoPathCtrlEdge@@ULegoPathCtrlEdgeCompare@@V?$allocator@PAULegoPathCtrlEdge@@@@@@ULegoPathCtrlEdgeCompare@@V?$allocator@PAULegoPathCtrlEdge@@@@@@QAEIABQAULegoPathCtrlEdge@@@Z


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::find


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Copy


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Ubound


// list<LegoBEWithFloat,allocator<LegoBEWithFloat> >::~list<LegoBEWithFloat,allocator<LegoBEWithFloat> >


// list<LegoBEWithFloat,allocator<LegoBEWithFloat> >::insert


// list<LegoBEWithFloat,allocator<LegoBEWithFloat> >::_Buynode


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::iterator::_Inc


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::~_Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFlo


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::insert


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::iterator::_Dec


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::erase


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Buynode


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Init


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Insert


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Erase


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Lrotate


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Rrotate


// List<LegoBEWithFloat>::~List<LegoBEWithFloat>


// Multiset<LegoBEWithFloat *,LegoBEWithFloatComparator>::~Multiset<LegoBEWithFloat *,LegoBEWithFloatComparator>


// multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::~multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >


// ?_Construct@@YAXPAPAULegoBEWithFloat@@ABQAU1@@Z


// ?_Construct@@YAXPAPAULegoPathCtrlEdge@@ABQAU1@@Z


// _Tree<LegoPathCtrlEdge *,LegoPathCtrlEdge *,set<LegoPathCtrlEdge *,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Kfn,LegoPathCtrlEdgeCompare,allocator<LegoPathCtrlEdge *> >::_Nil


// _Tree<LegoBEWithFloat *,LegoBEWithFloat *,multiset<LegoBEWithFloat *,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Kfn,LegoBEWithFloatComparator,allocator<LegoBEWithFloat *> >::_Nil
// clang-format on

#endif // LEGOPATHCONTROLLER_H
