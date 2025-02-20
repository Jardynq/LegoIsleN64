#include "mxomnicreateparam.h"

#include "utils.h"


// FUNCTION: LEGO1 0x100b0b00
// FUNCTION: BETA10 0x10130b6b
MxOmniCreateParam::MxOmniCreateParam(
	struct HWND__* p_windowHandle,
	MxVideoParam& p_vparam,
	MxOmniCreateFlags p_flags
) {
	this->m_windowHandle = (HWND)p_windowHandle;
	this->m_videoParam = p_vparam;
	this->m_createFlags = p_flags;
}
