#include "mxmediamanager.h"

#include "mxomni.h"
#include "mxpresenter.h"
#include "stdio.h"

MxMediaManager::MxMediaManager() {
	Init();
}

MxMediaManager::~MxMediaManager() {
	Destroy();
}

MxResult MxMediaManager::Init() {
	this->m_presenters = NULL;
	return SUCCESS;
}

MxResult MxMediaManager::Create() {
	this->m_presenters = new MxPresenterList;

	if (!this->m_presenters) {
		log_error("Failed to get presenters for MX media manager\n");
		this->Destroy();
		return FAILURE;
	}

	return SUCCESS;
}

void MxMediaManager::Destroy() {
	if (this->m_presenters) {
		delete this->m_presenters;
	}

	Init();
}

MxResult MxMediaManager::Tickle() {
	MxPresenter* presenter = nullptr;
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
	this->m_presenters->Append(&p_presenter);
}

void MxMediaManager::UnregisterPresenter(MxPresenter& p_presenter) {
	MxPresenterListCursor cursor(this->m_presenters);

	if (cursor.Find(&p_presenter)) {
		cursor.Detach();
	}
}

void MxMediaManager::StopPresenters() {
	MxPresenter* presenter = nullptr;
	MxPresenterListCursor cursor(this->m_presenters);

	while (cursor.Next(presenter)) {
		presenter->EndAction();
	}
}
