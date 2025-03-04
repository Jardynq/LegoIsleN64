#ifndef MXDSSERIALACTION_H
#define MXDSSERIALACTION_H

#include "mxdsmultiaction.h"

class MxDSSerialAction : public MxDSMultiAction {
public:
	MxDSSerialAction();
	~MxDSSerialAction() override;

	void CopyFrom(MxDSSerialAction& p_dsSerialAction);
	MxDSSerialAction& operator=(MxDSSerialAction& p_dsSerialAction);

	const char* ClassName() const override { return "MxDSSerialAction"; }

	MxBool IsA(const char* p_name) const override {
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

#endif // MXDSSERIALACTION_H
