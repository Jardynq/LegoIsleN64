#pragma once

#include "mx_ds_media_action.h"

class MxDSStill : public MxDSMediaAction {
public:
	MxDSStill();
	~MxDSStill() override;

	void CopyFrom(MxDSStill& p_dsStill);
	MxDSStill& operator=(MxDSStill& p_dsStill);

	static const char* ClassName() { return "MxDSStill"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSStill::ClassName()) ||
			   MxDSMediaAction::IsA(p_name);
	}

	MxDSAction* Clone() override;

	// MxDSStill::`scalar deleting destructor'
};

