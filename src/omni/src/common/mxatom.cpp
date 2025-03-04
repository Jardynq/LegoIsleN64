#include "mxatom.h"

#include "mxmisc.h"
#include "mxomni.h"

#include <assert.h>

MxAtomId::MxAtomId(const char* p_str, LookupMode p_mode) {
	if (!MxOmni::GetInstance()) {
		return;
	}

	if (!AtomSet()) {
		return;
	}

	MxAtom* atom = GetAtom(p_str, p_mode);
	*this = atom->GetKey();
	atom->Inc();
}

MxAtomId::~MxAtomId() {
	Destroy();
}

void MxAtomId::Destroy() {
	if (!m_internal) {
		return;
	}

	if (!MxOmni::GetInstance()) {
		return;
	}

	if (!AtomSet()) {
		return;
	}

	MxAtomSet::iterator it;
	{
		MxAtom idAtom(m_internal);
		it = AtomSet()->find(&idAtom);
	}
	assert(it != AtomSet()->end());

	MxAtom* atom = (MxAtom*) (*it);
	atom->Dec();
}

MxAtomId& MxAtomId::operator=(const MxAtomId& p_atomId) {
	if (m_internal) {
		Destroy();
	}

	if (p_atomId.m_internal && MxOmni::GetInstance() && AtomSet()) {
		MxAtom* atom = GetAtom(p_atomId.m_internal, e_exact);
		atom->Inc();
	}

	m_internal = p_atomId.m_internal;

	return *this;
}

MxAtom* MxAtomId::GetAtom(const char* p_str, LookupMode p_mode) {
	MxAtomId unused;
	MxAtom* atom = new MxAtom(p_str);
	assert(atom);

	switch (p_mode) {
	case e_exact:
		break;
	case e_upperCase:
		atom->GetKey().ToUpperCase();
		break;
	case e_lowerCase:
	case e_lowerCase2:
		atom->GetKey().ToLowerCase();
		break;
	}

	MxAtomSet::iterator it = AtomSet()->find(atom);
	if (it != AtomSet()->end()) {
		// Atom already in the set. Delete temp value and return it.
		delete atom;
		atom = *it;
	} else {
		// Atom is not in the set. Add it.
		AtomSet()->insert(atom);
	}

	return atom;
}

void MxAtomId::Clear() {
	// Reset but do not delete MxAtomId object.
	Destroy();
	m_internal = NULL;
}

void MxAtom::Inc() {
	m_value++;
}

void MxAtom::Dec() {
	if (m_value) {
		m_value--;
	}
}
