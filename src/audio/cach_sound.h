#ifndef LEGOCACHSOUND_H
#define LEGOCACHSOUND_H

#include "mx_core.h"
#include "mx_string.h"
#include "wav64.h"

class LegoCacheSound : public MxCore {
public:
	LegoCacheSound();
	~LegoCacheSound() override;

	static const char* ClassName() {
		return "LegoCacheSound";
	}

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoCacheSound::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	virtual MxResult Create(
		MxString p_mediaSrcPath,
		MxS32 p_volume,
		wav64_t *p_wav
	);
	virtual void Destroy();
	MxResult Tickle() override;

	const MxString& GetFileName() const { return m_filename; }
	const MxBool GetIsPlaying() const { return m_is_playing; }

	LegoCacheSound* Clone();
	MxResult Play(const char* p_name, MxBool p_looping);
	void Stop();
	void SetDistance(MxS32 p_min, MxS32 p_max);
	void MuteSilence(MxBool p_muted);
	void MuteStop(MxBool p_mute);

private:
	void Init();
	void CopyData(MxU8* p_data, MxU32 p_dataSize);
	MxString GetBaseFilename(MxString& p_path);

	wav64_t m_wav;
	undefined m_unk0x0c[4];
	MxU8* m_data;
	MxU32 m_dataSize;
	MxString m_filename;
	MxBool m_is_playing;
	MxBool m_looping;
	MxS32 m_volume;
	MxBool m_unk0x70;
	MxBool m_muted;
};

#endif // LEGOCACHSOUND_H
