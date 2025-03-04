#include "mxdsmediaaction.h"

#include "mxdebug.h"
#include "mxutilities.h"

MxDSMediaAction::MxDSMediaAction() {
	m_type = e_mediaAction;
	m_mediaSrcPath = NULL;
	m_unk0x9c.SetUnk0x00(0);
	m_unk0x9c.SetUnk0x04(0);
	m_framesPerSecond = 0;
	m_mediaFormat = 0;
	m_unk0xb4 = -1;
	m_paletteManagement = 1;
	m_sustainTime = 0;
}

MxDSMediaAction::~MxDSMediaAction() {
	delete[] m_mediaSrcPath;
}

void MxDSMediaAction::CopyFrom(MxDSMediaAction& p_dsMediaAction) {
	CopyMediaSrcPath(p_dsMediaAction.m_mediaSrcPath);

	m_unk0x9c = p_dsMediaAction.m_unk0x9c;
	m_framesPerSecond = p_dsMediaAction.m_framesPerSecond;
	m_mediaFormat = p_dsMediaAction.m_mediaFormat;
	m_paletteManagement = p_dsMediaAction.m_paletteManagement;
	m_sustainTime = p_dsMediaAction.m_sustainTime;
}

MxDSMediaAction::MxDSMediaAction(MxDSMediaAction& p_dsMediaAction)
	: MxDSAction(p_dsMediaAction) {
	CopyFrom(p_dsMediaAction);
}

MxDSMediaAction& MxDSMediaAction::operator=(MxDSMediaAction& p_dsMediaAction) {
	if (this == &p_dsMediaAction) {
		return *this;
	}

	MxDSAction::operator=(p_dsMediaAction);
	CopyFrom(p_dsMediaAction);
	return *this;
}

MxDSAction* MxDSMediaAction::Clone() {
	MxDSMediaAction* clone = new MxDSMediaAction();

	if (clone) {
		*clone = *this;
	}

	return clone;
}

void MxDSMediaAction::CopyMediaSrcPath(const char* p_mediaSrcPath) {
	if (m_mediaSrcPath == p_mediaSrcPath) {
		MxTrace(
			"MxDSMediaAction: name allocation SUCCESS: %s.\n",
			p_mediaSrcPath
		);
		return;
	}

	delete[] m_mediaSrcPath;

	if (p_mediaSrcPath) {
		m_mediaSrcPath = new char[strlen(p_mediaSrcPath) + 1];
		if (m_mediaSrcPath) {
			strcpy(m_mediaSrcPath, p_mediaSrcPath);
		}

		MxTrace(
			"MxDSMediaAction: name allocation failed: %s.\n",
			p_mediaSrcPath
		);
	} else {
		m_mediaSrcPath = NULL;
	}
}

undefined4 MxDSMediaAction::VTable0x14() {
	return MxDSAction::VTable0x14();
}

MxU32 MxDSMediaAction::GetSizeOnDisk() {
	MxU32 totalSizeOnDisk = MxDSAction::GetSizeOnDisk();

	if (m_mediaSrcPath) {
		totalSizeOnDisk += strlen(m_mediaSrcPath) + 1;
	} else {
		totalSizeOnDisk++;
	}

	totalSizeOnDisk += sizeof(m_unk0x9c.m_unk0x00);
	totalSizeOnDisk += sizeof(m_unk0x9c.m_unk0x04);
	totalSizeOnDisk += sizeof(m_framesPerSecond);
	totalSizeOnDisk += sizeof(m_mediaFormat);
	totalSizeOnDisk += sizeof(m_paletteManagement);
	totalSizeOnDisk += sizeof(m_sustainTime);

	m_sizeOnDisk = totalSizeOnDisk - MxDSAction::GetSizeOnDisk();
	return totalSizeOnDisk;
}

void MxDSMediaAction::Deserialize(MxU8*& p_source, MxS16 p_unk0x24) {
	MxDSAction::Deserialize(p_source, p_unk0x24);

	CopyMediaSrcPath((char*) p_source);
	p_source += strlen(m_mediaSrcPath) + 1;

	// clang-format off
	m_unk0x9c.SetUnk0x00(*(MxU32*)p_source);  p_source += sizeof(m_unk0x9c.m_unk0x00);
	m_unk0x9c.SetUnk0x04(*(MxU32*)p_source);  p_source += sizeof(m_unk0x9c.m_unk0x04);

	m_framesPerSecond = *(MxS32*)p_source;  p_source += sizeof(m_framesPerSecond);
	m_mediaFormat = *(MxS32*)p_source;  p_source += sizeof(m_mediaFormat);
	m_paletteManagement = *(MxS32*)p_source;  p_source += sizeof(m_paletteManagement);
	m_sustainTime = *(MxS32*)p_source;  p_source += sizeof(m_sustainTime);
	// clang-format on
}
