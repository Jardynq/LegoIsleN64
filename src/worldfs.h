#pragma once

#include <vector>

#define WORLDFS_COUNT 20
enum class WorldType : u8 {
	bldd = 0,
	bldh = 1,
	bldj = 2,
	hosp = 3,
	bldr = 4,
	police = 5,
	gmain = 6,
	icube = 7,
	ielev = 8,
	iisle = 9,
	racc = 10,
	imain = 11,
	ireg = 12,
	racj = 13,
	act1 = 14,
	act2 = 15,
	act3 = 16,
	test = 17,
	testworld = 18,
	isle = 19,
};

struct WorldfsT3dmRef {
	const char* roiname = nullptr;
	u8 lod_count = 0;
};

struct WorldfsModelRef {
	const char* name = nullptr;
	const char* presenterName = nullptr;
	float center[3] = {0.0f, 0.0f, 0.0f};
	float location[3] = {0.0f, 0.0f, 0.0f};
	float direction[3] = {0.0f, 0.0f, 0.0f};
	float up[3] = {0.0f, 0.0f, 0.0f};
	bool isVisible = 0;
	u16 num_components = 0;
	WorldfsT3dmRef* components = nullptr;
};

struct WorldfsWorld {
	const char* name = nullptr;
	u16 num_parts = 0;
	u16 num_models = 0;
	WorldfsT3dmRef* parts = nullptr;
	WorldfsModelRef** models = nullptr;
};

WorldfsWorld* worldfs_read_world(WorldType type);
MxResult
worldfs_open_t3dm(WorldfsT3dmRef& ref, T3DModel** model, float lod_percent);
