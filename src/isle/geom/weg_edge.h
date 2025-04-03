#pragma once

class LegoPathStruct;

#include "we_edge.h"

// This struct might have been defined elsewhere (legopathstruct.h?).
// Must be defined before the inclusion of Mx4DPointFloat for correct order

struct PathWithTrigger {

	PathWithTrigger() {
		m_pathStruct = NULL;
		m_data = 0;
		m_unk0x08 = 0.0f;
	}

	LegoPathStruct* m_pathStruct;
	unsigned int m_data;
	float m_unk0x08;
};

#include "mx_geometry_3d.h"
#include "mx_geometry_4d.h"

// might be a struct with public members

class LegoWEGEdge : public LegoWEEdge {
public:
	enum { c_bit1 = 0x01, c_bit2 = 0x02, c_bit3 = 0x04, c_bit5 = 0x10 };

	LegoWEGEdge();
	~LegoWEGEdge() override;

	LegoS32 VTable0x04() override;

	LegoU32 GetFlag0x10() { return m_flags & c_bit5 ? FALSE : TRUE; }

	// TODO: Other BETA10 reference at 0x1001c9e0, not sure what is going on

	Mx4DPointFloat* GetUnknown0x14() { return &m_unk0x14; }

	Mx4DPointFloat* GetEdgeNormal(int index) { return &m_edgeNormals[index]; }

	const LegoChar* GetName() { return m_name; }

	void SetFlag0x10(LegoU32 p_disable) {
		if (p_disable) {
			m_flags &= ~c_bit5;
		} else {
			m_flags |= c_bit5;
		}
	}

	LegoU8 GetMask0x03() { return m_flags & (c_bit1 | c_bit2); }

	// LegoWEGEdge::`scalar deleting destructor'

	friend class LegoPathController;

protected:
	LegoS32 FUN_1009aea0();

	LegoU8 m_flags;
	LegoU8 m_unk0x0d;
	LegoChar* m_name;
	Mx4DPointFloat m_unk0x14;
	Mx4DPointFloat* m_edgeNormals;
	Mx3DPointFloat m_unk0x30;
	float m_unk0x44;
	LegoU8 m_numTriggers;
	PathWithTrigger* m_pathTrigger;
	Mx3DPointFloat* m_unk0x50;
};

