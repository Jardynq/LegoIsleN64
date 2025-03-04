#ifndef MXCOMPOSITEMEDIAPRESENTER_H
#define MXCOMPOSITEMEDIAPRESENTER_H

#include "mxcompositepresenter.h"

class MxCompositeMediaPresenter : public MxCompositePresenter {
public:
	MxCompositeMediaPresenter();
	~MxCompositeMediaPresenter() override;

	MxResult Tickle() override;

	const char* ClassName() const override {

		return "MxCompositeMediaPresenter";
	}

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxCompositeMediaPresenter::ClassName()) ||
			   MxCompositePresenter::IsA(p_name);
	}

	void StartingTickle() override;
	MxResult StartAction(MxStreamController*, MxDSAction* p_action) override;
	MxResult PutData() override;

private:
	MxS16 m_unk0x4c;
	MxBool m_unk0x4e;
};

// MxCompositeMediaPresenter::`scalar deleting destructor'

#endif // MXCOMPOSITEMEDIAPRESENTER_H
