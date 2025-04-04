#include "legofs.h"

#include "asset.h"
#include "mpeg2.h"
#include "sprite.h"
#include "wav64.h"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>

LegofsIndex legofs_index;

const std::string LEGOFS_SCRIPT_ROOT =
	std::string("rom:/scripts/infocntr/infomain.si/");

void legofs_read_index_node(LegofsNode* node, FILE* file);
void legofs_init() {
	FILE* file = asset_fopen((LEGOFS_SCRIPT_ROOT + "index").c_str(), nullptr);
	if (!file) {
		return;
	}

	u16 size = 0;
	fread(&size, sizeof(size), 1, file);
	legofs_index.nodes.resize(size);
	for (u32 i = 0; i < size; ++i) {
		legofs_read_index_node(&legofs_index.nodes[i], file);
	}
	fclose(file);

	for (LegofsNode& node : legofs_index.nodes) {
		for (u32 i = 0; i < node.children.size(); ++i) {
			u16 child_index = (u16) (usize) node.children[i];
			node.children[i] = &legofs_index.nodes[child_index];
		}

		legofs_index.name_to_node[node.name] = &legofs_index.nodes[node.index];
		legofs_index.path_to_node[node.path] = &legofs_index.nodes[node.index];
	}
}

const u8* legofs_read(u16 index, i32* size) {
	auto path = LEGOFS_SCRIPT_ROOT + std::to_string(index);

	FILE* file = asset_fopen(path.c_str(), size);
	if (!file) {
		return nullptr;
	}

	u8* buffer = new u8[*size];
	fread(buffer, *size, 1, file);
	fclose(file);
	return buffer;
}

FILE* legofs_open(u16 index, i32* size, const char* ext) {
	auto path = LEGOFS_SCRIPT_ROOT + std::to_string(index);
	if (ext != nullptr) {
		path += ext;
	}

	FILE* file = asset_fopen(path.c_str(), size);
	if (!file) {
		return nullptr;
	}
	return file;
}

MxResult legofs_open_video(u16 index, mpeg2_t** video) {
	auto path = LEGOFS_SCRIPT_ROOT + std::to_string(index) + ".m1v";
	*video = mpeg2_open(path.c_str());
	if (!*video) {
		return FAILURE;
	}
	return SUCCESS;
}

MxResult legofs_open_audio(u16 index, wav64_t* audio) {
	auto path = LEGOFS_SCRIPT_ROOT + std::to_string(index) + ".wav64";
	FILE* file = fopen(path.c_str(), "r");
	if (!file) {
		return FAILURE;
	}
	fclose(file);
	wav64_open(audio, path.c_str());
	return SUCCESS;
}

MxResult legofs_open_sprite(u16 index, sprite_t** sprite) {
	auto path = LEGOFS_SCRIPT_ROOT + std::to_string(index) + ".sprite";
	*sprite = sprite_load(path.c_str());
	if (*sprite == nullptr) {
		return FAILURE;
	}
	return SUCCESS;
}

const LegofsNode& legofs_index_node(u16 index) {
	return legofs_index.nodes[index];
}

const LegofsNode& legofs_name_node(const char* name) {
	return *legofs_index.name_to_node[name];
}

const LegofsNode& legofs_path_node(const char* path) {
	return *legofs_index.path_to_node[path];
}

void legofs_read_index_node(LegofsNode* node, FILE* file) {
	fread(&node->type, sizeof(node->type), 1, file);
	fread(&node->index, sizeof(node->index), 1, file);
	if (node->type == LegofsType::Null) {
		node->name = nullptr;
		node->path = nullptr;
		node->presenter = nullptr;
		node->direction[0] = 0.0f;
		node->direction[1] = 0.0f;
		node->direction[2] = 0.0f;
		node->up[0] = 0.0f;
		node->up[1] = 0.0f;
		node->up[2] = 0.0f;
		node->location[0] = 0.0f;
		node->location[1] = 0.0f;
		node->location[2] = 0.0f;
		node->start_time = 0;
		node->duration = 0;
		node->loops = 0;
		node->flags = 0;
		return;
	}

	u16 size = 0;
	fread(&size, sizeof(size), 1, file);
	node->name = (char*) malloc(size + 1);
	fread((char*) node->name, sizeof(char), size, file);
	((char*) node->name)[size] = 0;

	fread(&size, sizeof(size), 1, file);
	node->path = (char*) malloc(size + 1);
	fread((char*) node->path, sizeof(char), size, file);
	((char*) node->path)[size] = 0;

	fread(&size, sizeof(size), 1, file);
	node->presenter = (char*) malloc(size + 1);
	fread((char*) node->presenter, sizeof(char), size, file);
	((char*) node->presenter)[size] = 0;

	fread(&node->start_time, sizeof(node->start_time), 1, file);
	fread(&node->duration, sizeof(node->duration), 1, file);
	fread(&node->loops, sizeof(node->loops), 1, file);
	fread(&node->flags, sizeof(node->flags), 1, file);

	fread(&node->location[0], sizeof(node->location[0]), 1, file);
	fread(&node->location[1], sizeof(node->location[1]), 1, file);
	fread(&node->location[2], sizeof(node->location[2]), 1, file);

	fread(&node->direction[0], sizeof(node->direction[0]), 1, file);
	fread(&node->direction[1], sizeof(node->direction[1]), 1, file);
	fread(&node->direction[2], sizeof(node->direction[2]), 1, file);

	fread(&node->up[0], sizeof(node->up[0]), 1, file);
	fread(&node->up[1], sizeof(node->up[1]), 1, file);
	fread(&node->up[2], sizeof(node->up[2]), 1, file);

	u16 extra_size = 0;
	fread(&extra_size, sizeof(extra_size), 1, file);
	node->extra.resize(extra_size);
	for (u16 i = 0; i < extra_size; ++i) {
		fread(&node->extra[i], sizeof(node->extra[i]), 1, file);
	}

	u16 children_size = 0;
	fread(&children_size, sizeof(children_size), 1, file);
	node->children.resize(children_size);
	for (u16 i = 0; i < children_size; ++i) {
		node->children[i] = 0;
		fread(&node->children[i], sizeof(u16), 1, file);
	}
}
