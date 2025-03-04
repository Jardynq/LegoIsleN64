#ifndef LEGOLOOPINGANIMPRESENTER_H
#define LEGOLOOPINGANIMPRESENTER_H

#include "legoanimpresenter.h"

class LegoLoopingAnimPresenter : public LegoAnimPresenter {
public:
	static const char* HandlerClassName() { return "LegoLoopingAnimPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
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
