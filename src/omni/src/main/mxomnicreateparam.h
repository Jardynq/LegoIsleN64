#ifndef MXOMNICREATEPARAM_H
#define MXOMNICREATEPARAM_H

#include "mxomnicreateflags.h"
#include "mxparam.h"
#include "mxstring.h"
#include "mxvideoparam.h"

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
