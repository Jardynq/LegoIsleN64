#ifndef MXSOUNDMANAGER_H
#define MXSOUNDMANAGER_H

#include "mx_atom.h"
#include "mx_audio_manager.h"

class MxSoundManager : public MxAudioManager {
public:
	MxSoundManager();
	~MxSoundManager() override;

	void Destroy() override;
	void SetVolume(MxS32 p_volume) override;
	virtual MxResult Create(MxU32 p_frequencyMS);
	virtual void Pause();
	virtual void Resume();

	MxS32 GetAttenuation(MxU32 p_volume);

	MxPresenter* FUN_100aebd0(const MxAtomId& p_atomId, MxU32 p_objectId);

protected:
	void Init();
	void Destroy(MxBool p_fromDestructor);

	undefined m_unk0x38[4];
};

// MxSoundManager::`scalar deleting destructor'

#endif // MXSOUNDMANAGER_H
