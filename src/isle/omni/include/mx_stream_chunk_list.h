#pragma once

#include "mx_list.h"
#include "mx_stream_chunk.h"

// class MxCollection<MxStreamChunk *>

// class MxList<MxStreamChunk *>

class MxStreamChunkList : public MxList<MxStreamChunk*> {
public:
	MxStreamChunkList() { m_customDestructor = Destroy; }

	MxS8 Compare(MxStreamChunk* p_a, MxStreamChunk* p_b) override {
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	}

	static void Destroy(MxStreamChunk* p_chunk) { delete p_chunk; }

	// MxStreamChunkList::`scalar deleting destructor'
};

class MxStreamChunkListCursor : public MxListCursor<MxStreamChunk*> {
public:
	MxStreamChunkListCursor(MxStreamChunkList* p_list)
		: MxListCursor<MxStreamChunk*>(p_list) {}
};

// class MxListCursor<MxStreamChunk *>

// MxCollection<MxStreamChunk *>::Compare

// MxCollection<MxStreamChunk *>::~MxCollection<MxStreamChunk *>

// MxCollection<MxStreamChunk *>::Destroy

// MxList<MxStreamChunk *>::~MxList<MxStreamChunk *>

// MxCollection<MxStreamChunk *>::`scalar deleting destructor'

// MxList<MxStreamChunk *>::`scalar deleting destructor'

