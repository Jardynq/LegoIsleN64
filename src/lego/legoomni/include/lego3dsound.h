#ifndef LEGO3DSOUND_H
#define LEGO3DSOUND_H

#include <dsound.h>

class LegoActor;
class LegoROI;

class Lego3DSound {
public:
	Lego3DSound();
	virtual ~Lego3DSound();

	void Init();
	MxResult Create(
		LPDIRECTSOUNDBUFFER p_directSoundBuffer,
		const char* p_name,
		MxS32 p_volume
	);
	void Destroy();
	MxU32 UpdatePosition(LPDIRECTSOUNDBUFFER p_directSoundBuffer);
	void
	FUN_10011a60(LPDIRECTSOUNDBUFFER p_directSoundBuffer, const char* p_name);
	void Reset();
	MxS32 SetDistance(MxS32 p_min, MxS32 p_max);

	// Lego3DSound::`scalar deleting destructor'

private:
	LPDIRECTSOUND3DBUFFER m_ds3dBuffer;
	LegoROI* m_roi;
	LegoROI* m_positionROI;
	MxBool m_enabled;
	MxBool m_isActor;
	LegoActor* m_actor;
	double m_frequencyFactor;
	DWORD m_dwFrequency;
	MxS32 m_volume;
};

// IID_IDirectSound3DBuffer

#endif // LEGO3DSOUND_H
