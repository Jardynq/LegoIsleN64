#ifndef _TglSurface_h
#define _TglSurface_h

#include "mxdirectx/mxstopwatch.h"
#include "tgl/tgl.h"

namespace Tgl {
class Renderer;
class Device;
class View;
class Group;
} // namespace Tgl

/////////////////////////////////////////////////////////////////////////////
// TglSurface

class TglSurface {
public:
	struct CreateStruct {
		const GUID* m_pDriverGUID;
		HWND m_hWnd;
		IDirectDraw* m_pDirectDraw;
		IDirectDrawSurface* m_pFrontBuffer;
		IDirectDrawSurface* m_pBackBuffer;
		IDirectDrawPalette* m_pPalette;
		BOOL m_isFullScreen;
		BOOL m_isWideViewAngle;
		IDirect3D2* m_direct3d;
		IDirect3DDevice2* m_d3dDevice;
	};

public:
	TglSurface();
	virtual ~TglSurface();

	virtual BOOL
	Create(const CreateStruct&, Tgl::Renderer*, Tgl::Group* pScene);
	virtual void Destroy();
	virtual double Render(); // render time in seconds

	Tgl::Renderer* GetRenderer() const { return m_pRenderer; }
	Tgl::Device* GetDevice() const { return m_pDevice; }

	Tgl::View* GetView() const { return m_pView; }

	Tgl::Group* GetScene() const { return m_pScene; }

	unsigned int GetWidth() const { return m_width; }

	unsigned int GetHeight() const { return m_height; }

	double GetRenderingRate() const { return m_renderingRateMeter.Frequency(); }
	double GetFrameRate() const { return m_frameRateMeter.Frequency(); }
	unsigned int GetFrameCount() const { return m_frameCount; }

protected:
	virtual Tgl::View* CreateView(Tgl::Renderer*, Tgl::Device*) = 0;
	virtual void DestroyView();

private:
	Tgl::Renderer* m_pRenderer;
	Tgl::Device* m_pDevice;
	Tgl::View* m_pView;
	Tgl::Group* m_pScene;
	unsigned int m_width;
	unsigned int m_height;
	BOOL m_isInitialized;
	BOOL m_stopRendering;
	// statistics
	MxFrequencyMeter m_renderingRateMeter;
	MxFrequencyMeter m_frameRateMeter;
	unsigned int m_frameCount;
};

/////////////////////////////////////////////////////////////////////////////

// TglSurface::`scalar deleting destructor'

#endif /* _TglSurface_h */
