#include "mx_ds_anim.h"

MxDSAnim::MxDSAnim() {
	this->SetType(e_anim);
}

MxDSAnim::~MxDSAnim() {
}

void MxDSAnim::CopyFrom(MxDSAnim& p_dsAnim) {
}

MxDSAnim& MxDSAnim::operator=(MxDSAnim& p_dsAnim) {
	if (this == &p_dsAnim) {
		return *this;
	}

	MxDSMediaAction::operator=(p_dsAnim);
	this->CopyFrom(p_dsAnim);
	return *this;
}

MxDSAction* MxDSAnim::Clone() {
	MxDSAnim* clone = new MxDSAnim();

	if (clone) {
		*clone = *this;
	}

	return clone;
}
