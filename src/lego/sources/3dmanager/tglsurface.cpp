// TglSurface.cpp : implementation file

#include "tglsurface.h"
#include "display.h"

using namespace Tgl;

/////////////////////////////////////////////////////////////////////////////
// TglSurface

TglSurface::TglSurface() {
	m_pRenderer = 0;
	m_pDevice = 0;
	m_pView = 0;
	m_pScene = 0;

	m_width = 0;
	m_height = 0;

	m_stopRendering = FALSE;
	m_isInitialized = FALSE;

	// statistics
	m_frameCount = 0;
}

TglSurface::~TglSurface() {
	Destroy();
}

void TglSurface::Destroy() {
	DestroyView();

	delete m_pDevice;
	m_pDevice = 0;

	m_pRenderer = 0;
	m_pScene = 0;
}

int GetBitsPerPixel() {
	// TODO: Verify this is correct
	return display_get_bitdepth() * 8;
}

BOOL TglSurface::Create(
	Renderer* pRenderer,
	Group* pScene
) {
	m_pRenderer = pRenderer;
	m_pScene = pScene;

	m_width = m_pDevice->GetWidth();
	m_height = m_pDevice->GetHeight();

	m_pView = CreateView(m_pRenderer, m_pDevice);
	if (!m_pView) {
		delete m_pDevice;
		m_pDevice = 0;
		m_pRenderer = 0;
		m_pScene = 0;
		return FALSE;
	}

	m_frameRateMeter.Reset();
	m_renderingRateMeter.Reset();
	m_frameRateMeter.StartOperation();

	m_isInitialized = TRUE;

	return TRUE;
}

void TglSurface::DestroyView() {
	delete m_pView;
	m_pView = 0;
}

double TglSurface::Render() {
	MxStopWatch renderTimer;

	if (m_isInitialized && !m_stopRendering) {
		Result result = Success;

		m_renderingRateMeter.StartOperation();
		renderTimer.Start();

		result = m_pView->Render(m_pScene);

		renderTimer.Stop();
		assert(Succeeded(result));
		m_renderingRateMeter.EndOperation();
		m_frameRateMeter.EndOperation();
		m_frameCount++;

#if 0
		// reset rate meters every 20 frames
		if ((++m_frameCount % 20) == 0)
#else
		// reset rate meters every 4 seconds
		if (m_frameRateMeter.ElapsedSeconds() > 4.0)
#endif
		{
			m_frameRateMeter.Reset();
			m_renderingRateMeter.Reset();
		}

		m_frameRateMeter.StartOperation();
	}

	return renderTimer.ElapsedSeconds();
}
