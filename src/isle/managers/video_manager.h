#pragma once

#include "phoneme_list.h"
#include "mx_video_manager.h"

#include <d3drm.h>
#include <ddraw.h>

class Lego3DManager;
class LegoROI;
class MxDirect3D;
class MxStopWatch;
struct ViewportAppData;

namespace Tgl {
class Renderer;
}

class LegoVideoManager : public MxVideoManager {
public:
	LegoVideoManager();
	~LegoVideoManager() override;

	int EnableRMDevice();
	int DisableRMDevice();
	void EnableFullScreenMovie(MxBool p_enable);
	void EnableFullScreenMovie(MxBool p_enable, MxBool p_scale);
	void MoveCursor(MxS32 p_cursorX, MxS32 p_cursorY);
	void ToggleFPS(MxBool p_visible);

	MxResult Tickle() override;
	void Destroy() override;
	MxResult Create(
		MxVideoParam& p_videoParam,
		MxU32 p_frequencyMS,
		MxBool p_createThread
	) override;
	MxResult RealizePalette(MxPalette*) override;
	void
	UpdateView(MxU32 p_x, MxU32 p_y, MxU32 p_width, MxU32 p_height) override;
	virtual MxPresenter* GetPresenterAt(MxS32 p_x, MxS32 p_y);

	virtual LegoPhonemeList* GetPhonemeList() { return m_phonemeRefList; }

	void SetSkyColor(float p_red, float p_green, float p_blue);
	void OverrideSkyColor(MxBool p_shouldOverride);
	MxResult ResetPalette(MxBool p_ignoreSkyColor);
	MxPresenter* GetPresenterByActionObjectName(const char* p_char);

	void FUN_1007c520();

	Tgl::Renderer* GetRenderer() { return m_renderer; }

	Lego3DManager* Get3DManager() { return m_3dManager; }

	LegoROI* GetViewROI() { return m_viewROI; }

	MxDirect3D* GetDirect3D() { return m_direct3d; }
	MxBool GetRender3D() { return m_render3d; }
	double GetElapsedSeconds() { return m_elapsedSeconds; }

	void SetRender3D(MxBool p_render3d) { m_render3d = p_render3d; }
	void SetUnk0x554(MxBool p_unk0x554) { m_unk0x554 = p_unk0x554; }

private:
	MxResult CreateDirect3D();
	MxResult ConfigureD3DRM();
	void DrawFPS();

	inline void DrawCursor();

	Tgl::Renderer* m_renderer;
	Lego3DManager* m_3dManager;
	LegoROI* m_viewROI;
	undefined4 m_unk0x70;
	MxDirect3D* m_direct3d;
	undefined4 m_unk0x78[27];
	MxBool m_render3d;
	MxBool m_unk0xe5;
	MxBool m_unk0xe6;
	PALETTEENTRY m_paletteEntries[256];
	LegoPhonemeList* m_phonemeRefList;
	MxBool m_isFullscreenMovie;
	MxPalette* m_palette;
	MxStopWatch* m_stopWatch;
	double m_elapsedSeconds;
	MxBool m_fullScreenMovie;
	MxBool m_drawCursor;
	MxS32 m_cursorXCopy;
	MxS32 m_cursorYCopy;
	MxS32 m_cursorX;
	MxS32 m_cursorY;
	LPDIRECTDRAWSURFACE m_cursorSurface;
	RECT m_cursorRect;
	LPDIRECTDRAWSURFACE m_unk0x528;
	MxBool m_drawFPS;
	RECT m_fpsRect;
	HFONT m_arialFont;
	SIZE m_fpsSize;
	MxFloat m_unk0x54c;
	MxFloat m_unk0x550;
	MxBool m_unk0x554;
	MxBool m_paused;
	D3DVALUE m_back;
	D3DVALUE m_front;
	float m_cameraWidth;
	float m_cameraHeight;
	D3DVALUE m_fov;
	IDirect3DRMFrame* m_camera;
	D3DRMPROJECTIONTYPE m_projection;
	ViewportAppData* m_appdata;
	D3DRMRENDERQUALITY m_quality;
	DWORD m_shades;
	D3DRMTEXTUREQUALITY m_textureQuality;
	DWORD m_rendermode;
	BOOL m_dither;
	DWORD m_bufferCount;
};

// LegoVideoManager::`scalar deleting destructor'

