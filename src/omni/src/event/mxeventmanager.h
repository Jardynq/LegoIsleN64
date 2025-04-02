#ifndef MXEVENTMANAGER_H
#define MXEVENTMANAGER_H

#include "mxmediamanager.h"

class MxEventManager : public MxMediaManager {
public:
	MxEventManager();
	~MxEventManager() override;

	void Destroy() override;
	virtual MxResult Create(MxU32 p_frequencyMS, MxBool p_createThread);

	// MxEventManager::`scalar deleting destructor'

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);
};

#endif // MXEVENTMANAGER_H
