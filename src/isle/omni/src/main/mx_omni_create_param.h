#ifndef MXOMNICREATEPARAM_H
#define MXOMNICREATEPARAM_H

#include "mx_omni_create_flags.h"
#include "mx_param.h"
#include "mx_string.h"
#include "mx_video_param.h"

class MxOmniCreateParam : public MxParam {
public:
	MxOmniCreateParam(MxVideoParam& p_vparam, MxOmniCreateFlags p_flags);

	MxOmniCreateFlags& CreateFlags() { return this->m_createFlags; }

	MxVideoParam& GetVideoParam() { return m_videoParam; }
	const MxVideoParam& GetVideoParam() const { return m_videoParam; }

	// MxOmniCreateParam::`scalar deleting destructor'

private:
	MxVideoParam m_videoParam;
	MxOmniCreateFlags m_createFlags;
};

// MxOmniCreateParam::~MxOmniCreateParam

#endif // MXOMNICREATEPARAM_H
