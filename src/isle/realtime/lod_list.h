#pragma once

#include "assert.h"

#include <stddef.h>

class LODObject;

//////////////////////////////////////////////////////////////////////////////
//
// LODListBase
//
// An LODListBase is an ordered list of LODObjects
// where each successive object in the list has a more complex
// geometric representation than the one preceeding it.
//

class LODListBase {
protected:
	LODListBase(size_t capacity);

	const LODObject* PushBack(const LODObject*);
	const LODObject* PopBack();

public:
	virtual ~LODListBase();
	const LODObject* operator[](int) const;

	// current number of LODObject* in LODListBase
	size_t Size() const;

	// maximum number of LODObject* LODListBase can hold
	size_t Capacity() const;

	// LODListBase::`scalar deleting destructor'

private:
	// not implemented
	LODListBase(const LODListBase&);
	LODListBase& operator=(const LODListBase&);

private:
	const LODObject** m_ppLODObject;
	size_t m_capacity;
	size_t m_size;
};

//////////////////////////////////////////////////////////////////////////////
//
// LODList
//

template <class T>
class LODList : public LODListBase {
public:
	LODList(size_t capacity);

	const T* operator[](int) const;
	const T* PushBack(const T*);
	const T* PopBack();
};

//////////////////////////////////////////////////////////////////////////////
//
// LODListBase implementation

inline LODListBase::LODListBase(size_t capacity)
	: m_ppLODObject(new const LODObject*[capacity]), m_capacity(capacity),
	  m_size(0) {
}

inline LODListBase::~LODListBase() {
	// all LODObject* should have been popped by client
	assert(m_size == 0);

	delete[] m_ppLODObject;
}

inline size_t LODListBase::Size() const {
	return m_size;
}

inline size_t LODListBase::Capacity() const {
	return m_capacity;
}

inline const LODObject* LODListBase::operator[](int i) const {
	assert((0 <= i) && (i < (int) m_size));

	return m_ppLODObject[i];
}

inline const LODObject* LODListBase::PushBack(const LODObject* pLOD) {
	assert(m_size < m_capacity);

	m_ppLODObject[m_size++] = pLOD;
	return pLOD;
}

inline const LODObject* LODListBase::PopBack() {
	const LODObject* pLOD = nullptr;

	assert(m_size > 0);

	pLOD = m_ppLODObject[--m_size];

	return pLOD;
}

//////////////////////////////////////////////////////////////////////////////
//
// LODList implementation

template <class T>
inline LODList<T>::LODList(size_t capacity) : LODListBase(capacity) {
}

template <class T>
inline const T* LODList<T>::operator[](int i) const {
	return static_cast<const T*>(LODListBase::operator[](i));
}

template <class T>
inline const T* LODList<T>::PushBack(const T* pLOD) {
	return static_cast<const T*>(LODListBase::PushBack(pLOD));
}

template <class T>
inline const T* LODList<T>::PopBack() {
	return static_cast<const T*>(LODListBase::PopBack());
}

// class LODList<ViewLOD>

// LODList<ViewLOD>::`scalar deleting destructor'

// LODList<ViewLOD>::PopBack

// LODList<ViewLOD>::LODList<ViewLOD>

// LODList<ViewLOD>::~LODList<ViewLOD>

// LODList<ViewLOD>::operator[]

