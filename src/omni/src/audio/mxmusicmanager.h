#ifndef MXMUSICMANAGER_H
#define MXMUSICMANAGER_H

#include "mxaudiomanager.h"

class MxMusicManager : public MxAudioManager {
public:
	MxMusicManager();
	~MxMusicManager() override;

	void Destroy() override;
	void SetVolume(MxS32 p_volume) override;
	virtual MxResult Create(MxU32 p_frequencyMS);

	MxBool GetMIDIInitialized() { return m_midiInitialized; }
	void GetMIDIVolume(DWORD& p_volume) {
		p_volume = CalculateVolume(100);
	}

	MxResult ResetStream();
	void ResetBuffer();
	MxResult InitializeMIDI(MxU8* p_data, MxS32 p_loopCount);
	void DeinitializeMIDI();
	void SetMultiplier(MxS32 p_multiplier);

private:
	void Destroy(MxBool p_fromDestructor);

	MxS32 CalculateVolume(MxS32 p_volume);
	void SetMIDIVolume();

	MxBool m_midiInitialized;
	MxU32 m_bufferSize;
	MxU32 m_bufferCurrentSize;
	MxU8* m_bufferOffset;
	MxU8* m_bufferCurrentOffset;
	MxU32 m_loopCount;
	MxS32 m_multiplier;
	DWORD m_midiVolume;

	// MxMusicManager::`scalar deleting destructor'

protected:
	void Init();
	void InitData();
};

#endif // MXMUSICMANAGER_H
