#ifndef LEGOLOCATIONS_H
#define LEGOLOCATIONS_H

struct LegoLocation {

	struct Boundary {
		const char* m_name;
		MxS32 m_src;
		float m_srcScale;
		MxS32 m_dest;
		float m_destScale;
		MxBool m_unk0x10;
	};

	MxU32 m_index;
	const char* m_name;
	float m_position[3];
	float m_direction[3];
	float m_up[3];
	Boundary m_boundaryA;
	Boundary m_boundaryB;
	MxBool m_unk0x5c;
	MxU8 m_frequency;
};

extern LegoLocation g_locations[70];

#endif // LEGOLOCATIONS_H
