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

// #include "mx_ds_action.h"
// #include "mx_ds_object.h"

LegofsIndexIndex legofs_index;

bool check_index(const std::string& si, u16 index, LegofsType type) {
	if (index >= legofs_index.si_to_index[si]->nodes.size()) {
		return false;
	}
	auto node = legofs_index.si_to_index[si]->nodes[index];
	return node.type == type;
}

void legofs_read_index_node(LegofsNode* node, FILE* file);
MxResult legofs_init(const std::string& si) {
	if (legofs_index.si_to_index.find(si) != legofs_index.si_to_index.end()) {
		return SUCCESS;
	}

	FILE* file = asset_fopen((si + "/index").c_str(), nullptr);
	if (!file) {
		return FAILURE;
	}

	LegofsIndex index;
	u16 size = 0;
	fread(&size, sizeof(size), 1, file);
	index.nodes.resize(size);
	for (u32 i = 0; i < size; ++i) {
		legofs_read_index_node(&index.nodes[i], file);
	}
	fclose(file);

	for (LegofsNode& node : index.nodes) {
		for (u32 i = 0; i < node.children.size(); ++i) {
			u16 child_index = (u16) (usize) node.children[i];
			node.children[i] = &index.nodes[child_index];
		}

		// index.name_to_node[node.name] = &index.nodes[node.index];
		// index.path_to_node[node.path] = &index.nodes[node.index];
	}

	legofs_index.indices.push_back(index);
	legofs_index.si_to_index[si] = &legofs_index.indices.back();

	return SUCCESS;
}

const LegofsIndex& legofs_get_index(const std::string& si) {
	legofs_init(si);
	return *legofs_index.si_to_index.at(si);
}

MxResult legofs_open_video(const std::string& si, u16 index, mpeg2_t** video) {
	legofs_init(si);
	if (!check_index(si, index, LegofsType::Flic) &&
		!check_index(si, index, LegofsType::Smacker)) {
		return FAILURE;
	}

	auto path = si + "/" + std::to_string(index) + ".m1v";
	*video = mpeg2_open(path.c_str());
	if (!*video) {
		return FAILURE;
	}
	return SUCCESS;
}

MxResult legofs_open_audio(const std::string& si, u16 index, wav64_t* audio) {
	legofs_init(si);
	if (!check_index(si, index, LegofsType::Wave)) {
		return FAILURE;
	}

	auto path = si + "/" + std::to_string(index) + ".wav64";
	FILE* file = fopen(path.c_str(), "r");
	if (!file) {
		return FAILURE;
	}
	fclose(file);
	wav64_open(audio, path.c_str());
	return SUCCESS;
}

MxResult
legofs_open_sprite(const std::string& si, u16 index, sprite_t** sprite) {
	legofs_init(si);
	if (!check_index(si, index, LegofsType::Bitmap)) {
		return FAILURE;
	}

	auto path = si + "/" + std::to_string(index) + ".sprite";
	*sprite = sprite_load(path.c_str());
	if (*sprite == nullptr) {
		return FAILURE;
	}
	return SUCCESS;
}

const LegofsNode& legofs_index_node(const std::string& si, u16 index) {
	legofs_init(si);
	return legofs_index.si_to_index[si]->nodes[index];
}

const LegofsNode&
legofs_name_node(const std::string& si, const std::string& name) {
	legofs_init(si);
	return *legofs_index.si_to_index[si]->name_to_node.at(name);
}

const LegofsNode&
legofs_path_node(const std::string& si, const std::string& path) {
	legofs_init(si);
	return *legofs_index.si_to_index[si]->path_to_node.at(path);
}

void legofs_read_index_node(LegofsNode* node, FILE* file) {
	fread(&node->type, sizeof(node->type), 1, file);
	fread(&node->index, sizeof(node->index), 1, file);
	if (node->type == LegofsType::Null) {
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

MxDSObject* legofs_create_object(const MxAtomId& atom, u16 index) {
	return nullptr;
}
MxDSAction* legofs_create_action(const MxAtomId& atom, u16 index) {
	return nullptr;
}
