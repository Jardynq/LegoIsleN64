#ifndef MXSOUNDPRESENTER_H
#define MXSOUNDPRESENTER_H

#include "mxaudiopresenter.h"

class MxSoundPresenter : public MxAudioPresenter {
public:
	~MxSoundPresenter() override { Destroy(TRUE); }

	void Destroy() override { Destroy(FALSE); }

	static const char* HandlerClassName() { return "MxSoundPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxSoundPresenter::ClassName()) ||
			   MxAudioPresenter::IsA(p_name);
	}

	MxResult AddToManager() override;

	// MxSoundPresenter::`scalar deleting destructor'

protected:
	void Destroy(MxBool p_fromDestructor);
};

#endif // MXSOUNDPRESENTER_H
