#ifndef LEGOPATHEDGECONTAINER_H
#define LEGOPATHEDGECONTAINER_H

#include "mx_geometry_3d.h"

class LegoPathBoundary;
struct LegoPathCtrlEdge;

struct LegoBoundaryEdge {
	LegoBoundaryEdge() {}

	LegoBoundaryEdge(LegoPathCtrlEdge* p_edge, LegoPathBoundary* p_boundary) {
		m_edge = p_edge;
		m_boundary = p_boundary;
	}

	LegoPathCtrlEdge* m_edge;
	LegoPathBoundary* m_boundary;
	int operator==(LegoBoundaryEdge) const { return 0; }
	int operator<(LegoBoundaryEdge) const { return 0; }
};

struct LegoBEWithFloat {
	LegoBEWithFloat() {
		m_edge = NULL;
		m_boundary = NULL;
		m_next = NULL;
		m_unk0x0c = 0.0f;
	}

	LegoBEWithFloat(
		LegoPathCtrlEdge* p_edge,
		LegoPathBoundary* p_boundary,
		MxFloat p_unk0x0c
	) {
		m_edge = p_edge;
		m_boundary = p_boundary;
		m_next = NULL;
		m_unk0x0c = p_unk0x0c;
	}

	LegoBEWithFloat(
		LegoPathCtrlEdge* p_edge,
		LegoPathBoundary* p_boundary,
		LegoBEWithFloat* p_next,
		MxFloat p_unk0x0c
	) {
		m_edge = p_edge;
		m_boundary = p_boundary;
		m_next = p_next;
		m_unk0x0c = p_unk0x0c;
	}

	LegoPathCtrlEdge* m_edge;
	LegoPathBoundary* m_boundary;
	LegoBEWithFloat* m_next;
	MxFloat m_unk0x0c;
	int operator==(LegoBEWithFloat) const { return 0; }
	int operator<(LegoBEWithFloat) const { return 0; }
};

struct LegoBEWithFloatComparator {

	bool
	operator()(LegoBEWithFloat* const& p_a, LegoBEWithFloat* const& p_b) const {
		return p_a->m_unk0x0c < p_b->m_unk0x0c;
	}
};

typedef multiset<LegoBEWithFloat*, LegoBEWithFloatComparator>
	LegoBEWithFloatSet;

struct LegoPathEdgeContainer : public list<LegoBoundaryEdge> {
	enum { c_bit1 = 0x01 };

	LegoPathEdgeContainer() {
		m_boundary = NULL;
		m_flags = 0;
	}

	void SetBit1(MxU32 p_set) {
		if (p_set) {
			m_flags |= c_bit1;
		} else {
			m_flags &= ~c_bit1;
		}
	}

	MxU32 GetBit1() { return m_flags & c_bit1; }

	Mx3DPointFloat m_position;
	Mx3DPointFloat m_direction;
	LegoPathBoundary* m_boundary;
	MxU8 m_flags;
};

#endif // LEGOPATHEDGECONTAINER_H
