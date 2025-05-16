#pragma once

#include "mx_composite_presenter.h"

class MxCompositeMediaPresenter : public MxCompositePresenter {
public:
	MxCompositeMediaPresenter();
	~MxCompositeMediaPresenter() override;

	MxResult Tickle() override;

	static const char* ClassName() {

		return "MxCompositeMediaPresenter";
	}

	static MxBool IsA(const char* p_name) {
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

