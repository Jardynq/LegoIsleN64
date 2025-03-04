#ifndef MXDSSTILL_H
#define MXDSSTILL_H

#include "mxdsmediaaction.h"

class MxDSStill : public MxDSMediaAction {
public:
	MxDSStill();
	~MxDSStill() override;

	void CopyFrom(MxDSStill& p_dsStill);
	MxDSStill& operator=(MxDSStill& p_dsStill);

	const char* ClassName() const override { return "MxDSStill"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxDSStill::ClassName()) ||
			   MxDSMediaAction::IsA(p_name);
	}

	MxDSAction* Clone() override;

	// MxDSStill::`scalar deleting destructor'
};

#endif // MXDSSTILL_H
