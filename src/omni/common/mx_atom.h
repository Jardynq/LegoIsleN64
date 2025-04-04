#pragma once

#include "mx_string.h"

// Counts the number of existing MxAtomId objects based
// on the matching char* string. A <map> seems fit for purpose here:
// We have an MxString as a key and MxU16 as the value.
// And yet a <set> is the best match. The malloc in MxOmni::Create
// for the _Nil node asks for more bytes than a regular node if a <map>
// is used, but all nodes are 20 bytes wide with a <set>.
// Also: the increment/decrement methods suggest a custom type was used
// for the combined key_value_pair, which doesn't seem possible with <map>.

class MxAtom {
public:
	MxAtom(const char* p_str) : m_key(p_str), m_value(0) {}

	void Inc();
	void Dec();

	MxString& GetKey() { return m_key; }

private:
	MxString m_key;
	MxU16 m_value;
};

struct MxAtomCompare {
	int operator()(MxAtom* const& p_val0, MxAtom* const& p_val1) const {
		return strcmp(p_val0->GetKey().GetData(), p_val1->GetKey().GetData()) >
			   0;
	}
};

class MxAtomSet : public set<MxAtom*, MxAtomCompare> {};

enum LookupMode {
	e_exact = 0,
	e_lowerCase,
	e_upperCase,
	e_lowerCase2,
};

class MxAtomId {
public:
	MxAtomId(const char*, LookupMode);
	~MxAtomId();

	MxAtomId& operator=(const MxAtomId& p_atomId);

	MxBool operator==(const MxAtomId& p_atomId) const {
		return this->m_internal == p_atomId.m_internal;
	}

	MxBool operator!=(const MxAtomId& p_atomId) const {
		return this->m_internal != p_atomId.m_internal;
	}

	MxBool operator==(const char* p_internal) const {
		return p_internal && !strcmp(m_internal, p_internal);
	}

	MxAtomId() : m_internal(0) {}

	void Clear();

	const char* GetInternal() const { return m_internal; }

private:
	MxAtomId& operator=(const MxString& p_key) {
		m_internal = p_key.GetData();
		return *this;
	}

	MxAtom* GetAtom(const char*, LookupMode);
	void Destroy();

	const char* m_internal;
};
