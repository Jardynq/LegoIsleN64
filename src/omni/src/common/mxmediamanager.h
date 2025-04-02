#ifndef MXMEDIAMANGER_H
#define MXMEDIAMANGER_H

#include "mxcore.h"
#include "mxpresenterlist.h"

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
};

#endif // MXMEDIAMANGER_H
