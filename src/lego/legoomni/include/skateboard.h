#ifndef SKATEBOARD_H
#define SKATEBOARD_H

#include "islepathactor.h"

class Act1State;

class SkateBoard : public IslePathActor {
public:
	SkateBoard();
	~SkateBoard() override;

	const char* ClassName() const override { return "SkateBoard"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, SkateBoard::ClassName()) ||
			   IslePathActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	MxLong HandleClick() override;
	MxLong HandleNotification0() override;
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;
	void Exit() override;

	void SetPizzaVisible(MxBool p_pizzaVisible) {
		m_pizzaVisible = p_pizzaVisible;
	}

	void ActivateSceneActions();
	void EnableScenePresentation(MxBool p_enable);

	// SkateBoard::`scalar deleting destructor'

private:
	MxBool m_pizzaVisible;
	Act1State* m_act1state;
};

#endif // SKATEBOARD_H
