#ifndef LEGOCONTAINER_H
#define LEGOCONTAINER_H

#include "texture.h"

// Note: dependency on LegoOmni
#include "texture_info.h"

#pragma warning(disable : 4237)

struct LegoContainerInfoComparator {
	LegoBool
	operator()(const char* const& p_key0, const char* const& p_key1) const {
		return strcmp(p_key0, p_key1) > 0;
	}
};

template <class T>
class LegoContainerInfo
	: public map<const char*, T*, LegoContainerInfoComparator> {};

template <class T>
class LegoContainer {
public:
	LegoContainer() { m_ownership = TRUE; }

	virtual ~LegoContainer() {
		typename LegoContainerInfo<T>::iterator it;
		for (it = m_map.begin(); it != m_map.end(); it++) {
			// DECOMP: Use of const_cast here matches ~ViewLODListManager from
			// 96 source.
			const char* const& key = (*it).first;
			delete[] const_cast<char*>(key);

			if (m_ownership) {
				delete (*it).second;
			}
		}
	}

	void Clear() {
		for (typename LegoContainerInfo<T>::iterator it = m_map.begin();
			 it != m_map.end();
			 it++) {
			delete (*it).second;
		}
	}

	T* Get(const char* p_name) {
		T* value = NULL;

		typename LegoContainerInfo<T>::iterator it = m_map.find(p_name);

		if (it != m_map.end()) {
			value = (*it).second;
		}

		return value;
	}

	void Add(const char* p_name, T* p_value) {
		typename LegoContainerInfo<T>::iterator it = m_map.find(p_name);

		char* name;
		if (it != m_map.end()) {
			name = const_cast<char*>((*it).first);

			if (m_ownership) {
				delete (*it).second;
			}
		} else {
			name = new char[strlen(p_name) + 1];
			strcpy(name, p_name);
		}

		m_map[name] = p_value;
	}

	void SetOwnership(LegoBool p_ownership) { m_ownership = p_ownership; }

protected:
	LegoBool m_ownership;
	LegoContainerInfo<T> m_map;
};

// class LegoContainer<LegoTextureInfo>

typedef pair<LegoTextureInfo*, BOOL> LegoCachedTexture;
typedef list<LegoCachedTexture> LegoCachedTextureList;

class LegoTextureContainer : public LegoContainer<LegoTextureInfo> {
public:
	~LegoTextureContainer() override;

	LegoTextureInfo* GetCached(LegoTextureInfo* p_textureInfo);
	void EraseCached(LegoTextureInfo* p_textureInfo);

protected:
	LegoCachedTextureList m_cached;
};

// allocator<LegoTextureInfo *>::_Charalloc

// clang-format off

// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Lbound


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::find


// map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::insert


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::iterator::_Dec


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Insert


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Color


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Left


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Parent


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Right


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::~_Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::iterator::_Inc


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::erase


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Erase


// list<pair<LegoTextureInfo *,int>,allocator<pair<LegoTextureInfo *,int> > >::~list<pair<LegoTextureInfo *,int>,allocator<pair<LegoTextureInfo *,int> > >


// map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::~map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >


// LegoContainer<LegoTextureInfo>::`scalar deleting destructor'


// LegoContainerInfo<LegoTextureInfo>::~LegoContainerInfo<LegoTextureInfo>


// Map<char const *,LegoTextureInfo *,LegoContainerInfoComparator>::~Map<char const *,LegoTextureInfo *,LegoContainerInfoComparator>


// LegoTextureContainer::`scalar deleting destructor'


// List<pair<LegoTextureInfo *,int> >::~List<pair<LegoTextureInfo *,int> >


// LegoContainer<LegoTextureInfo>::~LegoContainer<LegoTextureInfo>


// _Tree<char const *,pair<char const * const,LegoTextureInfo *>,map<char const *,LegoTextureInfo *,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Kfn,LegoContainerInfoComparator,allocator<LegoTextureInfo *> >::_Nil
// clang-format on

// LegoContainer<LegoTextureInfo>::Get

#endif // LEGOCONTAINER_H
