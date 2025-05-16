#include "mx_ds_streaming_action.h"

#include "mx_ds_buffer.h"

MxDSStreamingAction::MxDSStreamingAction(
	MxDSAction& p_dsAction,
	MxU32 p_offset
) {
	Init();

	MxDSAction::operator=(p_dsAction);
	m_unk0x94 = p_offset;
	m_bufferOffset = p_offset;
}

MxBool MxDSStreamingAction::HasId(MxU32 p_objectId) {
	return m_internalAction ? m_internalAction->HasId(p_objectId) : FALSE;
}

MxDSStreamingAction::MxDSStreamingAction(
	MxDSStreamingAction& p_dsStreamingAction
)
	: MxDSAction(p_dsStreamingAction) {
	Init();
	CopyFrom(p_dsStreamingAction);
}

MxDSStreamingAction::~MxDSStreamingAction() {
	if (m_unk0xa0) {
		delete m_unk0xa0;
	}
	if (m_unk0xa4) {
		delete m_unk0xa4;
	}
	if (m_internalAction) {
		delete m_internalAction;
	}
}

void MxDSStreamingAction::Init() {
	m_unk0x94 = 0;
	m_bufferOffset = 0;
	m_unk0x9c = 0;
	m_unk0xa0 = NULL;
	m_unk0xa4 = NULL;
	m_unk0xa8 = 0;
	m_unk0xac = 2;
	m_internalAction = NULL;
}

MxDSStreamingAction*
MxDSStreamingAction::CopyFrom(MxDSStreamingAction& p_dsStreamingAction) {
	MxDSAction::operator=(p_dsStreamingAction);
	m_unk0x94 = p_dsStreamingAction.m_unk0x94;
	m_bufferOffset = p_dsStreamingAction.m_bufferOffset;
	m_unk0x9c = p_dsStreamingAction.m_unk0x9c;
	m_unk0xa0 = NULL;
	m_unk0xa4 = NULL;
	m_unk0xac = p_dsStreamingAction.m_unk0xac;
	m_unk0xa8 = p_dsStreamingAction.m_unk0xa8;
	SetInternalAction(
		p_dsStreamingAction.m_internalAction
			? p_dsStreamingAction.m_internalAction->Clone()
			: NULL
	);

	return this;
}

void MxDSStreamingAction::SetInternalAction(MxDSAction* p_dsAction) {
	if (m_internalAction) {
		delete m_internalAction;
	}
	m_internalAction = p_dsAction;
}

void MxDSStreamingAction::FUN_100cd2d0() {
	if (m_duration == -1) {
		return;
	}

	MxLong duration = m_duration / m_loopCount;
	m_loopCount--;

	m_duration -= duration;
	m_unk0xa8 += duration;
}
