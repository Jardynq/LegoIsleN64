#pragma once

#include "mx_core.h"
#include "mx_presenter_list.h"

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

