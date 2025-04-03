#ifndef MXAUDIOMANAGER_H
#define MXAUDIOMANAGER_H

#include "mx_media_manager.h"

class MxAudioManager : public MxMediaManager {
public:
	MxAudioManager();
	~MxAudioManager() override;

	MxResult Create() override;
	void Destroy() override;

	virtual MxS32 GetVolume() { return m_volume; }

	virtual void SetVolume(MxS32 p_volume);

	// MxAudioManager::`scalar deleting destructor'

private:
	void Destroy(MxBool p_fromDestructor);

	static MxS32 g_count;

protected:
	void Init();

	MxS32 m_volume;
};

#endif // MXAUDIOMANAGER_H
