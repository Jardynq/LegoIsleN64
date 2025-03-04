#ifndef MXLOOPINGMIDIPRESENTER_H
#define MXLOOPINGMIDIPRESENTER_H

#include "mxmidipresenter.h"

class MxLoopingMIDIPresenter : public MxMIDIPresenter {
public:
	static const char* HandlerClassName() { return "MxLoopingMIDIPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxLoopingMIDIPresenter::ClassName()) ||
			   MxMIDIPresenter::IsA(p_name);
	}

	void StreamingTickle() override;
	void DoneTickle() override;
	MxResult PutData() override;
};

// MxLoopingMIDIPresenter::`scalar deleting destructor'

#endif // MXLOOPINGMIDIPRESENTER_H
