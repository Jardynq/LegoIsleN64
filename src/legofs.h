#pragma once

#include <string>
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
	Path = 10,
	Texture = 11,
	Model = 12,
};

struct LegofsNode {
	LegofsType type = LegofsType::Null;
	unsigned short index = 0;
	const char* name = nullptr;
	const char* path = nullptr;
	const char* presenter = nullptr;
	unsigned short start_time = 0;
	unsigned short duration = 0;
	unsigned char loops = 0;
	unsigned char flags = 0;
	float location[3] = {0.0f, 0.0f, 0.0f};
	float up[3] = {0.0f, 0.0f, 0.0f};
	float direction[3] = {0.0f, 0.0f, 0.0f};
	std::vector<unsigned char> extra;
	std::vector<const LegofsNode*> children;
};

struct LegofsIndex {
	std::string path;
	std::vector<LegofsNode> nodes;
	// TODO what happens when two nodes hare a path or name?
	// i.e. empty string
	std::unordered_map<std::string, const LegofsNode*> name_to_node;
	std::unordered_map<std::string, const LegofsNode*> path_to_node;
};

struct LegofsIndexIndex {
	std::vector<LegofsIndex> indices;
	std::unordered_map<std::string, const LegofsIndex*> si_to_index;
};

const LegofsIndex& legofs_get_index(const std::string& si);

const LegofsNode& legofs_index_node(const std::string& si, u16 index);
const LegofsNode&
legofs_name_node(const std::string& si, const std::string& name);
const LegofsNode&
legofs_path_node(const std::string& si, const std::string& path);

MxResult legofs_open_audio(const std::string& si, u16 index, wav64_t* audio);
MxResult legofs_open_video(const std::string& si, u16 index, mpeg2_t** video);
MxResult
legofs_open_sprite(const std::string& si, u16 index, sprite_t** sprite);

class MxAtomId;
struct MxDSObject;
struct MxDSAction;
MxDSObject* legofs_create_object(MxAtomId atom, u16 index);
MxDSAction* legofs_create_action(MxAtomId atom, u16 index);
