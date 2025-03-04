#ifndef MXDSSOUND_H
#define MXDSSOUND_H

#include "mxdsmediaaction.h"

class MxDSSound : public MxDSMediaAction {
public:
	MxDSSound();
	~MxDSSound() override;

	void CopyFrom(MxDSSound& p_dsSound);
	MxDSSound& operator=(MxDSSound& p_dsSound);

	const char* ClassName() const override { return "MxDSSound"; }

	MxBool IsA(const char* p_name) const override {
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

#endif // MXDSSOUND_H
