#ifndef LEGOANIMPRESENTER_H
#define LEGOANIMPRESENTER_H

#include "legoroilist.h"
#include "mxatom.h"
#include "mxvideopresenter.h"

class LegoAnim;
class LegoWorld;
class LegoPathBoundary;
class MxMatrix;
class Vector3;

struct LegoAnimStructComparator {
	MxBool operator()(const char* const& p_a, const char* const& p_b) const {
		return strcmp(p_a, p_b) < 0;
	}
};

struct LegoAnimSubstComparator {
	MxBool operator()(const char* const& p_a, const char* const& p_b) const {
		return strcmp(p_a, p_b) < 0;
	}
};

struct LegoAnimStruct {
	LegoROI* m_roi;
	MxU32 m_index;
};

typedef map<const char*, LegoAnimStruct, LegoAnimStructComparator>
	LegoAnimStructMap;
typedef map<const char*, const char*, LegoAnimSubstComparator> LegoAnimSubstMap;

class LegoAnimPresenter : public MxVideoPresenter {
public:
	enum { c_hideOnStop = 0x01, c_mustSucceed = 0x02 };

	LegoAnimPresenter();
	~LegoAnimPresenter() override;

	static const char* HandlerClassName() { return "LegoAnimPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoAnimPresenter::ClassName()) ||
			   MxVideoPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	void StreamingTickle() override;
	void DoneTickle() override;
	void ParseExtra() override;
	MxResult AddToManager() override;
	void Destroy() override;
	MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action)
		override;
	void EndAction() override;
	void PutFrame() override;
	virtual MxResult CreateAnim(MxStreamChunk* p_chunk);
	virtual void VTable0x8c();
	virtual void VTable0x90();
	virtual MxU32 VTable0x94(
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	);
	virtual MxResult VTable0x98(LegoPathBoundary* p_boundary);

	virtual LegoROI** GetROIMap(MxU32& p_roiMapSize) {
		p_roiMapSize = m_roiMapSize;
		return m_roiMap;
	}

	virtual void VTable0xa0(Matrix4& p_matrix);

	MxResult FUN_1006afc0(MxMatrix*& p_matrix, float p_und);
	MxResult FUN_1006b140(LegoROI* p_roi);
	void FUN_1006c7a0();
	const char* GetActionObjectName();

	void SetCurrentWorld(LegoWorld* p_currentWorld) {
		m_currentWorld = p_currentWorld;
	}
	void SetUnknown0x0cTo1() { m_unk0x9c = 1; }
	void SetUnknown0xa0(MxMatrix* p_unk0xa0) { m_unk0xa0 = p_unk0xa0; }

	LegoAnim* GetAnimation() { return m_anim; }

protected:
	void Init();
	void Destroy(MxBool p_fromDestructor);
	LegoChar* FUN_10069150(const LegoChar* p_und1);
	void FUN_100692b0();
	void FUN_100695c0();
	LegoChar* FUN_100697c0(const LegoChar* p_und1, const LegoChar* p_und2);
	LegoBool FUN_100698b0(const CompoundObject& p_rois, const LegoChar* p_und2);
	LegoROI* FUN_100699e0(const LegoChar* p_und);
	void FUN_10069b10();
	void FUN_1006a3c0(
		LegoAnimStructMap& p_map,
		LegoTreeNode* p_node,
		LegoROI* p_roi
	);
	void FUN_1006a4f0(
		LegoAnimStructMap& p_map,
		LegoAnimNodeData* p_data,
		const LegoChar* p_und,
		LegoROI* p_roi
	);
	void FUN_1006aa60();
	void FUN_1006ab70();
	LegoBool FUN_1006aba0();
	MxBool FUN_1006abb0(LegoTreeNode* p_node, LegoROI* p_roi);
	void SubstituteVariables();
	void FUN_1006b900(LegoAnim* p_anim, MxLong p_time, Matrix4* p_matrix);
	void FUN_1006b9a0(LegoAnim* p_anim, MxLong p_time, Matrix4* p_matrix);
	void FUN_1006c8a0(MxBool p_bool);

	LegoAnim* m_anim;
	LegoROI** m_roiMap;
	MxU32 m_roiMapSize;
	LegoROIList* m_unk0x70;
	LegoROIList* m_unk0x74;
	MxMatrix* m_unk0x78;
	MxU32 m_flags;
	LegoWorld* m_currentWorld;
	MxAtomId m_worldAtom;
	MxS32 m_worldId;
	LegoROI** m_unk0x8c;
	char** m_unk0x90;
	MxU8 m_unk0x94;
	MxBool m_unk0x95;
	MxBool m_unk0x96;
	undefined m_unk0x97;
	LegoAnimSubstMap* m_substMap;
	MxS16 m_unk0x9c;
	MxMatrix* m_unk0xa0;

public:
	float m_unk0xa4;
	Mx3DPointFloat m_unk0xa8;
};

