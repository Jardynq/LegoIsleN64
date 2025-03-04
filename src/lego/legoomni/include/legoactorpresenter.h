#ifndef LEGOACTORPRESENTER_H
#define LEGOACTORPRESENTER_H

#include "legoentitypresenter.h"

class LegoActorPresenter : public LegoEntityPresenter {
public:
	// LegoActorPresenter() {}

	~LegoActorPresenter() override {}

	static const char* HandlerClassName() { return "LegoActorPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoActorPresenter::ClassName()) ||
			   LegoEntityPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	void ParseExtra() override;
};

// LegoActorPresenter::`scalar deleting destructor'

#endif // LEGOACTORPRESENTER_H
