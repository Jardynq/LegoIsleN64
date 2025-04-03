#ifndef MXVARIABLE_H
#define MXVARIABLE_H

#include "mx_core.h"
#include "mx_string.h"

class MxVariable {
public:
	MxVariable() {}

	MxVariable(const char* p_key, const char* p_value)
		: m_key(p_key), m_value(p_value) {

		m_key.ToUpperCase();
	}

	MxVariable(const char* p_key) : m_key(p_key) { m_key.ToUpperCase(); }

	virtual MxString* GetValue() { return &m_value; }

	virtual void SetValue(const char* p_value) { m_value = p_value; }

	virtual void Destroy() { delete this; }

	const MxString* GetKey() const { return &m_key; }

protected:
	MxString m_key;
	MxString m_value;
};

// MxVariable::~MxVariable

#endif // MXVARIABLE_H
