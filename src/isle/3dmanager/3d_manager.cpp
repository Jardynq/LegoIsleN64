// Lego3DManager.cpp : implementation file
//
#include "3d_manager.h"

#include "view_lod_list.h"
#include "view_manager.h"

//////////////////////////////////////////////////////////////////////////////

Lego3DManager::Lego3DManager() {
	// Tgl things
	m_pRenderer = 0;

	m_pLego3DView = 0;
	m_pViewLODListManager = 0;
}

Lego3DManager::~Lego3DManager() {
	Destroy();
}

BOOL Lego3DManager::Create() {
	BOOL result = Tgl::Success;

	assert(!m_pViewLODListManager);
	assert(!m_pRenderer);
	assert(!m_pLego3DView);

	m_pViewLODListManager = new ViewLODListManager;
	assert(m_pViewLODListManager);

	m_pRenderer = Tgl::CreateRenderer();
	assert(m_pRenderer);

	m_pLego3DView = new Lego3DView;

	result = m_pLego3DView->Create(m_pRenderer);
	assert(result);

	return result;
}

void Lego3DManager::Destroy() {
	delete m_pLego3DView;
	m_pLego3DView = 0;

	delete m_pRenderer;
	m_pRenderer = 0;

	delete m_pViewLODListManager;
	m_pViewLODListManager = 0;
}

double Lego3DManager::Render(double p_und) {
	assert(m_pLego3DView);

	return m_pLego3DView->Render(p_und);
}

int Lego3DManager::SetFrustrum(float p_fov, float p_front, float p_back) {
	m_pLego3DView->GetView()->SetFrustrum(p_front, p_back, p_fov);
	m_pLego3DView->GetViewManager()->SetFrustrum(p_fov, p_front, p_back);
	return 0;
}
