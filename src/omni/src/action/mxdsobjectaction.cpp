#include "mxdsobjectaction.h"

MxDSObjectAction::MxDSObjectAction() {
	this->SetType(e_objectAction);
}

MxDSObjectAction::~MxDSObjectAction() {
}

void MxDSObjectAction::CopyFrom(MxDSObjectAction& p_dsObjectAction) {
}

MxDSObjectAction& MxDSObjectAction::operator=(MxDSObjectAction& p_dsObjectAction
) {
	if (this == &p_dsObjectAction) {
		return *this;
	}

	MxDSMediaAction::operator=(p_dsObjectAction);
	this->CopyFrom(p_dsObjectAction);
	return *this;
}

MxDSAction* MxDSObjectAction::Clone() {
	MxDSObjectAction* clone = new MxDSObjectAction();

	if (clone) {
		*clone = *this;
	}

	return clone;
}
