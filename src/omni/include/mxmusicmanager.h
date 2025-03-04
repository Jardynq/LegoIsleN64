#ifndef MXMUSICMANAGER_H
#define MXMUSICMANAGER_H

#include "mxaudiomanager.h"

#include <windows.h>

class MxMusicManager : public MxAudioManager {
public:
	MxMusicManager();
	~MxMusicManager() override;

	void Destroy() override;
	void SetVolume(MxS32 p_volume) override;
	virtual MxResult Create(MxU32 p_frequencyMS, MxBool p_createThread);

	MxBool GetMIDIInitialized() { return m_midiInitialized; }
	void GetMIDIVolume(DWORD& p_volume) {
		if (midiOutGetVolume((HMIDIOUT) m_midiStreamH, &p_volume)) {
			p_volume = CalculateVolume(100);
		}
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

	static void CALLBACK MidiCallbackProc(
		HDRVR p_hdrvr,
		UINT p_uMsg,
		DWORD p_dwUser,
		DWORD p_dw1,
		DWORD p_dw2
	);

	HMIDISTRM m_midiStreamH;
	MxBool m_midiInitialized;
	MxU32 m_bufferSize;
	MxU32 m_bufferCurrentSize;
	MxU8* m_bufferOffset;
	MxU8* m_bufferCurrentOffset;
	MxU32 m_loopCount;
	MIDIHDR* m_midiHdrP;
	MxS32 m_multiplier;
	DWORD m_midiVolume;

	// MxMusicManager::`scalar deleting destructor'

protected:
	void Init();
	void InitData();
};

#endif // MXMUSICMANAGER_H
