#include "debugcpp.h"
#include "display.h"
#include "dragonfs.h"
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
#include "testing.h"
#include "wav64.h"
#include "yuv.h"

#include <cmath>
#include <cstring>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/tpx.h>

auto sprites = std::vector<u16>();
auto waves = std::vector<u16>();
auto vids = std::vector<u16>();
int asset_index = 0;
int asset_type_index = 0;

int video_width = 32;
int video_height = 32;
yuv_blitter_t yuv;

yuv_frame_t last_frame2;
sprite_t* current_sprite = nullptr;
mpeg2_t* current_vid = nullptr;
wav64_t current_audio;

bool is_bad = true;

int get_asset_count(int index) {
	if (index == 0) {
		return sprites.size();
	} else if (index == 1) {
		return waves.size();
	} else if (index == 2) {
		return vids.size();
	}
	return 0;
}

void on_change() {
	if (get_asset_count(asset_type_index) == 0) {
		is_bad = true;
		return;
	}

	if (asset_type_index == 0) {
		if (current_sprite != nullptr) {
			sprite_free(current_sprite);
		}
		MxResult result =
			legofs_open_sprite(si, sprites[asset_index], &current_sprite);
		if (result == FAILURE) {
			log_error("Failed to open sprite %u\n", sprites[asset_index]);
			is_bad = true;
			return;
		}
	} else if (asset_type_index == 1) {
		if (current_audio.st != nullptr) {
			wav64_close(&current_audio);
		}
		MxResult result =
			legofs_open_audio(si, waves[asset_index], &current_audio);
		if (result == FAILURE) {
			log_error("Failed to open audio %u\n", waves[asset_index]);
			is_bad = true;
			return;
		}
		mixer_ch_stop(0);
		wav64_play(&current_audio, 0);
	} else if (asset_type_index == 2) {
		if (current_vid != nullptr) {
			mpeg2_close(current_vid);
		}
		MxResult result =
			legofs_open_video(si, vids[asset_index], &current_vid);
		if (result == FAILURE) {
			log_error("Failed to open video %u\n", vids[asset_index]);
			is_bad = true;
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
	is_bad = false;
}

void change_asset_index(int new_index) {
	if (new_index == asset_index) {
		return;
	}

	int asset_count = get_asset_count(asset_type_index);
	if (asset_count == 0) {
		return;
	}

	if (new_index >= asset_count) {
		new_index = 0;
	} else if (new_index < 0) {
		new_index = asset_count - 1;
	}

	asset_index = new_index;
	on_change();
}

void change_asset_type(int new_index) {
	if (new_index == asset_type_index) {
		return;
	} else if (new_index >= 3) {
		new_index = 0;
	} else if (new_index < 0) {
		new_index = 2;
	}

	asset_type_index = new_index;
	asset_index = 0;
	on_change();
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
		auto node = legofs_index_node(si, n);

		print_node(node);
		switch (node.type) {
		case LegofsType::Bitmap: {
			sprites.push_back(node.index);
			break;
		}
		case LegofsType::Wave: {
			waves.push_back(node.index);
			break;
		}
		case LegofsType::Flic:
		case LegofsType::Smacker: {
			vids.push_back(node.index);
			break;
		}
		default: {
			break;
		}
		}
	}

	on_change();
	while (true) {

		joypad_poll();
		auto a = joypad_get_buttons_pressed(JOYPAD_PORT_1);
		if (a.start) {
			break;
		}

		if (a.a) {
			change_asset_type(asset_type_index + 1);
		}
		if (a.b) {
			change_asset_type(asset_type_index - 1);
		}

		if (a.d_right) {
			change_asset_index(asset_index + 1);
		}
		if (a.d_left) {
			change_asset_index(asset_index - 1);
		}

		int asset_count = get_asset_count(asset_type_index);
		auto display_surface = display_get();

		char buf[256] = {0};
		if (get_asset_count(asset_type_index) == 0 || is_bad) {
			const char* type_str = "Unknown";
			if (asset_type_index == 0) {
				type_str = "Sprite";
			} else if (asset_type_index == 1) {
				type_str = "Audio";
			} else if (asset_type_index == 2) {
				type_str = "Video";
			}

			rdpq_attach_clear(display_surface, 0);
			rdpq_detach_wait();
			rspq_flush();
			rspq_wait();
			snprintf(buf, sizeof(buf), "No %s available", type_str);
			graphics_draw_text(display_surface, 8, 8, buf);
			display_show(display_surface);
		} else if (asset_type_index == 0) {
			rdpq_attach_clear(display_surface, 0);
			rdpq_detach_wait();
			rspq_flush();
			rspq_wait();
			snprintf(
				buf,
				sizeof(buf),
				"Sprite %u/%u: %s\n%ux%u",
				asset_index + 1,
				asset_count,
				legofs_index_node(si, sprites[asset_index]).name,
				current_sprite->width,
				current_sprite->height
			);
			int cx = display_get_width() / 2;
			int cy = display_get_height() / 2;
			int cw = current_sprite->width / 2;
			int ch = current_sprite->height / 2;
			graphics_draw_sprite_trans(
				display_surface,
				cx - cw,
				cy - ch,
				current_sprite
			);
			graphics_draw_text(display_surface, 8, 8, buf);
			display_show(display_surface);
		} else if (asset_type_index == 1) {
			rdpq_attach_clear(display_surface, 0);
			mixer_try_play();
			rdpq_detach_wait();
			rspq_flush();
			mixer_try_play();
			rspq_wait();
			snprintf(
				buf,
				sizeof(buf),
				"Audio %u/%u: %s\n%s %fhz, %u samples",
				asset_index + 1,
				asset_count,
				legofs_index_node(si, waves[asset_index]).name,
				current_audio.wave.channels == 1 ? "Mono" : "Stereo",
				current_audio.wave.frequency,
				current_audio.wave.len
			);
			mixer_try_play();
			graphics_draw_text(display_surface, 8, 8, buf);
			mixer_try_play();
			display_show(display_surface);
			mixer_try_play();
		} else if (asset_type_index == 2) {
			snprintf(
				buf,
				sizeof(buf),
				"Video %u/%u: %s\n",
				asset_index + 1,
				asset_count,
				legofs_index_node(si, vids[asset_index]).name
			);

			rdpq_attach_clear(display_surface, nullptr);
			if (mpeg2_next_frame(current_vid)) {
				last_frame2 = mpeg2_get_frame(current_vid);
				yuv_blitter_run(&yuv, &last_frame2);
			} else {
				yuv_blitter_run(&yuv, &last_frame2);
			}
			rdpq_detach_wait();
			rspq_flush();
			rspq_wait();
			graphics_draw_text(display_surface, 8, 8, buf);
			display_show(display_surface);
		}
	}

	return 0;
}