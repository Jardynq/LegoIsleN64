#include "mxmisc.h"

#include "mxomni.h"

#include <assert.h>

MxObjectFactory* ObjectFactory() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetObjectFactory();
}

MxNotificationManager* NotificationManager() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetNotificationManager();
}

MxTickleManager* TickleManager() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetTickleManager();
}

MxTimer* Timer() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetTimer();
}

MxAtomSet* AtomSet() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetAtomSet();
}

MxStreamer* Streamer() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetStreamer();
}

MxSoundManager* MSoundManager() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetSoundManager();
}

MxVideoManager* MVideoManager() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetVideoManager();
}

MxVariableTable* VariableTable() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetVariableTable();
}

MxMusicManager* MusicManager() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetMusicManager();
}

MxEventManager* EventManager() {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->GetEventManager();
}

MxResult Start(MxDSAction* p_dsAction) {
	assert(MxOmni::GetInstance());
	return MxOmni::GetInstance()->Start(p_dsAction);
}

void DeleteObject(MxDSAction& p_dsAction) {
	assert(MxOmni::GetInstance());
	MxOmni::GetInstance()->DeleteObject(p_dsAction);
}
