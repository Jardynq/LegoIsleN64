#include "mxdssubscriber.h"

#include "mxstreamcontroller.h"

MxDSSubscriber::MxDSSubscriber() {
	m_unk0x48 = -1;
	m_objectId = -1;
	m_pendingChunkCursor = NULL;
	m_consumedChunkCursor = NULL;
}

MxDSSubscriber::~MxDSSubscriber() {
	if (m_controller) {
		m_controller->RemoveSubscriber(this);
	}

	DestroyData();

	if (m_pendingChunkCursor) {
		delete m_pendingChunkCursor;
	}
	m_pendingChunkCursor = NULL;

	if (m_consumedChunkCursor) {
		delete m_consumedChunkCursor;
	}
	m_consumedChunkCursor = NULL;
}

MxResult MxDSSubscriber::Create(
	MxStreamController* p_controller,
	MxU32 p_objectId,
	MxS16 p_unk0x48
) {
	m_objectId = p_objectId;
	m_unk0x48 = p_unk0x48;

	if (!p_controller) {
		return FAILURE;
	}
	m_controller = p_controller;

	m_pendingChunkCursor = new MxStreamChunkListCursor(&m_pendingChunks);
	if (!m_pendingChunkCursor) {
		return FAILURE;
	}

	m_consumedChunkCursor = new MxStreamChunkListCursor(&m_consumedChunks);
	if (!m_consumedChunkCursor) {
		return FAILURE;
	}

	m_controller->AddSubscriber(this);
	return SUCCESS;
}

void MxDSSubscriber::DestroyData() {
	if (m_controller) {
		MxStreamChunk* chunk = NULL;

		while (m_pendingChunkCursor->First(chunk)) {
			m_pendingChunkCursor->Detach();
			delete chunk;
		}

		while (m_consumedChunkCursor->First(chunk)) {
			m_consumedChunkCursor->Detach();
			delete chunk;
		}
	}
}

MxResult MxDSSubscriber::AddData(MxStreamChunk* p_chunk, MxBool p_append) {
	if (m_pendingChunkCursor) {
		if (p_append) {
			m_pendingChunks.Append(p_chunk);
		} else {
			m_pendingChunks.Prepend(p_chunk);
		}
	}

	return SUCCESS;
}

MxStreamChunk* MxDSSubscriber::PopData() {
	MxStreamChunk* chunk = NULL;

	if (m_pendingChunkCursor) {
		m_pendingChunkCursor->First(chunk);
	}

	if (chunk) {
		m_pendingChunkCursor->Detach();
		m_consumedChunks.Append(chunk);
	}

	return chunk;
}

MxStreamChunk* MxDSSubscriber::PeekData() {
	MxStreamChunk* chunk = NULL;

	if (m_pendingChunkCursor) {
		m_pendingChunkCursor->First(chunk);
	}

	return chunk;
}

void MxDSSubscriber::FreeDataChunk(MxStreamChunk* p_chunk) {
	if (p_chunk) {
		if (m_consumedChunkCursor->Find(p_chunk)) {
			m_consumedChunkCursor->Detach();
			if (p_chunk) {
				delete p_chunk;
			}
		} else if (p_chunk->GetChunkFlags() & DS_CHUNK_BIT1 && p_chunk) {
			delete p_chunk;
		}
	}
}

MxDSSubscriber* MxDSSubscriberList::Find(MxDSObject* p_object) {
	for (iterator it = begin(); it != end(); it++) {
		if (p_object->GetObjectId() == -1 ||
			p_object->GetObjectId() == (*it)->GetObjectId()) {
			if (p_object->GetUnknown24() == -2 ||
				p_object->GetUnknown24() == (*it)->GetUnknown48()) {
				return *it;
			}
		}
	}

	return NULL;
}
