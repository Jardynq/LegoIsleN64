#ifndef __LEGOWEEDGE_H
#define __LEGOWEEDGE_H

struct LegoUnknown100db7f4;

// might be a struct with public members

class LegoWEEdge {
public:
	LegoWEEdge();
	virtual ~LegoWEEdge();

	virtual LegoS32 VTable0x04();

	LegoU8 GetNumEdges() { return m_numEdges; }

	LegoUnknown100db7f4** GetEdges() { return m_edges; }

	LegoU32 IsEqual(LegoWEEdge* p_other) { return this == p_other; }

	void SetEdges(LegoUnknown100db7f4** p_edges, LegoU8 p_numEdges) {
		m_edges = p_edges;
		m_numEdges = p_numEdges;
	}

	// LegoWEEdge::`scalar deleting destructor'

protected:
	LegoU8 m_numEdges;
	LegoUnknown100db7f4** m_edges;
};

#endif // __LEGOWEEDGE_H
