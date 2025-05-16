#include "debugcpp.h"
#include "display.h"
#include "dragonfs.h"
#include "graphics.h"
#include "legofs.h"
#include "mixer.h"
#include "rdpq.h"
#include "rdpq_attach.h"
#include "rdpq_sprite.h"
#include "rspq.h"
#include "sprite.h"
#include "testing.h"
#include "yuv.h"

#include <cmath>
#include <cstring>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/tpx.h>

auto sprites = std::vector<LegofsNode>();
int asset_index = 0;
int asset_type_index = 0;

int asset_count = 0;
int asset_type_count = 3;

bool changed = false;

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

	display_init(
		RESOLUTION_320x240,
		DEPTH_16_BPP,
		3,
		GAMMA_NONE,
		FILTERS_RESAMPLE
	);

	auto fs_index = legofs_get_index(si);

	log_info("Index size: %u\n", fs_index.nodes.size());
	for (unsigned int n = 0; n < fs_index.nodes.size(); n++) {
		auto node = legofs_index_node(si, (u16) n);
		print_node(node);
		switch (node.type) {
		case LegofsType::Bitmap: {
			sprites.push_back(node);
			break;
		}
		default: {
			break;
		}
		}
	}

	for (;;) {
		auto display_surface = display_get();

		rdpq_attach_clear(display_surface, 0);
		rdpq_detach_wait();

		std::sort(
			sprites.begin(),
			sprites.end(),
			[](const auto& a, const auto& b) {
				return a.location[2] < b.location[2];
			}
		);

		for (size_t i = 0; i < sprites.size(); i++) {
			const auto& node = sprites[i];
			sprite_t* sprite = nullptr;
			legofs_open_sprite(si, (u16) node.index, &sprite);

			graphics_draw_sprite_trans(
				display_surface,
				node.location[0],
				node.location[1],
				sprite
			);
			sprite_free(sprite);
		}

		rspq_flush();
		rspq_wait();
		display_show(display_surface);
	}

	return 0;
}