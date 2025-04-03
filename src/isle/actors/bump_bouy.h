#ifndef BUMPBOUY_H
#define BUMPBOUY_H

#include "anim_actor.h"

class BumpBouy : public LegoAnimActor {
public:
	BumpBouy();
	~BumpBouy() override;
	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "BumpBouy"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, BumpBouy::ClassName()) ||
			   LegoAnimActor::IsA(p_name);
	}

	// BumpBouy::`scalar deleting destructor'
};

// BumpBouy::`vbtable'

#endif // BUMPBOUY_H
