#pragma once

#include "mx_core.h"

#define DS_CHUNK_BIT1 0x01
#define DS_CHUNK_END_OF_STREAM 0x02
#define DS_CHUNK_BIT3 0x04
#define DS_CHUNK_SPLIT 0x10
#define DS_CHUNK_BIT16 0x8000

class MxDSChunk : public MxCore {
public:
	MxDSChunk();
	~MxDSChunk() override;

	static const char* ClassName() { return "MxDSChunk"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSChunk::ClassName()) || MxCore::IsA(p_name);
	}

	static MxU32 GetHeaderSize();

	static MxU32 Size(MxU8* p_buffer) {
		return (*(MxU32*) (p_buffer + 4) & 1) + *(MxU32*) (p_buffer + 4) + 8;
	}

	static MxU8* End(MxU8* p_buffer) { return p_buffer + Size(p_buffer); }

	void SetChunkFlags(MxU16 p_flags) { m_flags = p_flags; }
	void SetObjectId(undefined4 p_objectid) { m_objectId = p_objectid; }

	void SetTime(MxLong p_time) { m_time = p_time; }

	void SetLength(MxU32 p_length) { m_length = p_length; }
	void SetData(MxU8* p_data) { m_data = p_data; }

	MxU16 GetChunkFlags() { return m_flags; }

	undefined4 GetObjectId() { return m_objectId; }

	MxLong GetTime() { return m_time; }

	MxU32 GetLength() { return m_length; }

	MxU8* GetData() { return m_data; }

	void Release() {
		if (m_data) {
			delete[] m_data;
		}
	}

	// MxDSChunk::`scalar deleting destructor'

protected:
	MxU16 m_flags;
	MxU32 m_objectId;
	MxLong m_time;
	MxU32 m_length;
	MxU8* m_data;
};

