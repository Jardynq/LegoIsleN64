#ifndef MXSTREAMCHUNK_H
#define MXSTREAMCHUNK_H

#include "mxdschunk.h"

class MxDSBuffer;
class MxDSSubscriberList;

class MxStreamChunk : public MxDSChunk {
public:
	MxStreamChunk() : m_buffer(NULL) {}

	~MxStreamChunk() override;

	const char* ClassName() const override { return "MxStreamChunk"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxStreamChunk::ClassName()) ||
			   MxDSChunk::IsA(p_name);
	}

	MxDSBuffer* GetBuffer() { return m_buffer; }

	MxResult ReadChunk(MxDSBuffer* p_buffer, MxU8* p_chunkData);
	MxU32 ReadChunkHeader(MxU8* p_chunkData);
	MxResult SendChunk(
		MxDSSubscriberList& p_subscriberList,
		MxBool p_append,
		MxS16 p_obj24val
	);
	void SetBuffer(MxDSBuffer* p_buffer);

	static MxU16* IntoFlags(MxU8* p_buffer);
	static MxU32* IntoObjectId(MxU8* p_buffer);
	static MxLong* IntoTime(MxU8* p_buffer);
	static MxU32* IntoLength(MxU8* p_buffer);

private:
	MxDSBuffer* m_buffer;
};

// MxStreamChunk::`scalar deleting destructor'

#endif // MXSTREAMCHUNK_H
