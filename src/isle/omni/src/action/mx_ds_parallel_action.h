#pragma once

#include "mx_ds_multi_action.h"

class MxDSParallelAction : public MxDSMultiAction {
public:
	MxDSParallelAction();
	~MxDSParallelAction() override;

	void CopyFrom(MxDSParallelAction& p_dsParallelAction);
	MxDSParallelAction& operator=(MxDSParallelAction& p_dsParallelAction);

	static const char* ClassName() { return "MxDSParallelAction"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSParallelAction::ClassName()) ||
			   MxDSMultiAction::IsA(p_name);
	}

	// MxDSParallelAction::`scalar deleting destructor'

	MxLong GetDuration() override;

	void SetDuration(MxLong p_duration) override { m_duration = p_duration; }

	MxDSAction* Clone() override;
};

