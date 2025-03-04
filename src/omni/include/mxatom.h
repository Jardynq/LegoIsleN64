#ifndef MXATOM_H
#define MXATOM_H

#include "mxstring.h"

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
	// always inlined

	MxAtom(const char* p_str) : m_key(p_str), m_value(0) {}

	void Inc();
	void Dec();

	MxString& GetKey() { return m_key; }

	// MxAtom::`scalar deleting destructor'

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

	// Required for modern compilers.
	// MSVC 4.20 uses a synthetic function from INCLUDE/UTILITY that inverts
	// operator==
	MxBool operator!=(const MxAtomId& p_atomId) const {
		return this->m_internal != p_atomId.m_internal;
	}

	// TODO:
	// BETA10 0x1007dc20 operator==
	// BETA10 0x10096970 operator!=

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

// ??9@YAHABVMxAtomId@@0@Z
// aka MxAtomId::operator!=

// MxAtom::~MxAtom

// clang-format off

// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::iterator::_Dec
// clang-format on

// clang-format off

// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::_Lbound
// clang-format on

// clang-format off

// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::_Insert
// clang-format on

// clang-format off

// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::const_iterator::operator*
// clang-format on

// clang-format off


// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::~_Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >
// clang-format on

// clang-format off

// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::iterator::_Inc
// clang-format on

// clang-format off


// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::erase
// clang-format on

// clang-format off

// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::size
// clang-format on

// clang-format off

// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::_Erase
// clang-format on

// clang-format off


// set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::~set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >
// clang-format on

// Set<MxAtom *,MxAtomCompare>::~Set<MxAtom *,MxAtomCompare>

// set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::begin

// clang-format off


// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::_Nil
// clang-format on

// clang-format off

// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::begin
// clang-format on

// set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::size

// set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::erase

// set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::end

// set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::find

// clang-format off

// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::find
// clang-format on

// MxAtom::~MxAtom

// set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::insert

// MxAtomSet::MxAtomSet

// Set<MxAtom *,MxAtomCompare>::Set<MxAtom *,MxAtomCompare>

// clang-format off

// set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >


// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::_Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >


// _Tree<MxAtom *,MxAtom *,set<MxAtom *,MxAtomCompare,allocator<MxAtom *> >::_Kfn,MxAtomCompare,allocator<MxAtom *> >::_Init
// clang-format on

// MxAtomSet::`scalar deleting destructor'

// MxAtomSet::~MxAtomSet

#endif // MXATOM_H
