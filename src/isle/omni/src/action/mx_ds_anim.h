#ifndef MXDSANIM_H
#define MXDSANIM_H

#include "mx_ds_media_action.h"

class MxDSAnim : public MxDSMediaAction {
public:
	MxDSAnim();
	~MxDSAnim() override;

	void CopyFrom(MxDSAnim& p_dsAnim);
	MxDSAnim& operator=(MxDSAnim& p_dsAnim);

	static const char* ClassName() { return "MxDSAnim"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSAnim::ClassName()) ||
			   MxDSMediaAction::IsA(p_name);
	}

	MxDSAction* Clone() override;

	// MxDSAnim::`scalar deleting destructor'
};

#endif // MXDSANIM_H
