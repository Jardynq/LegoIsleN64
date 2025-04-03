// Lego3DView.cpp : implementation file
//

#include "3d_view.h"

#include "view_manager.h"

/////////////////////////////////////////////////////////////////////////////
// Lego3DView

Lego3DView::Lego3DView() {
	m_pViewManager = 0;
	m_previousRenderTime = 0;
	m_unk0x98 = 0;
	m_pPointOfView = 0;
}

Lego3DView::~Lego3DView() {
	Destroy();
}

BOOL Lego3DView::Create(
	Tgl::Renderer* pRenderer
) {
	double viewAngle = 90;

	float frontClippingDistance = 0.1;
	float backClippingDistance = 500;

	if (!LegoView1::Create(pRenderer)) {
		return FALSE;
	}

	assert(GetView());
	GetView()
		->SetFrustrum(frontClippingDistance, backClippingDistance, viewAngle);

	assert(GetScene());
	assert(!m_pViewManager);

	m_pViewManager = new ViewManager(pRenderer, GetScene(), 0);
	m_pViewManager->SetResolution(GetWidth(), GetHeight());
	m_pViewManager
		->SetFrustrum(viewAngle, frontClippingDistance, backClippingDistance);
	m_previousRenderTime = 0;
	m_unk0x98 = 0;

	// // NOTE: a derived class must inform view manager when it configures
	// //       its (Tgl) view: calling Tgl::View::SetFrustrum() should be
	// //       accompanied by calling ViewManager::SetFrustrum()

	return TRUE;
}

void Lego3DView::Destroy() {
	if (m_pPointOfView) {
		m_pPointOfView = 0;
		m_pViewManager->SetPOVSource(0);
	}

	delete m_pViewManager;
	m_pViewManager = 0;

	LegoView1::Destroy();
}

BOOL Lego3DView::Add(ViewROI& rROI) {
	assert(m_pViewManager);

	m_pViewManager->Add(&rROI);

	return TRUE;
}

BOOL Lego3DView::Remove(ViewROI& rROI) {
	assert(m_pViewManager);

	m_pViewManager->Remove(&rROI);

	if (m_pPointOfView == &rROI) {
		m_pPointOfView = 0;
		m_pViewManager->SetPOVSource(0);
	}

	return TRUE;
}

BOOL Lego3DView::SetPointOfView(ViewROI& rROI) {
	Matrix4 mat {0};
	Tgl::Result result = Tgl::Success;

	m_pPointOfView = &rROI;

	assert(m_pViewManager);
	m_pViewManager->SetPOVSource(m_pPointOfView);

	assert(GetCamera());
	rROI.GetLocalTransform(mat);
	result = GetCamera()->SetTransformation(mat);
	assert(Tgl::Succeeded(result));

	return TRUE;
}

BOOL Lego3DView::Moved(ViewROI& rROI) {
	assert(m_pViewManager);

	if (m_pPointOfView == &rROI) {
		// move the camera
		Matrix4 mat {0};
		Tgl::Result result = Tgl::Success;

		assert(GetCamera());

		rROI.GetLocalTransform(mat);
		result = GetCamera()->SetTransformation(mat);
		assert(Tgl::Succeeded(result));
		m_pViewManager->SetPOVSource(&rROI);
	}

	return TRUE;
}

double Lego3DView::Render(double p_und) {
	assert(m_pViewManager);
	m_pViewManager->Update(m_previousRenderTime, p_und);
	m_previousRenderTime = TglSurface::Render();
	return m_previousRenderTime;
}

ViewROI* Lego3DView::Pick(unsigned int x, unsigned int y) {
	return m_pViewManager->Pick(GetView(), x, y);
}
