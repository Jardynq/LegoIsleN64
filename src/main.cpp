#include "debug.h"
#include "debugcpp.h"
#include "display.h"
#include "dragonfs.h"
#include "graphics.h"
#include "joypad.h"
#include "legofs.h"
#include "model64.h"
#include "mpeg2.h"
#include "n64sys.h"
#include "rdpq.h"
#include "rdpq_attach.h"
#include "rdpq_rect.h"
#include "rdpq_sprite.h"
#include "rdpq_tex.h"
#include "sprite.h"
#include "surface.h"

#include <cmath>
#include <cstring>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/tpx.h>

/**
 * Simple example with a spinning quad.
 * This shows how to manually generate geometry and draw it,
 * although most o the time you should use the builtin model format.
 */
int main(void) {
	debug_init_isviewer();
	debug_init_usblog();
	// console_init();

	joypad_init();

	display_init(
		RESOLUTION_320x240,
		DEPTH_16_BPP,
		3,
		GAMMA_NONE,
		FILTERS_RESAMPLE
	);
	rdpq_init();

	dfs_init(DFS_DEFAULT_LOCATION);

	legofs_init();
	auto sprites = std::vector<sprite_t*>();

	log_info("Index size: %u\n", legofs_index.nodes.size());
	for (unsigned int n = 0; n < legofs_index.nodes.size(); n++) {
		auto node = legofs_index_node(n);
		if (node.type == LegofsType::Bitmap) {
			i32 size = 0;
			auto sprite_buf = legofs_read(node.index, &size);
			auto sprite = sprite_load_buf((void*) sprite_buf, size);
			sprites.push_back(sprite);
		}

		log_info("Node %hu name: %s\n", node.index, node.name);
		log_info("Node %hu path: %s\n", node.index, node.path);
		log_info("Node %hu presenter: %s\n", node.index, node.presenter);
		log_info("Node %hu start_time: %hu\n", node.index, node.start_time);
		log_info("Node %hu duration: %hu\n", node.index, node.duration);
		log_info("Node %hu loops: %hhu\n", node.index, node.loops);
		log_info("Node %hu flags: %hhu\n", node.index, node.flags);
		log_info(
			"Node %hu location: %f %f %f\n",
			node.index,
			node.location[0],
			node.location[1],
			node.location[2]
		);
		log_info(
			"Node %hu up: %f %f %f\n",
			node.index,
			node.up[0],
			node.up[1],
			node.up[2]
		);
		log_info(
			"Node %hu direction: %f %f %f\n",
			node.index,
			node.direction[0],
			node.direction[1],
			node.direction[2]
		);
		log_info("Node %hu extra: ", node.index);
		for (auto byte : node.extra) {
			log_inline("%02X ", byte);
		}
		log_inline("\n");
		log_inline("\n");
	}

	t3d_init((T3DInitParams) {}
	); // Init library itself, use empty params for default settings

	T3DMat4 modelMat; // matrix for our model, this is a "normal" float matrix
	t3d_mat4_identity(&modelMat);
	// Now allocate a fixed-point matrix, this is what t3d uses internally.
	T3DMat4FP* modelMatFP = (T3DMat4FP*) malloc_uncached(sizeof(T3DMat4FP));

	const T3DVec3 camPos = {{0, 0, -18}};
	const T3DVec3 camTarget = {{0, 0, 0}};

	uint8_t colorAmbient[4] = {50, 50, 50, 0xFF};
	uint8_t colorDir[4] = {0xFF, 0xFF, 0xFF, 0xFF};

	T3DVec3 lightDirVec = {{0.0f, 0.0f, 1.0f}};
	t3d_vec3_norm(&lightDirVec);

	// Allocate vertices (make sure to have an uncached pointer before passing
	// it to the API!) For performance reasons, 'T3DVertPacked' contains two
	// vertices at once in one struct.
	T3DVertPacked* vertices =
		(T3DVertPacked*) malloc_uncached(sizeof(T3DVertPacked) * 2);

	auto Z = (T3DVec3) {{0, 0, 1}};
	uint16_t norm =
		t3d_vert_pack_normal(&Z); // normals are packed in a 5.6.5 format
	vertices[0] = (T3DVertPacked) {
		.posA = {-16, -16, 0},
		.normA = norm,
		.posB = {16, -16, 0},
		.normB = norm,
		.rgbaA = 0xFF0000'FF,
		.rgbaB = 0x00FF00'FF,
	};
	vertices[1] = (T3DVertPacked) {
		.posA = {16, 16, 0},
		.normA = norm,
		.posB = {-16, 16, 0},
		.normB = norm,
		.rgbaA = 0x0000FF'FF,
		.rgbaB = 0xFF00FF'FF,
	};

	float rot_x = 0.0f;
	float rot_y = 0.0f;
	T3DVec3 X = {{1.0f, 0.0f, 0.0f}};
	T3DVec3 Y = {{0.0f, 1.0f, 0.0f}};

	// create a viewport, this defines the section to draw to (by default the
	// whole screen) and contains the projection & view (camera) matrices
	T3DViewport viewport = t3d_viewport_create();

	rspq_block_t* dplDraw = NULL;

	int sprite_index = 0;
	for (;;) {
		joypad_poll();
		// ======== Update ======== //
		joypad_inputs_t inputs = joypad_get_inputs(JOYPAD_PORT_1);

		auto a = joypad_get_buttons_pressed(JOYPAD_PORT_1);
		if (a.start) {
			break;
		}
		if (a.a) {
			sprite_index++;
			if (sprite_index >= (int) sprites.size()) {
				sprite_index = 0;
			}
		}

		rot_x += ((float) inputs.stick_x / (float) JOYPAD_RANGE_N64_STICK_MAX) *
				 0.03f;

		rot_y += ((float) inputs.stick_y / (float) JOYPAD_RANGE_N64_STICK_MAX) *
				 0.03f;

		t3d_viewport_set_projection(
			&viewport,
			T3D_DEG_TO_RAD(85.0f),
			10.0f,
			100.0f
		);
		t3d_viewport_look_at(&viewport, &camPos, &camTarget, &Y);

		// Model-Matrix, t3d offers some basic matrix functions

		float pos[3] = {0.0f, 0.0f, 0.0f};
		float scale[3] = {0.4f, 0.4f, 0.4f};
		float rot[3] = {rot_y, rot_x, 0.0f};
		t3d_mat4_from_srt_euler(&modelMat, scale, rot, pos);

		t3d_mat4_scale(&modelMat, 0.4f, 0.4f, 0.4f);
		t3d_mat4_to_fixed(modelMatFP, &modelMat);

		// ======== Draw (3D) ======== //
		auto display_surface = display_get();
		auto display_zbuf = display_get_zbuf();
		rdpq_attach(display_surface,
					display_zbuf); // set the target to draw to
		t3d_frame_start(
		); // call this once per frame at the beginning of your draw function

		t3d_viewport_attach(&viewport
		); // now use the viewport, this applies proj/view matrices and sets
		   // scissoring

		// TODO: check this guy out some more for texturing.
		rdpq_mode_combiner(RDPQ_COMBINER_SHADE);
		// this cleans the entire screen (even if out viewport is smaller)
		t3d_screen_clear_color(RGBA32(100, 0, 100, 0));
		t3d_screen_clear_depth();

		t3d_light_set_ambient(
			colorAmbient
		); // one global ambient light, always active
		t3d_light_set_directional(
			0,
			colorDir,
			&lightDirVec
		); // optional directional light, can be disabled
		t3d_light_set_count(1);

		t3d_state_set_drawflags((T3DDrawFlags) (T3D_FLAG_SHADED | T3D_FLAG_DEPTH
		));

		// t3d functions can be recorded into a display list:
		if (!dplDraw) {
			rspq_block_begin();

			t3d_matrix_push(
				modelMatFP
			); // Matrix load can be recorded as they DMA the data in internally

			// rdpq_sprite_upload(TILE0, sprite, &texParam);
			t3d_vert_load(vertices, 0, 4); // load 4 vertices...
			t3d_matrix_pop(1);     // ...and pop the matrix, this can be done as
								   // soon as the vertices are loaded...
			t3d_tri_draw(0, 1, 2); // ...then draw 2 triangles
			t3d_tri_draw(2, 3, 0);

			// NOTE: if you use the builtin model format, syncs are handled
			// automatically!
			t3d_tri_sync(); // after each batch of triangles, a sync is needed
			// technically, you only need a sync before any new 't3d_vert_load',
			// rdpq call, or after the last triangle for safety, just call it
			// after you are done with all triangles after a load

			dplDraw = rspq_block_end();
		}

		rspq_block_run(dplDraw);
		// rdpq_blitparms_t b = {};
		// rdpq_sprite_blit(sprites[sprite_index], 0, 0, nullptr);

		rdpq_detach_wait();

		graphics_draw_sprite(display_surface, 0, 0, sprites[sprite_index]);
		display_show(display_surface);
	}

	t3d_destroy();
	return 0;
}