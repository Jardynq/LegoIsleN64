#include "impl.h"

using namespace TglImpl;

struct ViewportAppData {
	ViewportAppData(IDirect3DRM2* pRenderer);
	~ViewportAppData();

	IDirect3DRMFrame2* m_pLightFrame;
	IDirect3DRMFrame2* m_pCamera;
	IDirect3DRMFrame2* m_pLastRenderedFrame;
	float m_backgroundColorRed;
	float m_backgroundColorGreen;
	float m_backgroundColorBlue;
};

ViewportAppData::ViewportAppData(IDirect3DRM2* pRenderer) {
	pRenderer->CreateFrame(NULL, &m_pLightFrame);
	m_pCamera = NULL;
	m_pLastRenderedFrame = NULL;
	m_backgroundColorRed = 0.0f;
	m_backgroundColorGreen = 0.0f;
	m_backgroundColorBlue = 0.0f;
}

ViewportAppData::~ViewportAppData() {
	IDirect3DRMFrameArray* pChildFrames;
	IDirect3DRMFrame* pChildFrame = NULL;
	m_pLightFrame->GetChildren(&pChildFrames);
	for (int i = 0; i < (int) pChildFrames->GetSize(); i++) {
		pChildFrames->GetElement(i, &pChildFrame);
		m_pLightFrame->DeleteChild(pChildFrame);
		pChildFrame->Release(); // GetElement() does AddRef()
	}
	pChildFrames->Release();
	m_pLightFrame->Release();
}

// Forward declare to satisfy order check
void ViewportDestroyCallback(IDirect3DRMObject* pObject, void* pArg);

Result ViewImpl::ViewportCreateAppData(
	IDirect3DRM2* pDevice,
	IDirect3DRMViewport* pView,
	IDirect3DRMFrame2* pCamera
) {
	ViewportAppData* data = new ViewportAppData(pDevice);
	data->m_pCamera = pCamera;
	Result result =
		ResultVal(pView->SetAppData(reinterpret_cast<LPD3DRM_APPDATA>(data)));
	if (Succeeded(result)) {
		result =
			ResultVal(pView->AddDestroyCallback(ViewportDestroyCallback, data));
	}
	if (!Succeeded(result)) {
		delete data;
		pView->SetAppData(0);
	}
	return result;
}

inline Result ViewRestoreFrameAfterRender(
	IDirect3DRMFrame* pFrame,
	IDirect3DRMFrame* pCamera,
	IDirect3DRMFrame* pLightFrame
) {
	Result result = Success;
	if (pFrame) {
		// remove camera and light frame from frame that was rendered
		// this doesn't destroy the camera as it is still the camera of the
		// viewport...
		result = ResultVal(pFrame->DeleteChild(pCamera));
		result = ResultVal(pFrame->DeleteChild(pLightFrame));

		// decrease frame's ref count (it was increased in
		// ViewPrepareFrameForRender())
		pFrame->Release();
	}
	return result;
}

// FIXME: from LEGO1/tgl/d3drm/view.cpp

void ViewportDestroyCallback(IDirect3DRMObject* pObject, void* pArg) {
	ViewportAppData* pViewportAppData =
		reinterpret_cast<ViewportAppData*>(pArg);

	ViewRestoreFrameAfterRender(
		pViewportAppData->m_pLastRenderedFrame,
		pViewportAppData->m_pCamera,
		pViewportAppData->m_pLightFrame
	);

	delete pViewportAppData;
}

Result ViewportPickImpl(
	IDirect3DRMViewport* pViewport,
	int x,
	int y,
	const Group** ppGroupsToPickFrom,
	int groupsToPickFromCount,
	const Group**& rppPickedGroups,
	int& rPickedGroupCount
) {
	// Left unimplemented in shipped game.
	return Error;
}

inline ViewportAppData* ViewportGetData(IDirect3DRMViewport* pViewport) {
	return reinterpret_cast<ViewportAppData*>(pViewport->GetAppData());
}

inline IDirect3DRMFrame* ViewportGetLightFrame(IDirect3DRMViewport* pViewport) {
	return ViewportGetData(pViewport)->m_pLightFrame;
}

void* ViewImpl::ImplementationDataPtr() {
	return reinterpret_cast<void*>(&m_data);
}

Result ViewImpl::Add(const Light* pLight) {
	const LightImpl* light = static_cast<const LightImpl*>(pLight);
	IDirect3DRMFrame* frame = light->ImplementationData();
	return ResultVal(ViewportGetLightFrame(m_data)->AddChild(frame));
}

Result ViewImpl::Remove(const Light* pLight) {
	const LightImpl* light = static_cast<const LightImpl*>(pLight);
	IDirect3DRMFrame* frame = light->ImplementationData();
	return ResultVal(ViewportGetLightFrame(m_data)->DeleteChild(frame));
}

Result ViewImpl::SetCamera(const Camera* pCamera) {
	const CameraImpl* camera = static_cast<const CameraImpl*>(pCamera);
	IDirect3DRMFrame2* frame = camera->ImplementationData();

	ViewportAppData* pViewportAppData;
	Result result;

	pViewportAppData = reinterpret_cast<ViewportAppData*>(m_data->GetAppData());
	result = ViewRestoreFrameAfterRender(
		pViewportAppData->m_pLastRenderedFrame,
		pViewportAppData->m_pCamera,
		pViewportAppData->m_pLightFrame
	);
	pViewportAppData->m_pCamera = frame;
	pViewportAppData->m_pLastRenderedFrame = 0;

	return ResultVal(m_data->SetCamera(frame));
}

Result ViewImpl::SetProjection(ProjectionType type) {
	return ResultVal(m_data->SetProjection(Translate(type)));
}

