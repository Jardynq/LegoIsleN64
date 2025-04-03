#ifndef MXDSEVENT_H
#define MXDSEVENT_H

#include "mx_ds_media_action.h"

class MxDSEvent : public MxDSMediaAction {
public:
	MxDSEvent();
	~MxDSEvent() override;

	void CopyFrom(MxDSEvent& p_dsEvent);
	MxDSEvent& operator=(MxDSEvent& p_dsEvent);

	static const char* ClassName() { return "MxDSEvent"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSEvent::ClassName()) ||
			   MxDSMediaAction::IsA(p_name);
	}

	MxDSAction* Clone() override;

	// MxDSEvent::`scalar deleting destructor'
};

#endif // MXDSEVENT_H
