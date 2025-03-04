#ifndef MXMEDIAMANGER_H
#define MXMEDIAMANGER_H

#include "mxcore.h"
#include "mxcriticalsection.h"
#include "mxpresenterlist.h"

class MxThread;

class MxMediaManager : public MxCore {
public:
	MxMediaManager();
	~MxMediaManager() override;

	MxResult Tickle() override;
	virtual MxResult Create();
	virtual void Destroy();
	virtual void RegisterPresenter(MxPresenter& p_presenter);
	virtual void UnregisterPresenter(MxPresenter& p_presenter);
	virtual void StopPresenters();

	MxResult Init();

	// MxMediaManager::`scalar deleting destructor'

protected:
	MxPresenterList* m_presenters;
	MxThread* m_thread;
	MxCriticalSection m_criticalSection;
};

#endif // MXMEDIAMANGER_H
