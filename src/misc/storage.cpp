#include "storage.h"

#include <memory.h>
#include <string.h>

LegoMemory::LegoMemory(void* p_buffer) : LegoStorage() {
	m_buffer = (LegoU8*) p_buffer;
	m_position = 0;
}

LegoResult LegoMemory::Read(void* p_buffer, LegoU32 p_size) {
	memcpy(p_buffer, m_buffer + m_position, p_size);
	m_position += p_size;
	return SUCCESS;
}

LegoResult LegoMemory::Write(const void* p_buffer, LegoU32 p_size) {
	memcpy(m_buffer + m_position, p_buffer, p_size);
	m_position += p_size;
	return SUCCESS;
}

LegoFile::LegoFile() {
	m_file = NULL;
}

LegoFile::~LegoFile() {
	if (m_file) {
		fclose(m_file);
	}
}

LegoResult LegoFile::Read(void* p_buffer, LegoU32 p_size) {
	if (!m_file) {
		return FAILURE;
	}
	if (fread(p_buffer, 1, p_size, m_file) != p_size) {
		return FAILURE;
	}
	return SUCCESS;
}

LegoResult LegoFile::Write(const void* p_buffer, LegoU32 p_size) {
	if (!m_file) {
		return FAILURE;
	}
	if (fwrite(p_buffer, 1, p_size, m_file) != p_size) {
		return FAILURE;
	}
	return SUCCESS;
}

LegoResult LegoFile::GetPosition(LegoU32& p_position) {
	if (!m_file) {
		return FAILURE;
	}
	LegoU32 position = ftell(m_file);
	if (position == -1) {
		return FAILURE;
	}
	p_position = position;
	return SUCCESS;
}

LegoResult LegoFile::SetPosition(LegoU32 p_position) {
	if (!m_file) {
		return FAILURE;
	}
	if (fseek(m_file, p_position, SEEK_SET) != 0) {
		return FAILURE;
	}
	return SUCCESS;
}

LegoResult LegoFile::Open(const char* p_name, LegoU32 p_mode) {
	(void) p_mode;
	if (m_file) {
		fclose(m_file);
	}

	if (!(m_file = asset_fopen(p_name, nullptr))) {
		return FAILURE;
	}
	return SUCCESS;
}
