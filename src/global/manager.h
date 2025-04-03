#ifndef MANAGER_H
#define MANAGER_H

#include "mx_core.h"
#include "mx_presenter_list.h"

class Manager : public MxCore {
public:
	Manager();
	~Manager() override;

	MxResult Tickle() override;
	virtual MxResult Create(MxU32 p_frequencyMS);
	virtual void Destroy();
	virtual void RegisterPresenter(MxPresenter& p_presenter);
	virtual void UnregisterPresenter(MxPresenter& p_presenter);
	virtual void StopPresenters();

	MxResult Init();

protected:
	MxPresenterList* m_presenters;
};

#endif // MANAGER_H
