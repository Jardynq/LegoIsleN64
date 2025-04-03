#include "mx_event_presenter.h"

#include "mxautolock.h"
#include "mx_ds_action.h"
#include "mx_ds_subscriber.h"
#include "mx_event_manager.h"
#include "mx_misc.h"
#include "mx_variable_table.h"

MxEventPresenter::MxEventPresenter() {
	Init();
}

MxEventPresenter::~MxEventPresenter() {
	Destroy();
}

void MxEventPresenter::Init() {
	m_data = NULL;
}

MxResult MxEventPresenter::AddToManager() {
	MxResult ret = FAILURE;

	if (EventManager()) {
		ret = SUCCESS;
		EventManager()->RegisterPresenter(*this);
	}

	return ret;
}

void MxEventPresenter::Destroy() {
	if (EventManager()) {
		EventManager()->UnregisterPresenter(*this);
	}

	m_criticalSection.Enter();

	if (m_data) {
		delete[] m_data;
	}

	Init();

	m_criticalSection.Leave();
}

void MxEventPresenter::CopyData(MxStreamChunk* p_chunk) {
	m_data = new MxU8[p_chunk->GetLength()];
	memcpy(m_data, p_chunk->GetData(), p_chunk->GetLength());
}

void MxEventPresenter::ReadyTickle() {
	MxStreamChunk* chunk = NextChunk();

	if (chunk) {
		CopyData(chunk);
		m_subscriber->FreeDataChunk(chunk);
		ParseExtra();
		ProgressTickleState(e_starting);
	}
}

void MxEventPresenter::StartingTickle() {
	MxStreamChunk* chunk = CurrentChunk();

	if (chunk && m_action->GetElapsedTime() >= chunk->GetTime()) {
		ProgressTickleState(e_streaming);
	}
}

MxResult MxEventPresenter::PutData() {
	AUTOLOCK(m_criticalSection);

	if (IsEnabled()) {
		if (m_currentTickleState >= e_streaming &&
			(m_currentTickleState <= e_repeating ||
			 m_currentTickleState == e_done)) {
			if (m_currentChunk && m_currentChunk->GetLength()) {
				if (m_data[12] == 2) {
					const char* data = (const char*) m_currentChunk->GetData();
					MxVariableTable* variableTable = VariableTable();

					const char* key = data;
					const char* value = &data[strlen(data) + 1];
					strlen(value);
					variableTable->SetVariable(key, value);
				}

				if (m_currentTickleState == e_streaming) {
					m_subscriber->FreeDataChunk(m_currentChunk);
				}
				m_currentChunk = NULL;
			}
		}
	}

	return SUCCESS;
}
