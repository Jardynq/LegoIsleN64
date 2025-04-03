#include "debugcpp.h"
#include "display.h"
#include "dragonfs.h"
#include "global/debug.h"
#include "global/types.h"
#include "graphics.h"
#include "joypad.h"
#include "legofs.h"
#include "mixer.h"
#include "mpeg2.h"
#include "rdpq.h"
#include "rdpq_attach.h"
#include "rdpq_sprite.h"
#include "rspq.h"
#include "sprite.h"
#include "wav64.h"
#include "yuv.h"

#include <cmath>
#include <cstring>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/tpx.h>

typedef struct mpeg2_s {
	void* buf;
	void* v;
	void* f;
} mpeg2_t;

auto sprites = std::vector<u16>();
auto waves = std::vector<u16>();
auto vids = std::vector<u16>();
int asset_index = 0;
int asset_type_index = 0;

int asset_count = 0;
int asset_type_count = 3;

int video_width = 32;
int video_height = 32;
yuv_blitter_t yuv;

bool changed = false;

yuv_frame_t last_frame2;
sprite_t* current_sprite = nullptr;
mpeg2_t* current_vid = nullptr;
wav64_t current_audio;

void on_change() {
	changed = true;
	if (asset_type_index == 0) {
		if (current_sprite != nullptr) {
			sprite_free(current_sprite);
		}
		MxResult result =
			legofs_open_sprite(sprites[asset_index], &current_sprite);
		if (result == FAILURE) {
			log_error("Failed to open sprite %u\n", sprites[asset_index]);
			return;
		}
	} else if (asset_type_index == 1) {
		if (current_audio.st != nullptr) {
			wav64_close(&current_audio);
		}
		MxResult result = legofs_open_audio(waves[asset_index], &current_audio);
		if (result == FAILURE) {
			log_error("Failed to open audio %u\n", waves[asset_index]);
			return;
		}
		mixer_ch_stop(0);
		wav64_play(&current_audio, 0);
	} else if (asset_type_index == 2) {
		if (current_vid != nullptr) {
			mpeg2_close(current_vid);
		}
		MxResult result = legofs_open_video(vids[asset_index], &current_vid);
		if (result == FAILURE) {
			log_error("Failed to open video %u\n", vids[asset_index]);
			return;
		}
		video_width = mpeg2_get_width(current_vid);
		video_height = mpeg2_get_height(current_vid);
		if (yuv.block != nullptr) {
			yuv_blitter_free(&yuv);
		}
		int cx = display_get_width() / 2;
		int cy = display_get_height() / 2;
		int cw = video_width / 2;
		int ch = video_height / 2;
		yuv = yuv_blitter_new(
			video_width,
			video_height,
			cx - cw,
			cy - ch,
			nullptr,
			nullptr
		);
	}
}

