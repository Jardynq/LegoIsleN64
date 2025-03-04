#include "mxdsmultiaction.h"

MxDSMultiAction::MxDSMultiAction() {
	this->SetType(e_multiAction);
	this->m_actions = new MxDSActionList;
	this->m_actions->SetDestroy(MxDSActionList::Destroy);
}

MxDSMultiAction::~MxDSMultiAction() {
	if (this->m_actions) {
		delete this->m_actions;
	}
}

void MxDSMultiAction::CopyFrom(MxDSMultiAction& p_dsMultiAction) {
	this->m_actions->DeleteAll();

	MxDSActionListCursor cursor(p_dsMultiAction.m_actions);
	MxDSAction* action;
	while (cursor.Next(action)) {
		this->m_actions->Append(action->Clone());
	}
}

MxDSMultiAction& MxDSMultiAction::operator=(MxDSMultiAction& p_dsMultiAction) {
	if (this == &p_dsMultiAction) {
		return *this;
	}

	MxDSAction::operator=(p_dsMultiAction);
	this->CopyFrom(p_dsMultiAction);
	return *this;
}

void MxDSMultiAction::SetUnknown90(MxLong p_unk0x90) {
	this->m_unk0x90 = p_unk0x90;

	MxDSActionListCursor cursor(this->m_actions);
	MxDSAction* action;
	while (cursor.Next(action)) {
		action->SetUnknown90(p_unk0x90);
	}
}

void MxDSMultiAction::MergeFrom(MxDSAction& p_dsMultiAction) {
	MxDSAction::MergeFrom(p_dsMultiAction);

	MxDSActionListCursor cursor(this->m_actions);
	MxDSAction* action;
	while (cursor.Next(action)) {
		action->MergeFrom(p_dsMultiAction);
	}
}

MxBool MxDSMultiAction::HasId(MxU32 p_objectId) {
	if (this->GetObjectId() == p_objectId) {
		return TRUE;
	}

	MxDSActionListCursor cursor(this->m_actions);
	MxDSAction* action;
	while (cursor.Next(action)) {
		if (action->HasId(p_objectId)) {
			return TRUE;
		}
	}

	return FALSE;
}

MxDSAction* MxDSMultiAction::Clone() {
	MxDSMultiAction* clone = new MxDSMultiAction();

	if (clone) {
		*clone = *this;
	}

	return clone;
}

undefined4 MxDSMultiAction::VTable0x14() {
	undefined4 result = MxDSAction::VTable0x14();

	MxDSActionListCursor cursor(this->m_actions);
	MxDSAction* action;
	while (cursor.Next(action)) {
		result += action->VTable0x14();
	}

	return result;
}

MxU32 MxDSMultiAction::GetSizeOnDisk() {
	MxU32 totalSizeOnDisk = MxDSAction::GetSizeOnDisk() + 16;

	MxDSActionListCursor cursor(this->m_actions);
	MxDSAction* action;
	while (cursor.Next(action)) {
		totalSizeOnDisk += action->GetSizeOnDisk();
	}

	this->m_sizeOnDisk = totalSizeOnDisk - MxDSAction::GetSizeOnDisk();

	return totalSizeOnDisk;
}

void MxDSMultiAction::Deserialize(MxU8*& p_source, MxS16 p_unk0x24) {
	MxDSAction::Deserialize(p_source, p_unk0x24);

	MxU32 extraFlag = *(MxU32*) (p_source + 4) & 1;
	p_source += 12;

	MxU32 count = *(MxU32*) p_source;
	p_source += sizeof(count);

	if (count) {
		while (count--) {
			MxU32 extraFlag = *(MxU32*) (p_source + 4) & 1;
			p_source += 8;

			MxDSAction* action =
				(MxDSAction*) DeserializeDSObjectDispatch(p_source, p_unk0x24);
			p_source += extraFlag;

			this->m_actions->Append(action);
		}
	}

	p_source += extraFlag;
}

void MxDSMultiAction::SetAtomId(MxAtomId p_atomId) {
	MxDSAction::SetAtomId(p_atomId);

	MxDSActionListCursor cursor(this->m_actions);
	MxDSAction* action;
	while (cursor.Next(action)) {
		action->SetAtomId(p_atomId);
	}
}
