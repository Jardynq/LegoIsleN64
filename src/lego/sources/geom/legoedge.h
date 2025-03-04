#ifndef __LEGOEDGE_H
#define __LEGOEDGE_H

class LegoWEEdge;
class Vector3;

struct LegoEdge {
	LegoEdge();
	virtual ~LegoEdge();

	LegoEdge* GetClockwiseEdge(LegoWEEdge& p_face);
	LegoEdge* GetCounterclockwiseEdge(LegoWEEdge& p_face);
	Vector3* CWVertex(LegoWEEdge& p_face);
	Vector3* CCWVertex(LegoWEEdge& p_face);

	LegoResult FUN_1002ddc0(LegoWEEdge& p_face, Vector3& p_point);

	LegoWEEdge* GetFaceA() { return m_faceA; }

	LegoWEEdge* GetFaceB() { return m_faceB; }

	Vector3* GetPointA() { return m_pointA; }

	Vector3* GetPointB() { return m_pointB; }

	// LegoEdge::`scalar deleting destructor'

	LegoWEEdge* m_faceA;
	LegoWEEdge* m_faceB;
	LegoEdge* m_ccwA;
	LegoEdge* m_cwA;
	LegoEdge* m_ccwB;
	LegoEdge* m_cwB;
	Vector3* m_pointA;
	Vector3* m_pointB;
};

#endif // __LEGOEDGE_H