int main(void) {
	debug_init_isviewer();
	debug_init_usblog();

	joypad_init();

	dfs_init(DFS_DEFAULT_LOCATION);
	legofs_init();

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

	log_info("Index size: %u\n", legofs_index.nodes.size());
	for (unsigned int n = 0; n < legofs_index.nodes.size(); n++) {
		auto node = legofs_index_node(n);

		switch (node.type) {
		case LegofsType::Bitmap: {
			debugf(
				"Bitmap %u: \t%s \t %s\n",
				node.index,
				node.name,
				node.presenter
			);
			sprites.push_back(node.index);
			break;
		}
		case LegofsType::Wave: {
			debugf(
				"Wave %u: \t%s \t %s\n",
				node.index,
				node.name,
				node.presenter
			);
			waves.push_back(node.index);
			break;
		}
		case LegofsType::Flic:
		case LegofsType::Smacker: {
			debugf(
				"Video %u: \t%s \t %s\n",
				node.index,
				node.name,
				node.presenter
			);
			vids.push_back(node.index);
			break;
		}
		case LegofsType::Presenter: {
			debugf(
				"Presenter %u: \t%s \t %s\n",
				node.index,
				node.name,
				node.presenter
			);
			break;
		}
		case LegofsType::World: {
			debugf(
				"World %u: \t%s \t %s\n",
				node.index,
				node.name,
				node.presenter
			);
			break;
		}
		case LegofsType::Object: {
			debugf(
				"Object %u: \t%s \t %s\n",
				node.index,
				node.name,
				node.presenter
			);
			break;
		}
		case LegofsType::Animation: {
			debugf(
				"Animation %u: \t%s \t %s\n",
				node.index,
				node.name,
				node.presenter
			);
			break;
		}
		case LegofsType::Event: {
			debugf(
				"Event %u: \t%s \t %s\n",
				node.index,
				node.name,
				node.presenter
			);
			break;
		}

		case LegofsType::Null:
			break;
		}
	}

	on_change();
	for (;;) {

		joypad_poll();
		auto a = joypad_get_buttons_pressed(JOYPAD_PORT_1);
		if (a.start) {
			break;
		}

		if (a.a) {
			asset_index = 0;
			asset_type_index++;
			if (asset_type_index >= asset_type_count) {
				asset_type_index = 0;
			}
			on_change();
		}
		if (a.b) {
			asset_index = 0;
			asset_type_index--;
			if (asset_type_index < 0) {
				asset_type_index = asset_type_count - 1;
			}
			on_change();
		}

		asset_count = 0;
		if (asset_type_index == 0) {
			asset_count = sprites.size();
		} else if (asset_type_index == 1) {
			asset_count = waves.size();
		} else if (asset_type_index == 2) {
			asset_count = vids.size();
		}

		if (a.d_right) {
			asset_index++;
			if (asset_index >= asset_count) {
				asset_index = 0;
			}
			on_change();
		}
		if (a.d_left) {
			asset_index--;
			if (asset_index < 0) {
				asset_index = asset_count - 1;
			}
			on_change();
		}

		auto display_surface = display_get();

		char buf[256] = {0};
		if (asset_type_index == 0) {
			rdpq_attach_clear(display_surface, 0);
			rdpq_detach_wait();
			snprintf(
				buf,
				sizeof(buf),
				"Sprite %u/%u: %s\n%ux%u",
				asset_index + 1,
				asset_count,
				legofs_index_node(sprites[asset_index]).name,
				current_sprite->width,
				current_sprite->height
			);
			int cx = display_get_width() / 2;
			int cy = display_get_height() / 2;
			int cw = current_sprite->width / 2;
			int ch = current_sprite->height / 2;
			graphics_draw_sprite(
				display_surface,
				cx - cw,
				cy - ch,
				current_sprite
			);
			graphics_draw_text(display_surface, 8, 8, buf);
			rspq_flush();
			rspq_wait();
			display_show(display_surface);
		} else if (asset_type_index == 1) {
			rdpq_attach_clear(display_surface, 0);
			rdpq_detach_wait();
			mixer_try_play();
			snprintf(
				buf,
				sizeof(buf),
				"Audio %u/%u: %s\n%s %fhz, %u samples",
				asset_index + 1,
				asset_count,
				legofs_index_node(waves[asset_index]).name,
				current_audio.wave.channels == 1 ? "Mono" : "Stereo",
				current_audio.wave.frequency,
				current_audio.wave.len
			);
			graphics_draw_text(display_surface, 8, 8, buf);
			rspq_flush();
			mixer_try_play();
			rspq_wait();
			mixer_try_play();
			display_show(display_surface);
		} else if (asset_type_index == 2) {
			snprintf(
				buf,
				sizeof(buf),
				"Video %u/%u: %s\n",
				asset_index + 1,
				asset_count,
				legofs_index_node(vids[asset_index]).name
			);

			rdpq_attach_clear(display_surface, nullptr);
			if (mpeg2_next_frame(current_vid)) {
				last_frame2 = mpeg2_get_frame(current_vid);
				yuv_blitter_run(&yuv, &last_frame2);
			} else {
				yuv_blitter_run(&yuv, &last_frame2);
			}
			rdpq_detach_wait();
			graphics_draw_text(display_surface, 8, 8, buf);
			rspq_flush();
			rspq_wait();
			display_show(display_surface);
		}
	}

	return 0;
}