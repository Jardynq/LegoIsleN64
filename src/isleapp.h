#ifndef ISLEAPP_H
#define ISLEAPP_H

#include "mxvideoparam.h"

#include <windows.h>

class IsleApp {
public:
	IsleApp();
	~IsleApp();

	void Close();

	BOOL SetupLegoOmni();
	void SetupVideoFlags(
		BOOL fullScreen,
		BOOL flipSurfaces,
		BOOL backBuffers,
		BOOL using8bit,
		BOOL using16bit,
		BOOL param_6,
		BOOL param_7,
		BOOL wideViewAngle,
		char* deviceId
	);
	MxResult SetupWindow(HINSTANCE hInstance, LPSTR lpCmdLine);

	BOOL ReadReg(LPCSTR name, LPSTR outValue, DWORD outSize);
	BOOL ReadRegBool(LPCSTR name, BOOL* out);
	BOOL ReadRegInt(LPCSTR name, int* out);

	void LoadConfig();
	void Tick(BOOL sleepIfNotNextFrame);
	void SetupCursor(WPARAM wParam);

	HWND GetWindowHandle() { return m_windowHandle; }
	MxLong GetFrameDelta() { return m_frameDelta; }
	BOOL GetFullScreen() { return m_fullScreen; }
	HCURSOR GetCursorCurrent() { return m_cursorCurrent; }
	HCURSOR GetCursorBusy() { return m_cursorBusy; }
	HCURSOR GetCursorNo() { return m_cursorNo; }
	BOOL GetDrawCursor() { return m_drawCursor; }

	void SetWindowActive(BOOL p_windowActive) {
		m_windowActive = p_windowActive;
	}

private:
	LPSTR m_hdPath;
	LPSTR m_cdPath;
	LPSTR m_deviceId;
	LPSTR m_savePath;
	BOOL m_fullScreen;
	BOOL m_flipSurfaces;
	BOOL m_backBuffersInVram;
	BOOL m_using8bit;
	BOOL m_using16bit;
	int m_unk0x24;
	BOOL m_use3dSound;
	BOOL m_useMusic;
	BOOL m_useJoystick;
	int m_joystickIndex;
	BOOL m_wideViewAngle;
	int m_islandQuality;
	int m_islandTexture;
	BOOL m_gameStarted;
	MxLong m_frameDelta;
	MxVideoParam m_videoParam;
	BOOL m_windowActive;
	HWND m_windowHandle;
	BOOL m_drawCursor;
	HCURSOR m_cursorArrow;
	HCURSOR m_cursorBusy;
	HCURSOR m_cursorNo;
	HCURSOR m_cursorCurrent;
};

#endif // ISLEAPP_H
