#include "mxdschunk.h"

MxDSChunk::MxDSChunk() {
	m_data = NULL;
	m_flags = 0;
	m_objectId = -1;
	m_time = 0;
	m_length = 0;
}

MxDSChunk::~MxDSChunk() {
	if (m_flags & DS_CHUNK_BIT1) {
		delete[] m_data;
	}
}

MxU32 MxDSChunk::GetHeaderSize() {
	return 0x0e;
}
