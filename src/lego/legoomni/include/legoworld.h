#ifndef LEGOWORLD_H
#define LEGOWORLD_H

// clang-format off
#include "mxpresenterlist.h"
#include "legoentitylist.h"
#include "legocachesoundlist.h"
// clang-format on

#include "legoentity.h"
#include "legomain.h"
#include "legopathcontrollerlist.h"
#include "roi/legoroi.h"

class LegoCameraController;
class LegoPathBoundary;
class LegoHideAnimPresenter;

#if defined(_M_IX86) || defined(__i386__)
#define COMPARE_POINTER_TYPE MxS32
#else
#define COMPARE_POINTER_TYPE MxS32*
#endif

struct CoreSetCompare {
	MxS32 operator()(MxCore* const& p_a, MxCore* const& p_b) const {
		return (COMPARE_POINTER_TYPE) p_a < (COMPARE_POINTER_TYPE) p_b;
	}
};

typedef set<MxCore*, CoreSetCompare> MxCoreSet;

class LegoWorld : public LegoEntity {
public:
	enum StartupTicks { e_start = 0, e_one, e_two, e_three, e_four };

	LegoWorld();
	~LegoWorld() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;
	MxResult Create(MxDSAction& p_dsAction) override;
	void Destroy(MxBool p_fromDestructor) override;
	virtual void ReadyWorld();
	virtual LegoCameraController* VTable0x54();
	virtual void Add(MxCore* p_object);

	// The BETA10 match could also be LegoWorld::Escape(), only the child
	// classes might be able to tell FUNCTION: LEGO1 0x1001d670 FUNCTION: BETA10
	virtual MxBool VTable0x5c() { return FALSE; }

	virtual void VTable0x60() {}

	virtual MxBool Escape() { return FALSE; }

	virtual void Enable(MxBool p_enable);

	const char* ClassName() const override { return "LegoWorld"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoWorld::ClassName()) ||
			   LegoEntity::IsA(p_name);
	}

	MxBool PresentersPending();
	void Remove(MxCore* p_object);
	MxResult PlaceActor(
		LegoPathActor* p_actor,
		const char* p_name,
		MxS32 p_src,
		float p_srcScale,
		MxS32 p_dest,
		float p_destScale
	);
	MxResult PlaceActor(LegoPathActor* p_actor);
	MxResult PlaceActor(
		LegoPathActor* p_actor,
		LegoAnimPresenter* p_presenter,
		Vector3& p_position,
		Vector3& p_direction
	);
	void RemoveActor(LegoPathActor* p_actor);
	MxBool ActorExists(LegoPathActor* p_actor);
	void FUN_1001fda0(LegoAnimPresenter* p_presenter);
	void FUN_1001fe90(LegoAnimPresenter* p_presenter);
	LegoPathBoundary* FindPathBoundary(const char* p_name);
	void AddPath(LegoPathController* p_controller);
	MxResult GetCurrPathInfo(LegoPathBoundary** p_boundaries, MxS32& p_numL);
	MxCore* Find(const char* p_class, const char* p_name);
	MxCore* Find(const MxAtomId& p_atom, MxS32 p_entityId);

	LegoCameraController* GetCameraController() { return m_cameraController; }

	LegoEntityList* GetEntityList() { return m_entityList; }
	LegoOmni::World GetWorldId() { return m_worldId; }
	MxBool GetUnknown0xd0Empty() { return m_set0xd0.empty(); }
	list<LegoROI*>& GetROIList() { return m_roiList; }
	LegoHideAnimPresenter* GetHideAnimPresenter() { return m_hideAnim; }

	void SetWorldId(LegoOmni::World p_worldId) { m_worldId = p_worldId; }

	// LegoWorld::`scalar deleting destructor'

protected:
	LegoPathControllerList m_list0x68;
	MxPresenterList m_animPresenters;
	LegoCameraController* m_cameraController;
	LegoEntityList* m_entityList;
	LegoCacheSoundList* m_cacheSoundList;
	MxBool m_destroyed;
	MxCoreSet m_set0xa8;
	MxPresenterList m_controlPresenters;
	MxCoreSet m_set0xd0;
	list<LegoROI*> m_roiList;
	LegoOmni::World m_worldId;
	// name verified by BETA10 0x100c7f59
	LegoHideAnimPresenter* m_hideAnim;
	MxS16 m_startupTicks;
	MxBool m_worldStarted;
	undefined m_unk0xf7;
};

// clang-format off

// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::~_Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::iterator::_Inc


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::erase


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Erase


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Init


// list<LegoROI *,allocator<LegoROI *> >::~list<LegoROI *,allocator<LegoROI *> >


// List<LegoROI *>::~List<LegoROI *>


// list<LegoROI *,allocator<LegoROI *> >::_Buynode


// set<MxCore *,CoreSetCompare,allocator<MxCore *> >::~set<MxCore *,CoreSetCompare,allocator<MxCore *> >


// Set<MxCore *,CoreSetCompare>::~Set<MxCore *,CoreSetCompare>


// list<LegoROI *,allocator<LegoROI *> >::erase


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::insert


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::iterator::_Dec


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::lower_bound


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Buynode


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Insert


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Lrotate


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Rrotate


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::find


// ?_Construct@@YAXPAPAVMxCore@@ABQAV1@@Z


// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Nil
// clang-format on

#endif // LEGOWORLD_H
