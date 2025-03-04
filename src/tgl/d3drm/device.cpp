#include "impl.h"

#include <d3drmwin.h>

using namespace TglImpl;

void* DeviceImpl::ImplementationDataPtr() {
	return reinterpret_cast<void*>(&m_data);
}

unsigned int DeviceImpl::GetWidth() {
	return m_data->GetWidth();
}

unsigned int DeviceImpl::GetHeight() {
	return m_data->GetHeight();
}

Result DeviceImpl::SetColorModel(ColorModel) {
	return Success;
}

Result DeviceImpl::SetShadingModel(ShadingModel model) {
	// Doesn't match well even though we know this is exactly
	// the original code thanks to the jump table.
	D3DRMRENDERQUALITY renderQuality = Translate(model);
	return ResultVal(m_data->SetQuality(renderQuality));
}

Result DeviceImpl::SetShadeCount(unsigned int shadeCount) {
	return ResultVal(m_data->SetShades(shadeCount));
}

Result DeviceImpl::SetDither(int dither) {
	return ResultVal(m_data->SetDither(dither));
}

void DeviceImpl::HandleActivate(WORD wParam) {
	// Device argument is intentionally unused.
	IDirect3DRMWinDevice* winDevice;
	if (ResultVal(m_data->QueryInterface(
			IID_IDirect3DRMWinDevice,
			(LPVOID*) &winDevice
		))) {
		winDevice->HandleActivate(wParam);
		winDevice->Release();
	}
}

void DeviceImpl::HandlePaint(HDC p_dc) {
	IDirect3DRMWinDevice* winDevice;
	if (SUCCEEDED(m_data->QueryInterface(
			IID_IDirect3DRMWinDevice,
			(LPVOID*) &winDevice
		))) {
		winDevice->HandlePaint(p_dc);
		winDevice->Release();
	}
}

Result DeviceImpl::Update() {
	return ResultVal(m_data->Update());
}

// IID_IDirect3DRMWinDevice
