#ifndef MXWAVEPRESENTER_H
#define MXWAVEPRESENTER_H

#include "mxsoundpresenter.h"

#include <dsound.h>

class MxWavePresenter : public MxSoundPresenter {
public:
	MxWavePresenter() { Init(); }

	~MxWavePresenter() override { Destroy(TRUE); }

	void Destroy() override { Destroy(FALSE); }

	virtual void Pause();
	virtual void Resume();

	virtual MxBool IsPaused() { return m_paused; }

	static const char* HandlerClassName() { return "MxWavePresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxWavePresenter::ClassName()) ||
			   MxSoundPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	void StreamingTickle() override;
	void DoneTickle() override;
	void ParseExtra() override;
	MxResult AddToManager() override;
	void EndAction() override;
	MxResult PutData() override;
	void Enable(MxBool p_enable) override;
	void LoopChunk(MxStreamChunk* p_chunk) override;
	void SetVolume(MxS32 p_volume) override;

	struct WaveFormat {
		PCMWAVEFORMAT m_pcmWaveFormat;
		MxU32 m_dataSize;
		MxU32 m_flags;
	};

	// MxWavePresenter::`scalar deleting destructor'

protected:
	void Init();
	void Destroy(MxBool p_fromDestructor);

	MxS8 GetPlayedChunks();
	MxBool FUN_100b1ba0();
	void WriteToSoundBuffer(void* p_audioPtr, MxU32 p_length);

	WaveFormat* m_waveFormat;
	LPDIRECTSOUNDBUFFER m_dsBuffer;
	MxU32 m_chunkLength;
	MxU32 m_lockSize;
	MxU8 m_writtenChunks;
	MxBool m_started;
	MxBool m_is3d;
	MxS8 m_silenceData;
	MxBool m_paused;
};

#endif // MXWAVEPRESENTER_H
