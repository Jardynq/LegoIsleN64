#pragma once

#include "mx_ds_source.h"
#include "mx_string.h"

class MxDSFile : public MxDSSource {
public:
	MxDSFile(const char* p_filename, MxULong p_skipReadingChunks);

	~MxDSFile() override { Close(); }

	static const char* ClassName() { return "MxDSFile"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSFile::ClassName()) ||
			   MxDSSource::IsA(p_name);
	}

	MxResult Open(MxULong) override;
	MxResult Close() override;
	MxResult Read(unsigned char*, MxULong) override;
	MxResult Seek(MxLong, MxS32) override;
	MxULong GetBufferSize() override;
	MxULong GetStreamBuffersNum() override;

	void SetFileName(const char* p_filename) { m_filename = p_filename; }

	MxS32 CalcFileSize();

	struct ChunkHeader {

		ChunkHeader()
			: m_majorVersion(0), m_minorVersion(0), m_bufferSize(0),
			  m_streamBuffersNum(0) {}

		MxS16 m_majorVersion;
		MxS16 m_minorVersion;
		MxULong m_bufferSize;
		MxS16 m_streamBuffersNum;
		MxS16 m_reserved;
	};

private:
	MxResult ReadChunks();

	MxString m_filename;
	ChunkHeader m_header;
	// If false, read chunks immediately on open, otherwise
	// skip reading chunks until ReadChunks is explicitly called.
	MxULong m_skipReadingChunks;
};
