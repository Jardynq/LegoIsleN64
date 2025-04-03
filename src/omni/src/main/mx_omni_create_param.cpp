#include "mx_omni_create_param.h"

MxOmniCreateParam::MxOmniCreateParam(
	struct HWND__* p_windowHandle,
	MxVideoParam& p_vparam,
	MxOmniCreateFlags p_flags
) {
	this->m_windowHandle = (HWND) p_windowHandle;
	this->m_videoParam = p_vparam;
	this->m_createFlags = p_flags;
}
