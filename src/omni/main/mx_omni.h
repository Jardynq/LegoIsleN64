#pragma once

#include "mx_core.h"
#include "mx_string.h"

class MxAtomSet;
class MxDSAction;
class MxEntity;
class MxEventManager;
class MxMusicManager;
class MxNotificationManager;
class MxNotificationParam;
class MxObjectFactory;
class MxOmniCreateParam;
class MxPresenter;
class MxSoundManager;
class MxStreamer;
class MxStreamController;
class MxTickleManager;
class MxTimer;
class MxVariableTable;
class MxVideoManager;

class MxOmni : public MxCore {
public:
	static void DestroyInstance();
	static const char* GetCD();
	static const char* GetHD();
	static MxOmni* GetInstance();
	static MxBool IsSound3D();
	static void SetCD(const char* p_cd);
	static void SetHD(const char* p_hd);
	static void SetSound3D(MxBool p_use3dSound);

	MxOmni();
	~MxOmni() override;

	MxLong Notify(MxParam& p_param) override;
	virtual void Init();
	virtual MxResult Create(MxOmniCreateParam& p_param);
	virtual void Destroy();
	virtual MxResult Start(MxDSAction* p_dsAction);
	virtual void DeleteObject(MxDSAction& p_dsAction);
	virtual MxBool DoesEntityExist(MxDSAction& p_dsAction);
	virtual MxResult
	CreatePresenter(MxStreamController* p_controller, MxDSAction& p_action);
	virtual MxEntity* AddToWorld(const char*, MxS32, MxPresenter*);
	virtual void NotifyCurrentEntity(const MxNotificationParam& p_param);
	virtual void Pause();
	virtual void Resume();

	virtual MxBool IsPaused() { return m_paused; }

	static void SetInstance(MxOmni* p_instance);
	static MxBool ActionSourceEquals(MxDSAction* p_action, const char* p_name);

	HWND GetWindowHandle() const { return this->m_windowHandle; }

	MxObjectFactory* GetObjectFactory() const { return this->m_objectFactory; }

	MxNotificationManager* GetNotificationManager() const {
		return this->m_notificationManager;
	}

	MxTickleManager* GetTickleManager() const { return this->m_tickleManager; }

	MxTimer* GetTimer() const { return this->m_timer; }

	MxStreamer* GetStreamer() const { return this->m_streamer; }

	MxSoundManager* GetSoundManager() const { return this->m_soundManager; }

	MxVideoManager* GetVideoManager() const { return this->m_videoManager; }

	MxVariableTable* GetVariableTable() const { return this->m_variableTable; }

	MxMusicManager* GetMusicManager() const { return this->m_musicManager; }

	MxEventManager* GetEventManager() const { return this->m_eventManager; }

	MxAtomSet* GetAtomSet() const { return this->m_atomSet; }

	MxLong HandleEndAction(MxParam& p_param);

protected:
	static MxOmni* g_instance;

	MxString m_mediaPath;
	HWND m_windowHandle;
	MxObjectFactory* m_objectFactory;
	MxVariableTable* m_variableTable;
	MxTickleManager* m_tickleManager;
	MxNotificationManager* m_notificationManager;
	MxVideoManager* m_videoManager;
	MxSoundManager* m_soundManager;
	MxMusicManager* m_musicManager;
	MxEventManager* m_eventManager;
	MxTimer* m_timer;
	MxStreamer* m_streamer;
	MxAtomSet* m_atomSet;
	MxBool m_paused;
};
