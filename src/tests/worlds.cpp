#include "debugcpp.h"
#include "display.h"
#include "dragonfs.h"
#include "global/types.h"
#include "graphics.h"
#include "joypad.h"
#include "mixer.h"
#include "n64sys.h"
#include "rdpq.h"
#include "rdpq_attach.h"
#include "rdpq_macros.h"
#include "rspq.h"
#include "t3d/t3dmodel.h"
#include "worldfs.h"
#include "yuv.h"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <libdragon.h>
#include <math.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/tpx.h>

// I keep confusing these two
#define printf debugf

WorldType worlds[] = {
	WorldType::bldd,  WorldType::bldh,   WorldType::bldj,      WorldType::hosp,
	WorldType::bldr,  WorldType::police, WorldType::gmain,     WorldType::icube,
	WorldType::ielev, WorldType::iisle,  WorldType::racc,      WorldType::imain,
	WorldType::ireg,  WorldType::racj,   WorldType::act1,      WorldType::act2,
	WorldType::act3,  WorldType::test,   WorldType::testworld, WorldType::isle,
};
int world_index = 19;

void cross_prod(const float a[3], const float b[3], float result[3]) {
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = a[2] * b[0] - a[0] * b[2];
	result[2] = a[0] * b[1] - a[1] * b[0];
}
void norm(float v[3]) {
	float length = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (length > 0.0f) {
		v[0] /= length;
		v[1] /= length;
		v[2] /= length;
	}
}
void to_euler(
	const float direction[3],
	const float upwards[3],
	float* pitch,
	float* yaw,
	float* roll
) {
	float dir[3] = {direction[0], direction[1], direction[2]};
	float up_vec[3] = {upwards[0], upwards[1], upwards[2]};
	norm(dir);
	norm(up_vec);

	float right[3];
	cross_prod(up_vec, dir, right);
	norm(right);

	float up[3];
	cross_prod(dir, right, up);
	norm(up);

	if (right[2] < 1.0f) {
		if (right[2] > -1.0f) {
			*yaw = asinf(-right[2]);
			*pitch = atan2f(up[2], dir[2]);
			*roll = atan2f(right[1], right[0]);
		} else {
			*yaw = M_PI / 2.0f;
			*pitch = atan2f(-up[0], up[1]);
			*roll = 0.0f;
		}
	} else {
		*yaw = -M_PI / 2.0f;
		*pitch = atan2f(-up[0], up[1]);
		*roll = 0.0f;
	}
}

struct Model {
	void free() {
		if (mat != nullptr) {
			free_uncached(mat);
		}
		if (t3d != nullptr) {
			t3d_model_free(t3d);
		}
	}

	bool isVisible = true;
	T3DModel* t3d = nullptr;
	rspq_block_t* dpl = nullptr;
	T3DMat4FP* mat = nullptr;
};

std::vector<Model> models;

void unload_world() {
	for (auto& model : models) {
		model.free();
	}
	models.clear();
}

