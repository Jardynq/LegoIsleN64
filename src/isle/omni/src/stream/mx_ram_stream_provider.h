#pragma once

#include "mx_stream_provider.h"

class MxRAMStreamProvider : public MxStreamProvider {
public:
	MxRAMStreamProvider();
	~MxRAMStreamProvider() override;

	static const char* ClassName() { return "MxRAMStreamProvider"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxRAMStreamProvider::ClassName()) ||
			   MxStreamProvider::IsA(p_name);
	}

	MxResult SetResourceToGet(MxStreamController* p_resource) override;
	MxU32 GetFileSize() override;
	MxS32 GetStreamBuffersNum() override;
	MxU32 GetLengthInDWords() override;
	MxU32* GetBufferForDWords() override;

	MxU8* GetBufferOfFileSize() { return m_pBufferOfFileSize; }

protected:
	MxU32 m_bufferSize;
	MxU32 m_fileSize;
	MxU8* m_pBufferOfFileSize;
	MxU32 m_lengthInDWords;
	MxU32* m_bufferForDWords;
};

// MxRAMStreamProvider::`scalar deleting destructor'

MxU32 ReadData(MxU8* p_fileSizeBuffer, MxU32 p_fileSize);

