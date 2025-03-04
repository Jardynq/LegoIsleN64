#ifndef MXDSEVENT_H
#define MXDSEVENT_H

#include "mxdsmediaaction.h"

class MxDSEvent : public MxDSMediaAction {
public:
	MxDSEvent();
	~MxDSEvent() override;

	void CopyFrom(MxDSEvent& p_dsEvent);
	MxDSEvent& operator=(MxDSEvent& p_dsEvent);

	const char* ClassName() const override { return "MxDSEvent"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxDSEvent::ClassName()) ||
			   MxDSMediaAction::IsA(p_name);
	}

	MxDSAction* Clone() override;

	// MxDSEvent::`scalar deleting destructor'
};

#endif // MXDSEVENT_H
