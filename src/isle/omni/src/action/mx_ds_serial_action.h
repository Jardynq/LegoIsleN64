#pragma once

#include "mx_ds_multi_action.h"

class MxDSSerialAction : public MxDSMultiAction {
public:
	MxDSSerialAction();
	~MxDSSerialAction() override;

	void CopyFrom(MxDSSerialAction& p_dsSerialAction);
	MxDSSerialAction& operator=(MxDSSerialAction& p_dsSerialAction);

	static const char* ClassName() { return "MxDSSerialAction"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSSerialAction::ClassName()) ||
			   MxDSMultiAction::IsA(p_name);
	}

	MxLong GetDuration() override;
	void SetDuration(MxLong p_duration) override;
	MxDSAction* Clone() override;

	// MxDSSerialAction::`scalar deleting destructor'

private:
	MxDSActionListCursor* m_cursor;
	undefined4 m_unk0xa0;
	undefined4 m_unk0xa4;
};