void load_world() {
	auto world = worldfs_read_world(worlds[world_index]);
	debugf("World: %s\n", world->name);

	for (int i = 0; i < world->num_models; ++i) {
		auto& ref = *world->models[i];
		debugf("Model: %s\n", ref.name);
		for (int j = 0; j < ref.num_components; ++j) {
			auto& comp = ref.components[j];
			debugf("  Component: %s\n", comp.roiname);
			T3DModel* model = nullptr;
			if (worldfs_open_t3dm(comp, &model, 0.5f) != SUCCESS) {
				debugf("Failed to load model %s\n", comp.roiname);
				continue;
			}
			float scale = 0.05f;

			T3DVec3 pos = {
				{(ref.center[0] + ref.location[0]) * 64 * scale,
				 (ref.center[1] + ref.location[1]) * 64 * scale,
				 (ref.center[2] + ref.location[2]) * 64 * scale}
			};
			T3DVec3 dir = {
				{ref.direction[0], ref.direction[1], ref.direction[2]}
			};
			T3DVec3 up = {{ref.up[0], ref.up[1], ref.up[2]}};
			T3DMat4 mat;
			float pitch = 0, yaw = 0, roll = 0;
			to_euler(dir.v, up.v, &pitch, &yaw, &roll);
			t3d_mat4_from_srt_euler(
				mat,
				{scale, scale, scale},
				{pitch, -yaw, roll},
				pos
			);

			auto matfp = (T3DMat4FP*) malloc_uncached(sizeof(T3DMat4FP));
			t3d_mat4_to_fixed(matfp, &mat);

			rspq_block_begin();
			t3d_matrix_push(matfp);
			T3DModelState state = t3d_model_state_create();
			T3DModelIter it =
				t3d_model_iter_create(model, T3D_CHUNK_TYPE_OBJECT);
			while (t3d_model_iter_next(&it)) {
				if (it.object->material) {
					if (it.object->material->renderFlags & T3D_FLAG_TEXTURED) {
						it.object->material->colorCombiner =
							RDPQ_COMBINER_TEX_SHADE;
					} else {
						it.object->material->colorCombiner =
							RDPQ_COMBINER1((PRIM, 0, SHADE, 0), (0, 0, 0, 1));
					}

					it.object->material->renderFlags &= ~T3D_FLAG_CULL_BACK;

					t3d_model_draw_material(it.object->material, &state);
				}
				t3d_model_draw_object(it.object, nullptr);
			}
			t3d_model_draw(model);
			t3d_matrix_pop(1);
			auto dpl = rspq_block_end();

			models.push_back(
				Model{
					.isVisible = ref.isVisible,
					.t3d = model,
					.dpl = dpl,
					.mat = matfp,
				}
			);
		}
	}
}