Result ViewImpl::SetFrustrum(
	float frontClippingDistance,
	float backClippingDistance,
	float degrees
) {
	float field = frontClippingDistance * tan(DegreesToRadians(degrees / 2));
	Result result;
	result = ResultVal(m_data->SetFront(frontClippingDistance));
	if (Succeeded(result)) {
		result = ResultVal(m_data->SetBack(backClippingDistance));
	}
	if (Succeeded(result)) {
		result = ResultVal(m_data->SetField(field));
	}

	return result;
}

Result ViewImpl::SetBackgroundColor(float r, float g, float b) {
	Result ret = Success;
	// Note, this method in the shipped game is very diverged from
	// the Tgl leak code.
	ViewportAppData* data = ViewportGetData(m_data);
	data->m_backgroundColorRed = r;
	data->m_backgroundColorGreen = g;
	data->m_backgroundColorBlue = b;
	if (data->m_pLastRenderedFrame) {
		ret =
			ResultVal(data->m_pLastRenderedFrame->SetSceneBackgroundRGB(r, g, b)
			);
	}
	return ret;
}

Result ViewImpl::GetBackgroundColor(float* r, float* g, float* b) {
	ViewportAppData* data = ViewportGetData(m_data);
	*r = data->m_backgroundColorRed;
	*g = data->m_backgroundColorGreen;
	*b = data->m_backgroundColorBlue;
	return Success;
}

Result ViewImpl::Clear() {
	return ResultVal(m_data->Clear());
}

inline Result ViewPrepareFrameForRender(
	IDirect3DRMFrame* pFrame,
	IDirect3DRMFrame* pCamera,
	IDirect3DRMFrame* pLightFrame,
	float backgroundRed,
	float backgroundGreen,
	float backgroundBlue
) {
	Result result = Success;

	if (pFrame) {
		// set background color
		result = ResultVal(pFrame->SetSceneBackgroundRGB(
			backgroundRed,
			backgroundGreen,
			backgroundBlue
		));

		// add camera to frame to be rendered
		result = ResultVal(pFrame->AddChild(pCamera));

		// add light frame to frame to be rendered
		result = ResultVal(pFrame->AddChild(pLightFrame));

		// increase ref count of frame to ensure it does not get deleted
		// underneath us
		pFrame->AddRef();
	}

	return result;
}

inline Result
ViewRender(IDirect3DRMViewport* pViewport, const IDirect3DRMFrame2* pGroup) {
	ViewportAppData* pViewportAppData;
	Result result;

	pViewportAppData =
		reinterpret_cast<ViewportAppData*>(pViewport->GetAppData());

	if (pViewportAppData->m_pLastRenderedFrame != pGroup) {
		result = ViewRestoreFrameAfterRender(
			pViewportAppData->m_pLastRenderedFrame,
			pViewportAppData->m_pCamera,
			pViewportAppData->m_pLightFrame
		);

		pViewportAppData->m_pLastRenderedFrame =
			const_cast<IDirect3DRMFrame2*>(pGroup);

		result = ViewPrepareFrameForRender(
			pViewportAppData->m_pLastRenderedFrame,
			pViewportAppData->m_pCamera,
			pViewportAppData->m_pLightFrame,
			pViewportAppData->m_backgroundColorRed,
			pViewportAppData->m_backgroundColorGreen,
			pViewportAppData->m_backgroundColorBlue
		);
	}

	result =
		ResultVal(pViewport->Render(const_cast<IDirect3DRMFrame2*>(pGroup)));
	return result;
}

Result ViewImpl::Render(const Group* pGroup) {
	return ViewRender(
		m_data,
		static_cast<const GroupImpl*>(pGroup)->ImplementationData()
	);
}

Result ViewImpl::ForceUpdate(
	unsigned int x,
	unsigned int y,
	unsigned int width,
	unsigned int height
) {
	return ResultVal(m_data->ForceUpdate(x, y, x + width - 1, y + height - 1));
}

Result ViewImpl::Pick(
	unsigned int x,
	unsigned int y,
	const Group** ppGroupsToPickFrom,
	int groupsToPickFromCount,
	const Group**& rppPickedGroups,
	int& rPickedGroupCount
) {
	return ViewportPickImpl(
		m_data,
		x,
		y,
		ppGroupsToPickFrom,
		groupsToPickFromCount,
		rppPickedGroups,
		rPickedGroupCount
	);
}

Result ViewImpl::TransformWorldToScreen(const float world[3], float screen[4]) {
	D3DRMVECTOR4D d3dRMScreen;
	D3DVECTOR d3dRMWorld;
	d3dRMWorld.x = world[0];
	d3dRMWorld.y = world[1];
	d3dRMWorld.z = world[2];
	Result result;

	result = ResultVal(m_data->Transform(&d3dRMScreen, &d3dRMWorld));

	if (Succeeded(result)) {
		screen[0] = d3dRMScreen.x;
		screen[1] = d3dRMScreen.y;
		screen[2] = d3dRMScreen.z;
		screen[3] = d3dRMScreen.w;
	}

	return result;
}

Result ViewImpl::TransformScreenToWorld(const float screen[4], float world[3]) {
	// 100% match minus instruction reordering.
	D3DVECTOR d3dRMWorld;
	D3DRMVECTOR4D d3dScreen;
	d3dScreen.x = screen[0];
	d3dScreen.y = screen[1];
	d3dScreen.z = screen[2];
	d3dScreen.w = screen[3];
	Result result;

	result = ResultVal(m_data->InverseTransform(&d3dRMWorld, &d3dScreen));

	if (Succeeded(result)) {
		world[0] = d3dRMWorld.x;
		world[1] = d3dRMWorld.y;
		world[2] = d3dRMWorld.z;
	}

	return result;
}
