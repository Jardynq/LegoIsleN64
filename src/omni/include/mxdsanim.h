#ifndef MXDSANIM_H
#define MXDSANIM_H

#include "mxdsmediaaction.h"

class MxDSAnim : public MxDSMediaAction {
public:
	MxDSAnim();
	~MxDSAnim() override;

	void CopyFrom(MxDSAnim& p_dsAnim);
	MxDSAnim& operator=(MxDSAnim& p_dsAnim);

	const char* ClassName() const override { return "MxDSAnim"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxDSAnim::ClassName()) ||
			   MxDSMediaAction::IsA(p_name);
	}

	MxDSAction* Clone() override;

	// MxDSAnim::`scalar deleting destructor'
};

#endif // MXDSANIM_H
