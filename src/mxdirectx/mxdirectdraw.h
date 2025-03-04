#ifndef MXDIRECTDRAW_H
#define MXDIRECTDRAW_H

#include "mxdirectxinfo.h"

#include <ddraw.h>
#include <windows.h>

class MxDirectDraw {
public:
	typedef void (*ErrorHandler)(const char*, HRESULT, void*);

	static int GetPrimaryBitDepth();

	MxDirectDraw();
	virtual ~MxDirectDraw();

	virtual BOOL Create(
		HWND hWnd,
		BOOL fullscreen_1,
		BOOL surface_fullscreen,
		BOOL onlySystemMemory,
		int width,
		int height,
		int bpp,
		const PALETTEENTRY* pPaletteEntries,
		int paletteEntryCount
	);
	virtual void Destroy();
	virtual void DestroyButNotDirectDraw();

	IDirectDraw* DirectDraw() { return m_pDirectDraw; }
	IDirectDrawSurface* FrontBuffer() { return m_pFrontBuffer; }
	IDirectDrawSurface* BackBuffer() { return m_pBackBuffer; }
	IDirectDrawClipper* Clipper() { return m_pClipper; }

	BOOL IsFullScreen() { return m_bFullScreen; }

	BOOL IsSupportedMode(int width, int height, int bpp);

	int Pause(BOOL);
	BOOL RestoreSurfaces();

	BOOL TextToTextSurface1(const char* text);
	BOOL TextToTextSurface2(const char* lpString);

	virtual const char* ErrorToString(HRESULT p_error);
	int FlipToGDISurface();

protected:
	BOOL SetPaletteEntries(
		const PALETTEENTRY* pPaletteEntries,
		int paletteEntryCount,
		BOOL fullscreen
	);
	BOOL CacheOriginalPaletteEntries();
	BOOL RestoreOriginalPaletteEntries();
	BOOL RestorePaletteEntries();

	BOOL DDInit(BOOL fullscreen);
	BOOL DDSetMode(int width, int height, int bpp);
	BOOL DDCreateSurfaces();
	HRESULT
	CreateDDSurface(LPDDSURFACEDESC a2, LPDIRECTDRAWSURFACE* a3, IUnknown* a4);
	BOOL GetDDSurfaceDesc(
		LPDDSURFACEDESC lpDDSurfDesc,
		LPDIRECTDRAWSURFACE lpDDSurf
	);
	BOOL CreateZBuffer(DWORD memorytype, DWORD depth);

	BOOL CreateTextSurfaces();
	BOOL TextToTextSurface(
		const char* text,
		IDirectDrawSurface* pSurface,
		SIZE& textSizeOnSurface
	);

	void Error(const char* p_message, int p_error);

	BOOL RecreateDirectDraw(GUID** a2);
	void FUN_1009e020();
	void FUN_1009d920();

	// MxDirectDraw::`scalar deleting destructor'

protected:
	BOOL m_bOnlySoftRender;
	BOOL m_bFlipSurfaces;
	IDirectDraw* m_pDirectDraw;
	IDirectDrawSurface* m_pFrontBuffer;
	IDirectDrawSurface* m_pBackBuffer;
	IDirectDrawSurface* m_pZBuffer;
	IDirectDrawSurface* m_pText1Surface;
	IDirectDrawSurface* m_pText2Surface;
	IDirectDrawClipper* m_pClipper;
	IDirectDrawPalette* m_pPalette;
	PALETTEENTRY m_paletteEntries[256];
	PALETTEENTRY m_originalPaletteEntries[256];
	SIZE m_text1SizeOnSurface;
	SIZE m_text2SizeOnSurface;
	HWND m_hWndMain;
	HFONT m_hFont;
	BOOL m_bIgnoreWMSIZE;
	BOOL m_bPrimaryPalettized;
	BOOL m_bFullScreen;
	void* m_unk0x850;
	BOOL m_bOnlySystemMemory;
	BOOL m_bIsOnPrimaryDevice;
	ErrorHandler m_pErrorHandler;
	ErrorHandler m_pFatalErrorHandler;
	void* m_pErrorHandlerArg;
	void* m_pFatalErrorHandlerArg;
	int m_pauseCount;
	DeviceModesInfo* m_pCurrentDeviceModesList;
	DeviceModesInfo::Mode m_currentMode;
};

#endif // MXDIRECTDRAW_H
