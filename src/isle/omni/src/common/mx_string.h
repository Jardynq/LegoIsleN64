#pragma once

#include "mx_core.h"

class MxString : public MxCore {
public:
	MxString();
	MxString(const MxString& p_str);
	MxString(const char* p_str);
	MxString(const char* p_str, MxU16 p_maxlen);
	~MxString() override;

	void Reverse();
	void ToUpperCase();
	void ToLowerCase();

	MxString& operator=(const MxString& p_str);
	const MxString& operator=(const char* p_str);
	MxString operator+(const MxString& p_str) const;
	MxString operator+(const char* p_str) const;
	MxString& operator+=(const char* p_str);

	static void CharSwap(char* p_a, char* p_b);

	char* GetData() const { return m_data; }

	MxU16 GetLength() const { return m_length; }

	MxBool Equal(const MxString& p_str) const {
		return strcmp(m_data, p_str.m_data) == 0;
	}

	MxS8 Compare(const MxString& p_str) const {
		return strcmp(m_data, p_str.m_data);
	}

	// MxString::`scalar deleting destructor'

private:
	char* m_data;
	MxU16 m_length;
};