// clang-format off

// LegoAnimPresenter::`scalar deleting destructor'


// map<char const *,char const *,LegoAnimSubstComparator,allocator<char const *> >::~map<char const *,char const *,LegoAnimSubstComparator,allocator<char const *> >


// _Tree<char const *,pair<char const * const,char const *>,map<char const *,char const *,LegoAnimSubstComparator,allocator<char const *> >::_Kfn,LegoAnimSubstComparator,allocator<char const *> >::~_Tree<char const *,pair<char const * const,char const *>,map


// _Tree<char const *,pair<char const * const,char const *>,map<char const *,char const *,LegoAnimSubstComparator,allocator<char const *> >::_Kfn,LegoAnimSubstComparator,allocator<char const *> >::iterator::_Inc


// _Tree<char const *,pair<char const * const,char const *>,map<char const *,char const *,LegoAnimSubstComparator,allocator<char const *> >::_Kfn,LegoAnimSubstComparator,allocator<char const *> >::erase


// _Tree<char const *,pair<char const * const,char const *>,map<char const *,char const *,LegoAnimSubstComparator,allocator<char const *> >::_Kfn,LegoAnimSubstComparator,allocator<char const *> >::_Erase


// _Tree<char const *,pair<char const * const,LegoAnimStruct>,map<char const *,LegoAnimStruct,LegoAnimStructComparator,allocator<LegoAnimStruct> >::_Kfn,LegoAnimStructComparator,allocator<LegoAnimStruct> >::~_Tree<char const *,pair<char const * const,LegoAni


// _Tree<char const *,pair<char const * const,LegoAnimStruct>,map<char const *,LegoAnimStruct,LegoAnimStructComparator,allocator<LegoAnimStruct> >::_Kfn,LegoAnimStructComparator,allocator<LegoAnimStruct> >::iterator::_Inc


// _Tree<char const *,pair<char const * const,LegoAnimStruct>,map<char const *,LegoAnimStruct,LegoAnimStructComparator,allocator<LegoAnimStruct> >::_Kfn,LegoAnimStructComparator,allocator<LegoAnimStruct> >::erase


// _Tree<char const *,pair<char const * const,LegoAnimStruct>,map<char const *,LegoAnimStruct,LegoAnimStructComparator,allocator<LegoAnimStruct> >::_Kfn,LegoAnimStructComparator,allocator<LegoAnimStruct> >::_Erase


// Map<char const *,LegoAnimStruct,LegoAnimStructComparator>::~Map<char const *,LegoAnimStruct,LegoAnimStructComparator>


// map<char const *,LegoAnimStruct,LegoAnimStructComparator,allocator<LegoAnimStruct> >::~map<char const *,LegoAnimStruct,LegoAnimStructComparator,allocator<LegoAnimStruct> >


// _Tree<char const *,pair<char const * const,LegoAnimStruct>,map<char const *,LegoAnimStruct,LegoAnimStructComparator,allocator<LegoAnimStruct> >::_Kfn,LegoAnimStructComparator,allocator<LegoAnimStruct> >::iterator::_Dec


// _Tree<char const *,pair<char const * const,LegoAnimStruct>,map<char const *,LegoAnimStruct,LegoAnimStructComparator,allocator<LegoAnimStruct> >::_Kfn,LegoAnimStructComparator,allocator<LegoAnimStruct> >::_Insert


// _Tree<char const *,pair<char const * const,char const *>,map<char const *,char const *,LegoAnimSubstComparator,allocator<char const *> >::_Kfn,LegoAnimSubstComparator,allocator<char const *> >::iterator::_Dec


// _Tree<char const *,pair<char const * const,char const *>,map<char const *,char const *,LegoAnimSubstComparator,allocator<char const *> >::_Kfn,LegoAnimSubstComparator,allocator<char const *> >::_Insert


// list<char *,allocator<char *> >::~list<char *,allocator<char *> >


// List<char *>::~List<char *>


// _Tree<char const *,pair<char const * const,char const *>,map<char const *,char const *,LegoAnimSubstComparator,allocator<char const *> >::_Kfn,LegoAnimSubstComparator,allocator<char const *> >::_Nil


// _Tree<char const *,pair<char const * const,LegoAnimStruct>,map<char const *,LegoAnimStruct,LegoAnimStructComparator,allocator<LegoAnimStruct> >::_Kfn,LegoAnimStructComparator,allocator<LegoAnimStruct> >::_Nil
// clang-format on

#endif // LEGOANIMPRESENTER_H
