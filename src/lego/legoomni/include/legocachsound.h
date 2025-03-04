#ifndef LEGOCACHSOUND_H
#define LEGOCACHSOUND_H

#include "lego3dsound.h"
#include "mxcore.h"
#include "mxstring.h"

class LegoCacheSound : public MxCore {
public:
	LegoCacheSound();
	~LegoCacheSound() override;

	const char* ClassName() const override {
		// not in BETA10

		return "LegoCacheSound";
	}

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoCacheSound::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	virtual MxResult Create(
		LPPCMWAVEFORMAT p_pwfx,
		MxString p_mediaSrcPath,
		MxS32 p_volume,
		MxU8* p_data,
		MxU32 p_dataSize
	);
	virtual void Destroy();
	virtual void FUN_10006cd0(undefined4, undefined4);

	const MxString& GetUnknown0x48() const { return m_unk0x48; }
	const MxBool GetUnknown0x58() const { return m_unk0x58; }

	LegoCacheSound* Clone();
	MxResult Play(const char* p_name, MxBool p_looping);
	void Stop();
	void FUN_10006be0();
	void SetDistance(MxS32 p_min, MxS32 p_max);
	void MuteSilence(MxBool p_muted);
	void MuteStop(MxBool p_mute);

	// LegoCacheSound::`scalar deleting destructor'

private:
	void Init();
	void CopyData(MxU8* p_data, MxU32 p_dataSize);
	MxString GetBaseFilename(MxString& p_path);

	LPDIRECTSOUNDBUFFER m_dsBuffer;
	undefined m_unk0x0c[4];
	Lego3DSound m_sound;
	MxU8* m_data;
	MxU32 m_dataSize;
	MxString m_unk0x48;
	MxBool m_unk0x58;
	PCMWAVEFORMAT m_wfx;
	MxBool m_looping;
	MxBool m_unk0x6a;
	MxS32 m_volume;
	MxBool m_unk0x70;
	MxString m_unk0x74;
	MxBool m_muted;
};

#endif // LEGOCACHSOUND_H
