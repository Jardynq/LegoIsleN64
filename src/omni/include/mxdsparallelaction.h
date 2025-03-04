#ifndef MXDSPARALLELACTION_H
#define MXDSPARALLELACTION_H

#include "mxdsmultiaction.h"

class MxDSParallelAction : public MxDSMultiAction {
public:
	MxDSParallelAction();
	~MxDSParallelAction() override;

	void CopyFrom(MxDSParallelAction& p_dsParallelAction);
	MxDSParallelAction& operator=(MxDSParallelAction& p_dsParallelAction);

	const char* ClassName() const override { return "MxDSParallelAction"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxDSParallelAction::ClassName()) ||
			   MxDSMultiAction::IsA(p_name);
	}

	// MxDSParallelAction::`scalar deleting destructor'

	MxLong GetDuration() override;

	void SetDuration(MxLong p_duration) override { m_duration = p_duration; }

	MxDSAction* Clone() override;
};

#endif // MXDSPARALLELACTION_H
