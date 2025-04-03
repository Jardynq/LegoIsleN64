#pragma once

#include <unordered_map>
#include <vector>

enum class LegofsType : u8 {
	Null = 0,
	Bitmap = 1,
	Wave = 2,
	Smacker = 3,
	Object = 4,
	Flic = 5,
	Presenter = 6,
	Animation = 7,
	World = 8,
	Event = 9,
};

struct LegofsNode {
	LegofsType type;
	unsigned short index;
	const char* name;
	const char* path;
	const char* presenter;
	unsigned short start_time;
	unsigned short duration;
	unsigned char loops;
	unsigned char flags;
	float location[3];
	float up[3];
	float direction[3];
	std::vector<unsigned char> extra;
	std::vector<const LegofsNode*> children;
};

struct LegofsIndex {
	std::vector<LegofsNode> nodes;
	// TODO what happens when two nodes hare a path or name?
	// i.e. empty string
	std::unordered_map<const char*, const LegofsNode*> name_to_node;
	std::unordered_map<const char*, const LegofsNode*> path_to_node;
};

extern LegofsIndex legofs_index;

const LegofsNode& legofs_index_node(u16 index);
const LegofsNode& legofs_name_node(const char* name);
const LegofsNode& legofs_path_node(const char* path);

void legofs_init();
const u8* legofs_read(u16 index, i32* size);
MxResult legofs_open_audio(u16 index, wav64_t* audio);
MxResult legofs_open_video(u16 index, mpeg2_t** video);
MxResult legofs_open_sprite(u16 index, sprite_t** sprite);

