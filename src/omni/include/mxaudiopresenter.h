#ifndef MXAUDIOPRESENTER_H
#define MXAUDIOPRESENTER_H

#include "mxmediapresenter.h"

class MxAudioPresenter : public MxMediaPresenter {
public:
	MxAudioPresenter() { m_volume = 100; }

	virtual MxS32 GetVolume() { return m_volume; }

	virtual void SetVolume(MxS32 p_volume) { m_volume = p_volume; }

	static const char* HandlerClassName() { return "MxAudioPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxAudioPresenter::ClassName()) ||
			   MxMediaPresenter::IsA(p_name);
	}

protected:
	MxS32 m_volume;
};

// MxAudioPresenter::`scalar deleting destructor'

// MxAudioPresenter::~MxAudioPresenter

#endif // MXAUDIOPRESENTER_H
