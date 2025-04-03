#include "mx_stream_chunk.h"

#include "mx_ds_buffer.h"
#include "mx_ds_subscriber.h"
#include "mx_utilities.h"

MxStreamChunk::~MxStreamChunk() {
	if (m_buffer) {
		m_buffer->ReleaseRef(this);
	}
}

MxResult MxStreamChunk::ReadChunk(MxDSBuffer* p_buffer, MxU8* p_chunkData) {
	MxResult result = FAILURE;

	if (p_chunkData != NULL &&
		*(MxU32*) p_chunkData == FOURCC('M', 'x', 'C', 'h')) {
		if (ReadChunkHeader(p_chunkData + 8)) {
			if (p_buffer) {
				SetBuffer(p_buffer);
				p_buffer->AddRef(this);
			}
			result = SUCCESS;
		}
	}

	return result;
}

MxU32 MxStreamChunk::ReadChunkHeader(MxU8* p_chunkData) {
	MxU32 headersize = 0;
	if (p_chunkData) {
		MxU8* chunkData = p_chunkData;

		memcpy(&m_flags, p_chunkData, sizeof(m_flags));
		p_chunkData += sizeof(m_flags);

		memcpy(&m_objectId, p_chunkData, sizeof(m_objectId));
		p_chunkData += sizeof(m_objectId);

		memcpy(&m_time, p_chunkData, sizeof(m_time));
		p_chunkData += sizeof(m_time);

		memcpy(&m_length, p_chunkData, sizeof(m_length));
		p_chunkData += sizeof(m_length);

		m_data = p_chunkData;
		headersize = p_chunkData - chunkData;
	}

	return headersize;
}

MxResult MxStreamChunk::SendChunk(
	MxDSSubscriberList& p_subscriberList,
	MxBool p_append,
	MxS16 p_obj24val
) {
	for (MxDSSubscriberList::iterator it = p_subscriberList.begin();
		 it != p_subscriberList.end();
		 it++) {
		if ((*it)->GetObjectId() == m_objectId &&
			(*it)->GetUnknown48() == p_obj24val) {
			if (m_flags & DS_CHUNK_END_OF_STREAM && m_buffer) {
				m_buffer->ReleaseRef(this);
				m_buffer = NULL;
			}

			(*it)->AddData(this, p_append);

			return SUCCESS;
		}
	}

	return FAILURE;
}

void MxStreamChunk::SetBuffer(MxDSBuffer* p_buffer) {
	m_buffer = p_buffer;
}

MxU16* MxStreamChunk::IntoFlags(MxU8* p_buffer) {
	return (MxU16*) (p_buffer + 0x08);
}

MxU32* MxStreamChunk::IntoObjectId(MxU8* p_buffer) {
	return (MxU32*) (p_buffer + 0x0a);
}

MxLong* MxStreamChunk::IntoTime(MxU8* p_buffer) {
	return (MxLong*) (p_buffer + 0x0e);
}

MxU32* MxStreamChunk::IntoLength(MxU8* p_buffer) {
	return (MxU32*) (p_buffer + 0x12);
}
