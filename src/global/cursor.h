#pragma once
#include <libdragon.h>

#include "utils.h"
#include "global/types.h"

struct AppCursor {
	sprite_t* cursor = nullptr;
	u32 x = 0;
	u32 y = 0;
};

extern AppCursor g_current_app_cursor;

void set_cursor(Cursor cursor);
void move_cursor(u32 x, u32 y);
void move_cursor_delta(u32 dx, u32 dy);
