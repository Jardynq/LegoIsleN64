#include "mxdssound.h"

#include "mxutilities.h"

MxDSSound::MxDSSound() {
	this->m_volume = 0x4f;
	this->SetType(e_sound);
}

MxDSSound::~MxDSSound() {
}

void MxDSSound::CopyFrom(MxDSSound& p_dsSound) {
	this->SetType(p_dsSound.GetType());
	this->m_volume = p_dsSound.m_volume;
}

MxDSSound& MxDSSound::operator=(MxDSSound& p_dsSound) {
	if (this == &p_dsSound) {
		return *this;
	}

	MxDSMediaAction::operator=(p_dsSound);
	this->CopyFrom(p_dsSound);
	return *this;
}

MxDSAction* MxDSSound::Clone() {
	MxDSSound* clone = new MxDSSound();

	if (clone) {
		*clone = *this;
	}

	return clone;
}

void MxDSSound::Deserialize(MxU8*& p_source, MxS16 p_unk0x24) {
	MxDSMediaAction::Deserialize(p_source, p_unk0x24);

	GetScalar(p_source, this->m_volume);
}

MxU32 MxDSSound::GetSizeOnDisk() {
	MxU32 totalSizeOnDisk = MxDSMediaAction::GetSizeOnDisk();

	this->m_sizeOnDisk = sizeof(this->m_volume);
	return totalSizeOnDisk + 4;
}
