#ifndef MXDSSOURCE_H
#define MXDSSOURCE_H

#include "mx_core.h"
#include "mx_ds_buffer.h"

class MxDSSource : public MxCore {
public:
	MxDSSource() : m_lengthInDWords(0), m_pBuffer(NULL), m_position(-1) {}

	~MxDSSource() override { delete[] m_pBuffer; }

	static const char* ClassName() { return "MxDSSource"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSSource::ClassName()) || MxCore::IsA(p_name);
	}

	virtual MxLong Open(MxULong) = 0;
	virtual MxLong Close() = 0;

	virtual MxResult ReadToBuffer(MxDSBuffer* p_buffer) {
		return Read(p_buffer->GetBuffer(), p_buffer->GetWriteOffset());
	}

	virtual MxResult Read(unsigned char*, MxULong) = 0;
	virtual MxLong Seek(MxLong, MxS32) = 0;
	virtual MxULong GetBufferSize() = 0;
	virtual MxULong GetStreamBuffersNum() = 0;

	virtual MxLong GetLengthInDWords() { return m_lengthInDWords; }

	virtual MxU32* GetBuffer() { return m_pBuffer; }

	MxLong GetPosition() const { return m_position; }

protected:
	MxULong m_lengthInDWords;
	MxU32* m_pBuffer;
	MxLong m_position;
};

// MxDSSource::`scalar deleting destructor'

#endif // MXDSSOURCE_H
