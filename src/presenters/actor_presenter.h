#ifndef LEGOACTORPRESENTER_H
#define LEGOACTORPRESENTER_H

#include "entity_presenter.h"

class LegoActorPresenter : public LegoEntityPresenter {
public:
	// LegoActorPresenter() {}

	~LegoActorPresenter() override {}

	static const char* HandlerClassName() { return "LegoActorPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoActorPresenter::ClassName()) ||
			   LegoEntityPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	void ParseExtra() override;
};

// LegoActorPresenter::`scalar deleting destructor'

#endif // LEGOACTORPRESENTER_H
