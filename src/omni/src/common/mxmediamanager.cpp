#include "mxmediamanager.h"

#include "mxautolock.h"
#include "mxomni.h"
#include "mxpresenter.h"
#include "mxticklemanager.h"
#include "stdio.h"

MxMediaManager::MxMediaManager() {
	Init();
}

MxMediaManager::~MxMediaManager() {
	Destroy();
}

MxResult MxMediaManager::Init() {
	this->m_presenters = NULL;
	this->m_thread = NULL;
	return SUCCESS;
}

MxResult MxMediaManager::Create() {
	AUTOLOCK(m_criticalSection);

	this->m_presenters = new MxPresenterList;

	if (!this->m_presenters) {
		printf("Failed to get presenters for MX media manager\n");
		this->Destroy();
		return FAILURE;
	}

	return SUCCESS;
}

void MxMediaManager::Destroy() {
	AUTOLOCK(m_criticalSection);

	if (this->m_presenters) {
		delete this->m_presenters;
	}

	Init();
}

MxResult MxMediaManager::Tickle() {
	AUTOLOCK(m_criticalSection);
	MxPresenter* presenter;
	MxPresenterListCursor cursor(this->m_presenters);

	while (cursor.Next(presenter)) {
		presenter->Tickle();
	}

	cursor.Reset();

	while (cursor.Next(presenter)) {
		presenter->PutData();
	}

	return SUCCESS;
}

void MxMediaManager::RegisterPresenter(MxPresenter& p_presenter) {
	AUTOLOCK(m_criticalSection);

	this->m_presenters->Append(&p_presenter);
}

void MxMediaManager::UnregisterPresenter(MxPresenter& p_presenter) {
	AUTOLOCK(m_criticalSection);
	MxPresenterListCursor cursor(this->m_presenters);

	if (cursor.Find(&p_presenter)) {
		cursor.Detach();
	}
}

void MxMediaManager::StopPresenters() {
	AUTOLOCK(m_criticalSection);
	MxPresenter* presenter;
	MxPresenterListCursor cursor(this->m_presenters);

	while (cursor.Next(presenter)) {
		presenter->EndAction();
	}
}
