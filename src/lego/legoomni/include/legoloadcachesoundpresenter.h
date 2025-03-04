#ifndef LEGOLOADCACHESOUNDPRESENTER_H
#define LEGOLOADCACHESOUNDPRESENTER_H

#include "mxwavepresenter.h"

class LegoCacheSound;

class LegoLoadCacheSoundPresenter : public MxWavePresenter {
public:
	LegoLoadCacheSoundPresenter();
	~LegoLoadCacheSoundPresenter() override;

	static const char* HandlerClassName() {

		return "LegoLoadCacheSoundPresenter";
	}

	const char* ClassName() const override { return HandlerClassName(); }

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
	PCMWAVEFORMAT m_pcmWaveFormat;
};

// LegoLoadCacheSoundPresenter::`scalar deleting destructor'

#endif // LEGOLOADCACHESOUNDPRESENTER_H