int main(void) {
	debug_init_isviewer();
	debug_init_usblog();

	joypad_init();

	dfs_init(DFS_DEFAULT_LOCATION);

	rdpq_init();
	yuv_init();

	audio_init(32000.0f, 4);
	mixer_init(8);

	joypad_init();

	const resolution_t resolution =
		{.width = 128, .height = 120, .interlaced = INTERLACE_OFF};
	display_init(
		RESOLUTION_640x480,
		DEPTH_32_BPP,
		3,
		GAMMA_NONE,
		FILTERS_RESAMPLE
	);

	t3d_init((T3DInitParams) {});
	T3DViewport viewport = t3d_viewport_create();

	T3DVec3 up{{0, 1, 0}};
	T3DVec3 camPos = {{0, 25.0f, 25.0f}};
	T3DVec3 camForward = {{0, 0, 0}};
	T3DVec3 camRight = {{0, 0, 0}};
	const float camSpeed = 1.0f;
	const float camSpeedMult = 10.0f;

	const float deadzone = 0.1f;
	const float camSens = 0.1f;

	float camEulerX = 3.145f;
	float camEulerY = -0.785f;

	uint8_t colorAmbient[4] = {0x55, 0x55, 0x55, 0xff};
	uint8_t colorDir[4] = {0xeb, 0xd8, 0x8f, 0xff};

	T3DVec3 lightDirVec = {{-1.0f, 1.0f, 1.0f}};
	t3d_vec3_norm(&lightDirVec);

	load_world();

	for (;;) {
		joypad_poll();
		auto a = joypad_get_buttons_pressed(JOYPAD_PORT_1);
		auto b = joypad_get_inputs(JOYPAD_PORT_1);
		auto c = joypad_get_buttons_held(JOYPAD_PORT_1);
		if (a.start) {
			break;
		}
		if (a.a) {
			world_index++;
			if (world_index >= WORLDFS_COUNT) {
				world_index = 0;
			}
			unload_world();
			load_world();
		}
		if (a.b) {
			world_index--;
			if (world_index < 0) {
				world_index = WORLDFS_COUNT - 1;
			}
			unload_world();
			load_world();
		}

		if (abs(b.cstick_x) > deadzone || abs(b.cstick_y) > deadzone) {
			camEulerX += ((float) b.cstick_x / 127.0f) * camSens;
			camEulerY -= ((float) b.cstick_y / 127.0f) * camSens;

			camEulerX = fmod(camEulerX, T3D_PI * 2.0f);
			const float maxPitch = T3D_PI / 2.0f - 0.01f;
			/*if (camEulerY > maxPitch) {
				camEulerY = maxPitch;
			}
			if (camEulerY < -maxPitch) {
				camEulerY = -maxPitch;
			}*/
		}

		float cosPitch = cosf(camEulerY);
		float sinPitch = sinf(camEulerY);
		float cosYaw = cosf(camEulerX);
		float sinYaw = sinf(camEulerX);
		camRight = {cosYaw, 0.0f, -sinYaw};
		camForward = {cosPitch * sinYaw, sinPitch, cosPitch * cosYaw};

		float speed = camSpeed;
		if (c.l) {
			speed = camSpeed * camSpeedMult;
		}
		if (abs(b.stick_x) >= deadzone || abs(b.stick_y) >= deadzone) {
			float x = b.stick_x / 127.0f;
			float y = b.stick_y / 127.0f;
			camPos.x += (camForward.x * y + camRight.x * x) * speed;
			camPos.y += (camForward.y * y) * speed;
			camPos.z += (camForward.z * y + camRight.z * x) * speed;
		}

		// ======== Update ======== //
		t3d_viewport_set_projection(
			&viewport,
			T3D_DEG_TO_RAD(70.0f),
			5.0f,
			175.0f
		);
		T3DVec3 lookForward{
			{camPos.x + camForward.x,
			 camPos.y + camForward.y,
			 camPos.z + camForward.z}
		};
		t3d_viewport_look_at(&viewport, &camPos, &lookForward, &up);

		T3DMat4 xflip;
		t3d_mat4_identity(xflip);
		t3d_mat4_scale(xflip, -1.0f, 1.0f, 1.0f);
		t3d_mat4_mul(viewport.matProj, xflip, viewport.matProj);

		// ======== Draw ======== //
		surface_t* buf = display_try_get();
		while (buf == nullptr) {
			buf = display_try_get();
			wait_ms(1);
		}
		rdpq_attach(buf, display_get_zbuf());
		t3d_frame_start();
		t3d_viewport_attach(&viewport);
		t3d_screen_clear_color(RGBA32(100, 80, 80, 0xFF));
		t3d_screen_clear_depth();

		// rdpq_mode_fog(RDPQ_FOG_STANDARD);
		// rdpq_set_fog_color((color_t) {0xFF, 0xFF, 0xFF, 0xFF});
		// t3d_fog_set_range(20.0f, 100.0f);
		// t3d_fog_set_enabled(true);

		rdpq_set_env_color((color_t) {0xFF, 0xFF, 0xFF, 0xFF});
		// rdpq_set_prim_color((color_t) {0xFF, 0x00, 0x00, 0xFF});

		t3d_light_set_ambient(colorAmbient);
		t3d_light_set_directional(0, colorDir, &lightDirVec);
		t3d_light_set_count(1);

		for (int i = 0; i < models.size(); i++) {
			if (i != 9 && i != 5 && i != 11) {
				if (models[i].isVisible) {
					// debugf("Model %d\n", i);
					rspq_block_run(models[i].dpl);
				} else {
					// debugf("Model %d (not visible)\n", i);
				}
			} else {
				if (models[i].isVisible) {
					// debugf("Skipping %d\n", i);
				} else {
					// debugf("Skipping %d (not visible)\n", i);
				}
			}
		}

		rdpq_detach_show();
	}

	t3d_destroy();
	return 0;
}