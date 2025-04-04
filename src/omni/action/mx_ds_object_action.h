#pragma once

#include "mx_ds_media_action.h"

class MxDSObjectAction : public MxDSMediaAction {
public:
	MxDSObjectAction();
	~MxDSObjectAction() override;

	MxDSObjectAction& operator=(MxDSObjectAction& p_dsObjectAction);

	static const char* ClassName() { return "MxDSObjectAction"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSObjectAction::ClassName()) ||
			   MxDSMediaAction::IsA(p_name);
	}

	MxDSAction* Clone() override;
	virtual void CopyFrom(MxDSObjectAction& p_dsObjectAction);

	// MxDSObjectAction::`scalar deleting destructor'
};

