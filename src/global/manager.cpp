#include "manager.h"

#include "mx_misc.h"
#include "mx_tickle_manager.h"
#include "stdio.h"

Manager::Manager() {
	Init();
}

Manager::~Manager() {
	Destroy();
}

MxResult Manager::Init() {
	this->m_presenters = NULL;
	return SUCCESS;
}

MxResult Manager::Create(MxU32 p_frequencyMS) {
	this->m_presenters = new MxPresenterList();

	if (!this->m_presenters) {
		log_error("Failed to get presenters for manager\n");
		this->Destroy();
		return FAILURE;
	}

	TickleManager()->RegisterClient(this, p_frequencyMS);

	return SUCCESS;
}

void Manager::Destroy() {
	TickleManager()->UnregisterClient(this);
	if (this->m_presenters) {
		delete this->m_presenters;
	}

	Init();
}

MxResult Manager::Tickle() {
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

void Manager::RegisterPresenter(MxPresenter& p_presenter) {
	this->m_presenters->Append(&p_presenter);
}

void Manager::UnregisterPresenter(MxPresenter& p_presenter) {
	MxPresenterListCursor cursor(this->m_presenters);

	if (cursor.Find(&p_presenter)) {
		cursor.Detach();
	}
}

void Manager::StopPresenters() {
	MxPresenter* presenter = nullptr;
	MxPresenterListCursor cursor(this->m_presenters);

	while (cursor.Next(presenter)) {
		presenter->EndAction();
	}
}
