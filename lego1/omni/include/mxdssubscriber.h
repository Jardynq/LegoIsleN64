#ifndef MXDSSUBSCRIBER_H
#define MXDSSUBSCRIBER_H

#include "utils.h"
#include "mxcore.h"
#include "mxstreamchunklist.h"
#include "mxutilitylist.h"

class MxDSObject;
class MxDSSubscriber;
class MxStreamController;

// SIZE 0x0c
class MxDSSubscriberList : public MxUtilityList<MxDSSubscriber*> {
public:
	MxDSSubscriber* Find(MxDSObject* p_object);
};

// VTABLE: LEGO1 0x100dc698
// VTABLE: BETA10 0x101c1d38
// SIZE 0x4c
class MxDSSubscriber : public MxCore {
public:
	MxDSSubscriber();
	~MxDSSubscriber() override;

	// FUNCTION: LEGO1 0x100b7d50
	// FUNCTION: BETA10 0x10135180
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x101020f8
		return "MxDSSubscriber";
	}

	// FUNCTION: LEGO1 0x100b7d60
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSSubscriber::ClassName()) || MxCore::IsA(p_name);
	}

	MxResult Create(MxStreamController* p_controller, MxU32 p_objectId, MxS16 p_unk0x48);
	void DestroyData();
	MxResult AddData(MxStreamChunk* p_chunk, MxBool p_append);
	MxStreamChunk* PopData();
	MxStreamChunk* PeekData();
	void FreeDataChunk(MxStreamChunk* p_chunk);

	// FUNCTION: BETA10 0x101354f0
	MxU32 GetObjectId() { return m_objectId; }

	// FUNCTION: BETA10 0x10135510
	MxS16 GetUnknown48() { return m_unk0x48; }

private:
	MxStreamChunkList m_pendingChunks;              // 0x08
	MxStreamChunkListCursor* m_pendingChunkCursor;  // 0x20
	MxStreamChunkList m_consumedChunks;             // 0x24
	MxStreamChunkListCursor* m_consumedChunkCursor; // 0x3c
	MxStreamController* m_controller;               // 0x40
	MxU32 m_objectId;                               // 0x44
	MxS16 m_unk0x48;                                // 0x48
};

// SYNTHETIC: LEGO1 0x100b7de0
// MxDSSubscriber::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x100b7d00
// MxStreamChunkList::~MxStreamChunkList

// TEMPLATE: BETA10 0x10150a70
// MxUtilityList<MxDSSubscriber *>::PopFront

#endif // MXDSSUBSCRIBER_H
