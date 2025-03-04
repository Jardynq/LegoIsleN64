#ifndef MXDSOBJECTACTION_H
#define MXDSOBJECTACTION_H

#include "mxdsmediaaction.h"

class MxDSObjectAction : public MxDSMediaAction {
public:
	MxDSObjectAction();
	~MxDSObjectAction() override;

	MxDSObjectAction& operator=(MxDSObjectAction& p_dsObjectAction);

	const char* ClassName() const override { return "MxDSObjectAction"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxDSObjectAction::ClassName()) ||
			   MxDSMediaAction::IsA(p_name);
	}

	MxDSAction* Clone() override;
	virtual void CopyFrom(MxDSObjectAction& p_dsObjectAction);

	// MxDSObjectAction::`scalar deleting destructor'
};

#endif // MXDSOBJECTACTION_H
