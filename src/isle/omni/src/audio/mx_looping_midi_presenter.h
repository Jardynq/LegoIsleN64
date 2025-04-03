#pragma once

#include "mx_midi_presenter.h"

class MxLoopingMIDIPresenter : public MxMIDIPresenter {
public:
	static const char* HandlerClassName() { return "MxLoopingMIDIPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxLoopingMIDIPresenter::ClassName()) ||
			   MxMIDIPresenter::IsA(p_name);
	}

	void StreamingTickle() override;
	void DoneTickle() override;
	MxResult PutData() override;
};

// MxLoopingMIDIPresenter::`scalar deleting destructor'

