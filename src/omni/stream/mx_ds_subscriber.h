#pragma once

#include "mx_core.h"
#include "mx_stream_chunk_list.h"
#include "mx_utility_list.h"

class MxDSObject;
class MxDSSubscriber;
class MxStreamController;

class MxDSSubscriberList : public MxUtilityList<MxDSSubscriber*> {
public:
	MxDSSubscriber* Find(MxDSObject* p_object);
};

class MxDSSubscriber : public MxCore {
public:
	MxDSSubscriber();
	~MxDSSubscriber() override;

	static const char* ClassName() { return "MxDSSubscriber"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSSubscriber::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	MxResult
	Create(MxStreamController* p_controller, MxU32 p_objectId, MxS16 p_unk0x48);
	void DestroyData();
	MxResult AddData(MxStreamChunk* p_chunk, MxBool p_append);
	MxStreamChunk* PopData();
	MxStreamChunk* PeekData();
	void FreeDataChunk(MxStreamChunk* p_chunk);

	MxU32 GetObjectId() { return m_objectId; }

	MxS16 GetUnknown48() { return m_unk0x48; }

private:
	MxStreamChunkList m_pendingChunks;
	MxStreamChunkListCursor* m_pendingChunkCursor;
	MxStreamChunkList m_consumedChunks;
	MxStreamChunkListCursor* m_consumedChunkCursor;
	MxStreamController* m_controller;
	MxU32 m_objectId;
	MxS16 m_unk0x48;
};

// MxDSSubscriber::`scalar deleting destructor'

// MxStreamChunkList::~MxStreamChunkList

// MxUtilityList<MxDSSubscriber *>::PopFront

