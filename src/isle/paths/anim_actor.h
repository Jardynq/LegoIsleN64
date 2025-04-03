#pragma once

#include "path_actor.h"

class LegoAnim;

struct LegoAnimActorStruct {
	LegoAnimActorStruct(
		float p_unk0x00,
		LegoAnim* p_AnimTreePtr,
		LegoROI** p_roiMap,
		MxU32 p_numROIs
	);
	~LegoAnimActorStruct();

	float GetDuration();

	float GetUnknown0x00() { return m_unk0x00; }

	LegoAnim* GetAnimTreePtr() { return m_AnimTreePtr; }

	LegoROI** GetROIMap() { return m_roiMap; }

	// TODO: Possibly private
	float m_unk0x00;
	LegoAnim* m_AnimTreePtr;
	LegoROI** m_roiMap;
	MxU32 m_numROIs;
	vector<undefined*> m_unk0x10;
};

class LegoAnimActor : public virtual LegoPathActor {
public:
	LegoAnimActor() { m_curAnim = -1; }

	~LegoAnimActor() override;

	void ParseAction(char* p_extra) override;
	void SetWorldSpeed(MxFloat p_worldSpeed) override;
	void Animate(float p_time) override;
	void VTable0x74(Matrix4& p_transform) override;

	virtual MxResult FUN_1001c1f0(float& p_und);
	virtual MxResult FUN_1001c360(float, Matrix4& p_transform);
	virtual MxResult FUN_1001c450(
		LegoAnim* p_AnimTreePtr,
		float p_unk0x00,
		LegoROI** p_roiMap,
		MxU32 p_numROIs
	);
	virtual void ClearMaps();

	static const char* ClassName() { return "LegoAnimActor"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoAnimActor::ClassName()) ||
			   LegoPathActor::IsA(p_name);
	}

	// LegoAnimActor::`scalar deleting destructor'

protected:
	vector<LegoAnimActorStruct*> m_animMaps;
	MxS16 m_curAnim;
};

// clang-format off

// LegoAnimActor::`vbtable'


// vector<LegoAnimActorStruct *,allocator<LegoAnimActorStruct *> >::~vector<LegoAnimActorStruct *,allocator<LegoAnimActorStruct *> >


// Vector<LegoAnimActorStruct *>::~Vector<LegoAnimActorStruct *>



// LegoAnimActor::`vbase destructor'


// vector<unsigned char *,allocator<unsigned char *> >::~vector<unsigned char *,allocator<unsigned char *> >


// Vector<unsigned char *>::~Vector<unsigned char *>



// vector<LegoAnimActorStruct *,allocator<LegoAnimActorStruct *> >::size


// vector<LegoAnimActorStruct *,allocator<LegoAnimActorStruct *> >::operator[]


// vector<LegoAnimActorStruct *,allocator<LegoAnimActorStruct *> >::_Destroy


// uninitialized_fill_n


// ?uninitialized_copy@@YAPAPAULegoAnimActorStruct@@PAPAU1@00@Z
// clang-format on

