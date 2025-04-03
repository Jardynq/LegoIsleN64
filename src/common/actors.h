#ifndef LEGOACTORS_H
#define LEGOACTORS_H

class LegoExtraActor;
class LegoROI;

struct LegoActorInfo {

	struct Part {
		MxU8* m_unk0x00;
		const char** m_unk0x04;
		MxU8 m_unk0x08;
		MxU8* m_unk0x0c;
		const char** m_unk0x10;
		MxU8 m_unk0x14;
	};

	const char* m_name;
	LegoROI* m_roi;
	LegoExtraActor* m_actor;
	MxS32 m_sound;
	MxS32 m_move;
	MxU8 m_mood;
	Part m_parts[10];
};

struct LegoActorLOD {
	enum { c_flag1 = 0x01, c_flag2 = 0x02 };

	const char* m_name;
	const char* m_parentName;
	MxU32 m_flags;
	float m_boundingSphere[4];
	float m_boundingBox[6];
	float m_position[3];
	float m_direction[3];
	float m_up[3];
};

enum LegoActorLODs {
	c_topLOD,
	c_bodyLOD,
	c_infohatLOD,
	c_infogronLOD,
	c_headLOD,
	c_armlftLOD,
	c_armrtLOD,
	c_clawlftLOD,
	c_clawrtLOD,
	c_leglftLOD,
	c_legrtLOD
};

enum LegoActorParts {
	c_bodyPart,
	c_infohatPart,
	c_infogronPart,
	c_headPart,
	c_armlftPart,
	c_armrtPart,
	c_clawlftPart,
	c_clawrtPart,
	c_leglftPart,
	c_legrtPart
};

extern LegoActorInfo g_actorInfoInit[66];
extern LegoActorLOD g_actorLODs[11];

#endif // LEGOACTORS_H
