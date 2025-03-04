#ifndef LEGOSOUNDMANAGER_H
#define LEGOSOUNDMANAGER_H

#include "mxsoundmanager.h"

class LegoCacheSoundManager;

class LegoSoundManager : public MxSoundManager {
public:
	LegoSoundManager();
	~LegoSoundManager() override;

	MxResult Tickle() override;
	void Destroy() override;
	MxResult Create(MxU32 p_frequencyMS, MxBool p_createThread) override;

	// LegoSoundManager::`scalar deleting destructor'

	void UpdateListener(
		const float* p_position,
		const float* p_direction,
		const float* p_up,
		const float* p_velocity
	);

	LegoCacheSoundManager* GetCacheSoundManager() {
		return m_cacheSoundManager;
	}

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);

	LPDIRECTSOUND3DLISTENER m_listener;
	LegoCacheSoundManager* m_cacheSoundManager;
};

// IID_IDirectSound3DListener

#endif // LEGOSOUNDMANAGER_H
