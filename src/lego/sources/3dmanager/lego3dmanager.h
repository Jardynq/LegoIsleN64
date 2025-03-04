#ifndef _Lego3DManager_h
#define _Lego3DManager_h

#include "assert.h"
#include "lego3dview.h"

namespace Tgl {
class Renderer;
class Group;
} // namespace Tgl

class ViewROI;

// ??? for now
class ViewLODListManager;

/////////////////////////////////////////////////////////////////////////////
//
// Lego3DManager

class Lego3DManager {
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
	Lego3DManager();
	virtual ~Lego3DManager();

	BOOL Create(CreateStruct&);
	void Destroy();

	BOOL Add(ViewROI&);
	BOOL Remove(ViewROI&);
	BOOL Moved(ViewROI&);
	BOOL SetPointOfView(ViewROI&);

	double Render(double p_und);

	int SetFrustrum(float p_fov, float p_front, float p_back);

	Tgl::Renderer* GetRenderer();
	Tgl::Group* GetScene();
	Lego3DView* GetLego3DView();
	// ??? for now
	ViewLODListManager* GetViewLODListManager();

	// Lego3DManager::`scalar deleting destructor'

private:
	Tgl::Renderer* m_pRenderer;
	Lego3DView* m_pLego3DView;
	ViewLODListManager* m_pViewLODListManager;
};

/////////////////////////////////////////////////////////////////////////////
//
// Lego3DManager implementaion

inline BOOL Lego3DManager::Add(ViewROI& rROI) {
	assert(m_pLego3DView);

	return m_pLego3DView->Add(rROI);
}

inline BOOL Lego3DManager::Remove(ViewROI& rROI) {
	assert(m_pLego3DView);

	return m_pLego3DView->Remove(rROI);
}

inline BOOL Lego3DManager::SetPointOfView(ViewROI& rROI) {
	assert(m_pLego3DView);

	return m_pLego3DView->SetPointOfView(rROI);
}

inline BOOL Lego3DManager::Moved(ViewROI& rROI) {
	assert(m_pLego3DView);

	return m_pLego3DView->Moved(rROI);
}

inline Tgl::Renderer* Lego3DManager::GetRenderer() {
	return m_pRenderer;
}

inline Tgl::Group* Lego3DManager::GetScene() {
	assert(m_pLego3DView);

	return m_pLego3DView->GetScene();
}

inline Lego3DView* Lego3DManager::GetLego3DView() {
	return m_pLego3DView;
}

inline ViewLODListManager* Lego3DManager::GetViewLODListManager() {
	return m_pViewLODListManager;
}

#endif /* _Lego3DManager_h */
