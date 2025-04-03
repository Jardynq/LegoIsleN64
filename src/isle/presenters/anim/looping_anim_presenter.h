#ifndef LEGOLOOPINGANIMPRESENTER_H
#define LEGOLOOPINGANIMPRESENTER_H

#include "anim_presenter.h"

class LegoLoopingAnimPresenter : public LegoAnimPresenter {
public:
	static const char* HandlerClassName() { return "LegoLoopingAnimPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, ClassName()) || LegoAnimPresenter::IsA(p_name);
	}

	void StreamingTickle() override;
	void PutFrame() override;

private:
	undefined4 m_unk0xbc;
};

// LegoLoopingAnimPresenter::~LegoLoopingAnimPresenter

// LegoLoopingAnimPresenter::`scalar deleting destructor'

#endif // LEGOLOOPINGANIMPRESENTER_H
