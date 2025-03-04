#include "mxdsstill.h"

MxDSStill::MxDSStill() {
	this->SetType(e_still);
}

MxDSStill::~MxDSStill() {
}

void MxDSStill::CopyFrom(MxDSStill& p_dsStill) {
}

MxDSStill& MxDSStill::operator=(MxDSStill& p_dsStill) {
	if (this == &p_dsStill) {
		return *this;
	}

	MxDSMediaAction::operator=(p_dsStill);
	this->CopyFrom(p_dsStill);
	return *this;
}

MxDSAction* MxDSStill::Clone() {
	MxDSStill* clone = new MxDSStill();

	if (clone) {
		*clone = *this;
	}

	return clone;
}
