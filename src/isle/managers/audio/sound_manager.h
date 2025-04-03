#pragma once

#include "cache_sound_manager.h"
#include "mx_atom.h"

class LegoSoundManager : public Manager {
public:
	LegoSoundManager();
	~LegoSoundManager() override;

	MxResult Tickle() override;
	void Destroy() override;
	MxResult Create(MxU32 p_frequencyMS) override;
	void SetVolume(MxS32 p_volume);
	void Pause();
	void Resume();

	MxS32 GetVolume();

	MxPresenter* FUN_100aebd0(const MxAtomId& p_atomId, MxU32 p_objectId);

private:
	void Init();

	void UpdateListener(
		const float* p_position,
		const float* p_direction,
		const float* p_up,
		const float* p_velocity
	);

	LegoCacheSoundManager* GetCacheSoundManager() {
		return m_cacheSoundManager;
	}

	LegoCacheSoundManager* m_cacheSoundManager;
	MxS32 m_volume;
};

// IID_IDirectSound3DListener

