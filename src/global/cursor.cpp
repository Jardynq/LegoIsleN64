#include "cursor.h"

#include "sprite.h"

AppCursor g_current_app_cursor;

void set_cursor(Cursor cursor) {
	if (g_current_app_cursor.cursor != nullptr) {
		sprite_free(g_current_app_cursor.cursor);
		g_current_app_cursor.cursor = nullptr;
	}

	switch (cursor) {
	case e_cursorArrow:
		sprite_load("rom:/cursors/arrow.sprite", &g_current_app_cursor.cursor);
	case e_cursorBusy:
		sprite_load("rom:/cursors/busy.sprite", &g_current_app_cursor.cursor);
	case e_cursorNo:
		sprite_load("rom:/cursors/no.sprite", &g_current_app_cursor.cursor);
	case e_cursorNone:
		break;
	case e_cursorUnused3:
	case e_cursorUnused4:
	case e_cursorUnused5:
	case e_cursorUnused6:
	case e_cursorUnused7:
	case e_cursorUnused8:
	case e_cursorUnused9:
	case e_cursorUnused10:
		break;
	}
}

void move_cursor(u32 x, u32 y) {
	g_current_app_cursor.x = x;
	g_current_app_cursor.y = y;
}

void move_cursor_delta(u32 dx, u32 dy) {
	g_current_app_cursor.x += dx;
	g_current_app_cursor.y += dy;
}