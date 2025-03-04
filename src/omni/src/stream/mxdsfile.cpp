#include "mxdsfile.h"

#include "mxdebug.h"

#include <stdio.h>

#define SI_MAJOR_VERSION 2
#define SI_MINOR_VERSION 2

MxDSFile::MxDSFile(const char* p_filename, MxULong p_skipReadingChunks) {
	SetFileName(p_filename);
	m_skipReadingChunks = p_skipReadingChunks;
}

MxResult MxDSFile::Open(MxULong p_uStyle) {
	MxResult result = -FAILURE; // Non-standard value of 1 here
	memset(&m_io, 0, sizeof(MXIOINFO));

	if (m_io.Open(m_filename.GetData(), p_uStyle) != 0) {
		return -1;
	}

	m_io.SetBuffer(NULL, 0, 0);
	m_position = 0;

	if (m_skipReadingChunks == 0) {
		result = ReadChunks();
	}

	if (result != SUCCESS) {
		Close();
	} else {
		Seek(0, SEEK_SET);
	}

	return result;
}

MxResult MxDSFile::ReadChunks() {
	_MMCKINFO topChunk;
	_MMCKINFO childChunk;
	char tempBuffer[80];

	topChunk.fccType = FOURCC('O', 'M', 'N', 'I');
	if (m_io.Descend(&topChunk, NULL, MMIO_FINDRIFF) != 0) {
		MxTrace("Unable to find Streamer RIFF chunk in file: %s\n", m_filename);
		return FAILURE;
	}

	childChunk.ckid = FOURCC('M', 'x', 'H', 'd');
	if (m_io.Descend(&childChunk, &topChunk, 0) != 0) {
		MxTrace("Unable to find Header chunk in file: %s\n", m_filename);
		return FAILURE;
	}

	m_io.Read(&m_header, 0x0c);
	if ((m_header.m_majorVersion != SI_MAJOR_VERSION) ||
		(m_header.m_minorVersion != SI_MINOR_VERSION)) {
		sprintf(
			tempBuffer,
			"Wrong SI file version. %d.%d expected.",
			SI_MAJOR_VERSION,
			SI_MINOR_VERSION
		);
		MessageBoxA(NULL, tempBuffer, NULL, MB_ICONERROR);
		return FAILURE;
	}

	childChunk.ckid = FOURCC('M', 'x', 'O', 'f');
	if (m_io.Descend(&childChunk, &topChunk, 0) != 0) {
		MxTrace("Unable to find Header chunk in file: %s\n", m_filename);
		return FAILURE;
	}

	m_io.Read(&m_lengthInDWords, 4);
	m_pBuffer = new MxU32[m_lengthInDWords];
	m_io.Read(m_pBuffer, m_lengthInDWords * 4);
	return SUCCESS;
}

MxLong MxDSFile::Close() {
	m_io.Close(0);
	m_position = -1;
	memset(&m_header, 0, sizeof(m_header));
	if (m_lengthInDWords != 0) {
		m_lengthInDWords = 0;
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}

	return SUCCESS;
}

MxResult MxDSFile::Read(unsigned char* p_buf, MxULong p_nbytes) {
	if (m_io.Read(p_buf, p_nbytes) != p_nbytes) {
		return FAILURE;
	}

	m_position += p_nbytes;
	return SUCCESS;
}

MxResult MxDSFile::Seek(MxLong p_lOffset, MxS32 p_iOrigin) {
	m_position = m_io.Seek(p_lOffset, p_iOrigin);
	if (m_position == -1) {
		return FAILURE;
	}

	return SUCCESS;
}

MxULong MxDSFile::GetBufferSize() {
	return m_header.m_bufferSize;
}

MxULong MxDSFile::GetStreamBuffersNum() {
	return m_header.m_streamBuffersNum;
}
