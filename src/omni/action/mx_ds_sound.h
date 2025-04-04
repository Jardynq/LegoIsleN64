#pragma once

#include "mx_ds_media_action.h"

class MxDSSound : public MxDSMediaAction {
public:
	MxDSSound();
	~MxDSSound() override;

	void CopyFrom(MxDSSound& p_dsSound);
	MxDSSound& operator=(MxDSSound& p_dsSound);

	static const char* ClassName() { return "MxDSSound"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSSound::ClassName()) ||
			   MxDSMediaAction::IsA(p_name);
	}

	MxU32 GetSizeOnDisk() override;
	void Deserialize(MxU8*& p_source, MxS16 p_unk0x24) override;
	MxDSAction* Clone() override;

	MxS32 GetVolume() const { return m_volume; }

	// MxDSSound::`scalar deleting destructor'

private:
	MxU32 m_sizeOnDisk;
	MxS32 m_volume;
};

