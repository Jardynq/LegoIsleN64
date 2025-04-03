#ifndef MXDSMULTIACTION_H
#define MXDSMULTIACTION_H

#include "mx_ds_action.h"
#include "mx_ds_action_list.h"

class MxDSMultiAction : public MxDSAction {
public:
	MxDSMultiAction();
	~MxDSMultiAction() override;

	void CopyFrom(MxDSMultiAction& p_dsMultiAction);
	MxDSMultiAction& operator=(MxDSMultiAction& p_dsMultiAction);

	static const char* ClassName() { return "MxDSMultiAction"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSMultiAction::ClassName()) ||
			   MxDSAction::IsA(p_name);
	}

	undefined4 VTable0x14() override;
	MxU32 GetSizeOnDisk() override;
	void Deserialize(MxU8*& p_source, MxS16 p_unk0x24) override;
	void SetAtomId(MxAtomId p_atomId) override;
	MxDSAction* Clone() override;
	void MergeFrom(MxDSAction& p_dsAction) override;
	MxBool HasId(MxU32 p_objectId) override;
	void SetUnknown90(MxLong p_unk0x90) override;

	MxDSActionList* GetActionList() const { return m_actions; }

	// MxDSMultiAction::`scalar deleting destructor'

protected:
	MxU32 m_sizeOnDisk;
	MxDSActionList* m_actions;
};

// MxDSActionListCursor::`scalar deleting destructor'

// MxListCursor<MxDSAction *>::~MxListCursor<MxDSAction *>

// MxListCursor<MxDSAction *>::`scalar deleting destructor'

// MxDSActionListCursor::~MxDSActionListCursor

#endif // MXDSMULTIACTION_H
