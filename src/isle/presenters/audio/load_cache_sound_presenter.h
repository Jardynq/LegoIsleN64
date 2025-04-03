#pragma once

#include "mx_wave_presenter.h"

class LegoCacheSound;

class LegoLoadCacheSoundPresenter : public MxWavePresenter {
public:
	LegoLoadCacheSoundPresenter();
	~LegoLoadCacheSoundPresenter() override;

	static const char* HandlerClassName() {
		return "LegoLoadCacheSoundPresenter";
	}

	static const char* ClassName() { return HandlerClassName(); }

	void ReadyTickle() override;
	void StreamingTickle() override;
	void DoneTickle() override;
	MxResult PutData() override;

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);

	LegoCacheSound* m_cacheSound;
	MxU8* m_data;
	MxU8* m_pData;
	MxU32 m_dataSize;
	MxBool m_unk0x7c;
};

// LegoLoadCacheSoundPresenter::`scalar deleting destructor'

