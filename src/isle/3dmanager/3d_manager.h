#pragma once

#include "assert.h"
#include "3d_view.h"

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
	Lego3DManager();
	virtual ~Lego3DManager();

	BOOL Create();
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

