#ifndef BUMPBOUY_H
#define BUMPBOUY_H

#include "legoanimactor.h"

class BumpBouy : public LegoAnimActor {
public:
	BumpBouy();
	~BumpBouy() override;
	MxLong Notify(MxParam& p_param) override;

	const char* ClassName() const override { return "BumpBouy"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, BumpBouy::ClassName()) ||
			   LegoAnimActor::IsA(p_name);
	}

	// BumpBouy::`scalar deleting destructor'
};

// BumpBouy::`vbtable'

#endif // BUMPBOUY_H
