#include "display.h"
#include "impl.h"

using namespace TglImpl;

void* DeviceImpl::ImplementationDataPtr() {
	return reinterpret_cast<void*>(&m_data);
}

unsigned int DeviceImpl::GetWidth() {
	return display_get_width();
}

unsigned int DeviceImpl::GetHeight() {
	return display_get_height();
}

Result DeviceImpl::SetColorModel(ColorModel) {
	return Success;
}

Result DeviceImpl::SetShadingModel(ShadingModel model) {
	(void)model;
	return Success;
}

Result DeviceImpl::SetShadeCount(unsigned int shadeCount) {
	(void)shadeCount;
	return Success;
}

Result DeviceImpl::SetDither(int dither) {
	(void)dither;
	return Success;
}

void DeviceImpl::HandleActivate(WORD wParam) {
	(void)wParam;
}

void DeviceImpl::HandlePaint(HDC p_dc) {
	(void)p_dc;
}

Result DeviceImpl::Update() {
	// TODO might have to flush render pipeline here.
	//return ResultVal(m_data->Update());
	return Success;
}

// IID_IDirect3DRMWinDevice
