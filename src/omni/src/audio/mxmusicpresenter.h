#ifndef MXMUSICPRESENTER_H
#define MXMUSICPRESENTER_H

#include "mxaudiopresenter.h"

class MxMusicPresenter : public MxAudioPresenter {
public:
	MxMusicPresenter();
	~MxMusicPresenter() override;

	static const char* HandlerClassName() { return "MxMusicPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxMusicPresenter::ClassName()) ||
			   MxAudioPresenter::IsA(p_name);
	}

	MxResult AddToManager() override;
	void Destroy() override;

	// MxMusicPresenter::`scalar deleting destructor'

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);
};

#endif // MXMUSICPRESENTER_H
