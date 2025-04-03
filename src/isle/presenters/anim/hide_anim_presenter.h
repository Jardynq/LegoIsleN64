#pragma once

#include "looping_anim_presenter.h"

class LegoPathBoundary;

struct LegoHideAnimStructComparator {
	MxBool operator()(const char* const& p_a, const char* const& p_b) const {
		return strcmp(p_a, p_b) < 0;
	}
};

struct LegoHideAnimStruct {
	LegoPathBoundary* m_boundary;
	MxU32 m_index;
};

typedef map<const char*, LegoHideAnimStruct, LegoHideAnimStructComparator>
	LegoHideAnimStructMap;

class LegoHideAnimPresenter : public LegoLoopingAnimPresenter {
public:
	LegoHideAnimPresenter();
	~LegoHideAnimPresenter() override;

	void VTable0x8c() override {}

	void VTable0x90() override {}

	static const char* HandlerClassName() { return "LegoHideAnimPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, ClassName()) || LegoAnimPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	MxResult AddToManager() override;
	void Destroy() override;
	void EndAction() override;
	void PutFrame() override;

	void FUN_1006db40(LegoTime p_time);

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);
	void FUN_1006db60(LegoTreeNode* p_node, LegoTime p_time);
	void FUN_1006dc10();
	void FUN_1006e3f0(LegoHideAnimStructMap& p_map, LegoTreeNode* p_node);
	void FUN_1006e470(
		LegoHideAnimStructMap& p_map,
		LegoAnimNodeData* p_data,
		const char* p_name,
		LegoPathBoundary* p_boundary
	);

	LegoPathBoundary** m_boundaryMap;
};

// clang-format off

// LegoHideAnimPresenter::`scalar deleting destructor'


// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::~_Tree<char const *,pair<ch


// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::iterator::_Inc


// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::erase


// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Erase


// Map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator>::~Map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator>


// map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::~map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >


// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::iterator::_Dec


// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Insert


// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Nil
// clang-format on

