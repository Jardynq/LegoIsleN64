#ifndef MXDSMEDIAACTION_H
#define MXDSMEDIAACTION_H

#include "mxdsaction.h"

class MxDSMediaAction : public MxDSAction {
public:
	MxDSMediaAction();
	~MxDSMediaAction() override;

	void CopyFrom(MxDSMediaAction& p_dsMediaAction);
	MxDSMediaAction(MxDSMediaAction& p_dsMediaAction);
	MxDSMediaAction& operator=(MxDSMediaAction& p_dsMediaAction);

	const char* ClassName() const override { return "MxDSMediaAction"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxDSMediaAction::ClassName()) ||
			   MxDSAction::IsA(p_name);
	}

	// MxDSMediaAction::`scalar deleting destructor'

	undefined4 VTable0x14() override;
	MxU32 GetSizeOnDisk() override;
	void Deserialize(MxU8*& p_source, MxS16 p_unk0x24) override;
	MxDSAction* Clone() override;

	void CopyMediaSrcPath(const char* p_mediaSrcPath);

	const char* GetMediaSrcPath() { return m_mediaSrcPath; }

	MxS32 GetFramesPerSecond() const { return m_framesPerSecond; }

	MxS32 GetMediaFormat() const { return m_mediaFormat; }

	MxS32 GetPaletteManagement() const { return m_paletteManagement; }

	MxLong GetSustainTime() const { return m_sustainTime; }

private:
	struct Unk0x9cStruct {

		void SetUnk0x00(undefined4 p_value) { m_unk0x00 = p_value; }

		void SetUnk0x04(undefined4 p_value) { m_unk0x04 = p_value; }

		// intentionally public
		undefined4 m_unk0x00;
		undefined4 m_unk0x04;
	};

	MxU32 m_sizeOnDisk;
	char* m_mediaSrcPath;
	Unk0x9cStruct m_unk0x9c;
	MxS32 m_framesPerSecond;
	MxS32 m_mediaFormat;
	MxS32 m_paletteManagement;
	MxLong m_sustainTime;
	undefined4 m_unk0xb4;
};

#endif // MXDSMEDIAACTION_H
