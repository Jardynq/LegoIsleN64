#include "edge.h"

#include "assert.h"

LegoEdge::LegoEdge() {
	m_faceA = NULL;
	m_faceB = NULL;
	m_ccwA = NULL;
	m_cwA = NULL;
	m_ccwB = NULL;
	m_cwB = NULL;
	m_pointA = NULL;
	m_pointB = NULL;
}

LegoEdge::~LegoEdge() {
}

LegoEdge* LegoEdge::GetClockwiseEdge(LegoWEEdge& p_face) {
	if (&p_face == m_faceA) {
		return m_cwA;
	} else if (&p_face == m_faceB) {
		return m_cwB;
	} else {
		return NULL;
	}
}

LegoEdge* LegoEdge::GetCounterclockwiseEdge(LegoWEEdge& p_face) {
	if (&p_face == m_faceA) {
		return m_ccwA;
	} else if (&p_face == m_faceB) {
		return m_ccwB;
	} else {
		return NULL;
	}
}

Vector3* LegoEdge::CWVertex(LegoWEEdge& p_face) {
	if (m_faceA == &p_face) {
		return m_pointB;
	} else {
		assert(m_faceB == &p_face);
		return m_pointA;
	}
}

Vector3* LegoEdge::CCWVertex(LegoWEEdge& p_face) {
	if (m_faceB == &p_face) {
		return m_pointB;
	} else {
		assert(m_faceA == &p_face);
		return m_pointA;
	}
}
