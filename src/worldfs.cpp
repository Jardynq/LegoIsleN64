#include "worldfs.h"

#include "debug.h"
#include "t3d/t3dmodel.h"

#include <cstdlib>
#include <string>
#include <t3d/t3d.h>

const char* worldfs_names[] = {"bldd",   "bldh",  "bldj",  "hosp",      "bldr",
							   "police", "gmain", "icube", "ielev",     "iisle",
							   "racc",   "imain", "ireg",  "racj",      "act1",
							   "act2",   "act3",  "test",  "testworld", "isle"};

MxResult
worldfs_open_t3dm(WorldfsT3dmRef& ref, T3DModel** model, float lod_percent) {
	if (ref.lod_count == 0) {
		return FAILURE;
	}
	if (lod_percent < 0.0f) {
		lod_percent = 0.0f;
	} else if (lod_percent > 1.0f) {
		lod_percent = 1.0f;
	}

	int lod = (int) (ref.lod_count * lod_percent);
	auto path = std::string("rom:/data/") + ref.roiname + "_" +
				std::to_string(lod) + ".t3dm";
	*model = t3d_model_load(path.c_str());
	if (*model == nullptr) {
		return FAILURE;
	}
	return SUCCESS;
}

const char* read_string(FILE* file) {
	u16 length = 0;
	fread(&length, sizeof(length), 1, file);
	char* str = (char*) malloc(length + 1);
	fread(str, sizeof(char), length, file);
	str[length] = 0;
	return str;
}
WorldfsWorld* worldfs_read_world(WorldType type) {
	const char* name = worldfs_names[(u8) type];
	FILE* file =
		asset_fopen((std::string("rom:/data/index_") + name).c_str(), nullptr);
	if (!file) {
		return nullptr;
	}

	WorldfsWorld* world = (WorldfsWorld*) malloc(sizeof(WorldfsWorld));
	world->name = worldfs_names[(u8) type];

	fread(&world->num_parts, sizeof(world->num_parts), 1, file);
	world->parts = new WorldfsT3dmRef[world->num_parts];
	for (u32 i = 0; i < world->num_parts; ++i) {
		auto& part = world->parts[i];
		part.roiname = read_string(file);
		fread(&part.lod_count, sizeof(part.lod_count), 1, file);
	}

	fread(&world->num_models, sizeof(world->num_models), 1, file);
	world->models = new WorldfsModelRef*[world->num_models];
	for (u32 i = 0; i < world->num_models; ++i) {
		auto model = new WorldfsModelRef();
		world->models[i] = model;

		model->name = read_string(file);
		model->presenterName = read_string(file);

		fread(&model->center[0], sizeof(model->center[0]), 1, file);
		fread(&model->center[1], sizeof(model->center[1]), 1, file);
		fread(&model->center[2], sizeof(model->center[2]), 1, file);

		fread(&model->location[0], sizeof(model->location[0]), 1, file);
		fread(&model->location[1], sizeof(model->location[1]), 1, file);
		fread(&model->location[2], sizeof(model->location[2]), 1, file);

		fread(&model->direction[0], sizeof(model->direction[0]), 1, file);
		fread(&model->direction[1], sizeof(model->direction[1]), 1, file);
		fread(&model->direction[2], sizeof(model->direction[2]), 1, file);

		fread(&model->up[0], sizeof(model->up[0]), 1, file);
		fread(&model->up[1], sizeof(model->up[1]), 1, file);
		fread(&model->up[2], sizeof(model->up[2]), 1, file);

		fread(&model->isVisible, sizeof(model->isVisible), 1, file);

		fread(&model->num_components, sizeof(model->num_components), 1, file);
		model->components = new WorldfsT3dmRef[model->num_components];
		for (u32 i = 0; i < model->num_components; ++i) {
			auto& comp = model->components[i];
			comp.roiname = read_string(file);
			fread(&comp.lod_count, sizeof(comp.lod_count), 1, file);
		}
	}

	fclose(file);
	return world;
}