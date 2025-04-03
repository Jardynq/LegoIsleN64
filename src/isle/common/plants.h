#pragma once

class LegoEntity;
class LegoPathBoundary;

struct LegoPlantInfo {
	// See LegoOmni::RegisterWorlds for IDs
	enum World {
		c_act1 = 1 << 0,
		c_imain = 1 << 1,
		c_ielev = 1 << 4,
		c_iisle = 1 << 5,
		c_act2 = 1 << 15,
		c_act3 = 1 << 16
	};

	enum Variant { e_flower = 0, e_tree, e_bush, e_palm };

	enum Color { e_white = 0, e_black, e_yellow, e_red, e_green };

	LegoEntity* m_entity;
	MxU32 m_worlds;
	MxU8 m_variant;
	MxU32 m_sound;
	MxU32 m_move;
	MxU8 m_mood;
	MxU8 m_color;
	MxS8 m_unk0x16;
	MxS8 m_initialUnk0x16;
	const char* m_name;
	undefined4 m_unk0x1c;
	float m_x;
	float m_y;
	float m_z;
	LegoPathBoundary* m_boundary;
	float m_position[3];
	float m_direction[3];
	float m_up[3];
};

extern LegoPlantInfo g_plantInfoInit[81];

