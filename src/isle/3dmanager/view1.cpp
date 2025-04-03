// LegoView1.cpp : implementation file
//

#include "view1.h"

#include "mx_geometry_3d.h"
#include "mx_matrix.h"
#include "realtime.h"

#include <vec.h>

float g_sunLightRGB = 1.0;

float g_directionalLightRGB = 1.0;

float g_ambientLightRGB = 0.3;

/////////////////////////////////////////////////////////////////////////////
// LegoView

LegoView::LegoView() {
	m_pScene = 0;
	m_pCamera = 0;
}

LegoView::~LegoView() {
	Destroy();
}

BOOL LegoView::Create(
	Tgl::Renderer* pRenderer
) {
	float viewAngle = 90;

	float frontClippingDistance = 0.1;
	float backClippingDistance = 500;

	assert(!m_pScene);
	assert(!m_pCamera);
	assert(pRenderer);

	m_pScene = pRenderer->CreateGroup();
	assert(m_pScene);
	// TglSurface::Create() calls CreateView(), and we need the camera in
	// CreateView(), so create camera before calling TglSurface::Create()
	m_pCamera = pRenderer->CreateCamera();
	assert(m_pCamera);

	if (!TglSurface::Create(pRenderer, m_pScene)) {
		delete m_pScene;
		m_pScene = 0;

		delete m_pCamera;
		m_pCamera = 0;

		return FALSE;
	}

	assert(GetView());
	GetView()
		->SetFrustrum(frontClippingDistance, backClippingDistance, viewAngle);
	GetView()->SetBackgroundColor(.223, .639, .851);

	return TRUE;
}

Tgl::View*
LegoView::CreateView(Tgl::Renderer* pRenderer, Tgl::Device* pDevice) {
	assert(pRenderer);
	assert(pDevice);

	return pRenderer
		->CreateView(pDevice, m_pCamera, 0, 0, GetWidth(), GetHeight());
}

void LegoView::Destroy() {
	delete m_pScene;
	m_pScene = 0;

	delete m_pCamera;
	m_pCamera = 0;

	TglSurface::Destroy();
}

/////////////////////////////////////////////////////////////////////////////
// LegoView1

LegoView1::LegoView1() {
	m_pSunLight = 0;
	m_pDirectionalLight = 0;
	m_pAmbientLight = 0;
}

LegoView1::~LegoView1() {
	Destroy();
}

BOOL LegoView1::AddLightsToViewport() {
	assert(GetView());
	GetView()->Add(m_pSunLight);
	GetView()->Add(m_pDirectionalLight);
	GetView()->Add(m_pAmbientLight);
	return TRUE;
}

BOOL LegoView1::Create(
	Tgl::Renderer* pRenderer
) {
	if (!LegoView::Create(pRenderer)) {
		return FALSE;
	}

	// lights
	m_pSunLight = pRenderer->CreateLight(
		Tgl::Point,
		g_sunLightRGB,
		g_sunLightRGB,
		g_sunLightRGB
	);
	m_pDirectionalLight = pRenderer->CreateLight(
		Tgl::Directional,
		g_directionalLightRGB,
		g_directionalLightRGB,
		g_directionalLightRGB
	);
	m_pAmbientLight = pRenderer->CreateLight(
		Tgl::Ambient,
		g_ambientLightRGB,
		g_ambientLightRGB,
		g_ambientLightRGB
	);

	Mx3DPointFloat position(0.0, 0.0, 0.0);
	Mx3DPointFloat direction(0.0, -1.0, 0.0);
	Mx3DPointFloat up(1.0, 0.0, 0.0);

	Matrix4 matrix {0};
	MxMatrix transform;

	CalcLocalTransform(position, direction, up, transform);
	matrix = transform;
	m_pDirectionalLight->SetTransformation(matrix);

	position[0] = 0, position[1] = 150, position[2] = -150;
	CalcLocalTransform(position, direction, up, transform);
	matrix = transform;
	m_pSunLight->SetTransformation(matrix);

	return AddLightsToViewport();
}

void LegoView1::Destroy() {
	if (m_pSunLight) {
		GetView()->Remove(m_pSunLight);
		delete m_pSunLight;
		m_pSunLight = 0;
	}

	if (m_pDirectionalLight) {
		GetView()->Remove(m_pDirectionalLight);
		delete m_pDirectionalLight;
		m_pDirectionalLight = 0;
	}

	if (m_pAmbientLight) {
		GetView()->Remove(m_pAmbientLight);
		delete m_pAmbientLight;
		m_pAmbientLight = 0;
	}

	LegoView::Destroy();
}

void LegoView1::SetLightTransform(
	BOOL bDirectionalLight,
	Matrix4& rMatrix
) {
	Tgl::Light* pLight = nullptr;

	if (bDirectionalLight == FALSE) {
		pLight = m_pSunLight;
	} else {
		pLight = m_pDirectionalLight;
	}

	SetLightTransform(pLight, rMatrix);
}

void LegoView1::SetLightTransform(
	Tgl::Light* pLight,
	Matrix4& rMatrix
) {
	pLight->SetTransformation(rMatrix);
}

void LegoView1::SetLightColor(
	BOOL bDirectionalLight,
	float red,
	float green,
	float blue
) {
	Tgl::Light* pLight = nullptr;

	if (bDirectionalLight == FALSE) {
		pLight = m_pSunLight;
	} else {
		pLight = m_pDirectionalLight;
	}

	SetLightColor(pLight, red, green, blue);
}

void LegoView1::SetLightColor(
	Tgl::Light* pLight,
	float red,
	float green,
	float blue
) {
	pLight->SetColor(red, green, blue);
}
