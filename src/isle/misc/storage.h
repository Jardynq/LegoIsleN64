#pragma once

#include "mx_geometry_3d.h"
#include "mx_string.h"

#include <stdio.h>

class LegoStorage {
public:
	enum OpenFlags { c_read = 1, c_write = 2, c_text = 4 };

	LegoStorage() : m_mode(0) {}

	virtual ~LegoStorage() {}

	virtual LegoResult Read(void* p_buffer, LegoU32 p_size) = 0;
	virtual LegoResult Write(const void* p_buffer, LegoU32 p_size) = 0;
	virtual LegoResult GetPosition(LegoU32& p_position) = 0;
	virtual LegoResult SetPosition(LegoU32 p_position) = 0;

	virtual LegoBool IsWriteMode() { return m_mode == c_write; }

	virtual LegoBool IsReadMode() { return m_mode == c_read; }

	LegoStorage* WriteString(const char* p_data) {
		LegoS16 length = strlen(p_data);
		WriteS16(length);
		Write(p_data, length);
		return this;
	}

	LegoStorage* WriteU8(LegoU8 p_data) {
		Write(&p_data, sizeof(p_data));
		return this;
	}

	LegoStorage* WriteS16(LegoS16 p_data) {
		Write(&p_data, sizeof(p_data));
		return this;
	}

	LegoStorage* WriteU16(LegoU16 p_data) {
		Write(&p_data, sizeof(p_data));
		return this;
	}

	// TODO: Type might be different (LegoS32). MxS32 is incompatible with
	// LegoS32. FUNCTION: BETA10 0x10088540
	LegoStorage* WriteS32(MxS32 p_data) {
		Write(&p_data, sizeof(p_data));
		return this;
	}

	// TODO: Type might be different (LegoU32). MxU32 is incompatible with
	// LegoU32. FUNCTION: BETA10 0x1004b150
	LegoStorage* WriteU32(MxU32 p_data) {
		Write(&p_data, sizeof(p_data));
		return this;
	}

	LegoStorage* WriteFloat(LegoFloat p_data) {
		Write(&p_data, sizeof(p_data));
		return this;
	}

	LegoStorage* WriteVector(Mx3DPointFloat p_data) {
		WriteFloat(p_data[0]);
		WriteFloat(p_data[1]);
		WriteFloat(p_data[2]);
		return this;
	}

	LegoStorage* WriteMxString(const MxString& p_data) {
		WriteString(p_data.GetData());
		return this;
	}

	LegoStorage* ReadString(char* p_data) {
		LegoS16 length = 0;
		ReadS16(length);
		Read(p_data, length);
		p_data[length] = '\0';
		return this;
	}

	LegoStorage* ReadU8(LegoU8& p_data) {
		Read(&p_data, sizeof(p_data));
		return this;
	}

	LegoStorage* ReadS16(LegoS16& p_data) {
		Read(&p_data, sizeof(p_data));
		return this;
	}

	LegoStorage* ReadU16(LegoU16& p_data) {
		Read(&p_data, sizeof(p_data));
		return this;
	}

	// TODO: Type might be different (LegoS32). MxS32 is incompatible with
	// LegoS32. FUNCTION: BETA10 0x10088580
	LegoStorage* ReadS32(MxS32& p_data) {
		Read(&p_data, sizeof(p_data));
		return this;
	}

	// TODO: Type might be different (LegoU32). MxU32 is incompatible with
	// LegoU32. FUNCTION: BETA10 0x1004b210
	LegoStorage* ReadU32(MxU32& p_data) {
		Read(&p_data, sizeof(p_data));
		return this;
	}

	LegoStorage* ReadFloat(LegoFloat& p_data) {
		Read(&p_data, sizeof(p_data));
		return this;
	}

	LegoStorage* ReadVector(Mx3DPointFloat& p_data) {
		ReadFloat(p_data[0]);
		ReadFloat(p_data[1]);
		ReadFloat(p_data[2]);
		return this;
	}

	LegoStorage* ReadMxString(MxString& p_data) {
		LegoS16 length = 0;
		ReadS16(length);

		char* text = new char[length + 1];
		Read(text, length);

		text[length] = '\0';
		p_data = text;
		delete[] text;
		return this;
	}

	// LegoStorage::`scalar deleting destructor'

protected:
	LegoU8 m_mode;
};

class LegoMemory : public LegoStorage {
public:
	LegoMemory(void* p_buffer);
	LegoResult Read(void* p_buffer, LegoU32 p_size) override;
	LegoResult Write(const void* p_buffer, LegoU32 p_size) override;

	LegoResult GetPosition(LegoU32& p_position) override {
		p_position = m_position;
		return SUCCESS;
	}

	LegoResult SetPosition(LegoU32 p_position) override {
		m_position = p_position;
		return SUCCESS;
	}

	// LegoMemory::~LegoMemory

	// LegoMemory::`scalar deleting destructor'

protected:
	LegoU8* m_buffer;
	LegoU32 m_position;
};

class LegoFile : public LegoStorage {
public:
	LegoFile();
	~LegoFile() override;

	LegoResult Read(void* p_buffer, LegoU32 p_size) override;
	LegoResult Write(const void* p_buffer, LegoU32 p_size) override;
	LegoResult GetPosition(LegoU32& p_position) override;
	LegoResult SetPosition(LegoU32 p_position) override;
	LegoResult Open(const char* p_name, LegoU32 p_mode);

	// LegoFile::`scalar deleting destructor'

protected:
	FILE* m_file;
};

