#ifndef LEGOLOOPINGANIMPRESENTER_H
#define LEGOLOOPINGANIMPRESENTER_H

#include "legoanimpresenter.h"

// VTABLE: LEGO1 0x100d4900
// SIZE 0xc0
class LegoLoopingAnimPresenter : public LegoAnimPresenter {
public:
	// FUNCTION: BETA10 0x1005c6f0
	static const char* HandlerClassName() {
		// STRING: LEGO1 0x100f0700
		return "LegoLoopingAnimPresenter";
	}

	// FUNCTION: LEGO1 0x1000c9a0
	// FUNCTION: BETA10 0x1005c6c0
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	// FUNCTION: LEGO1 0x1000c9b0
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, ClassName()) || LegoAnimPresenter::IsA(p_name);
	}

	void StreamingTickle() override; // vtable+0x20
	void PutFrame() override;        // vtable+0x6c

private:
	undefined4 m_unk0xbc; // 0xbc
};

// SYNTHETIC: LEGO1 0x1006d000
// LegoLoopingAnimPresenter::~LegoLoopingAnimPresenter

// SYNTHETIC: LEGO1 0x1000f440
// LegoLoopingAnimPresenter::`scalar deleting destructor'

#endif // LEGOLOOPINGANIMPRESENTER_H
