#pragma once

#include "lod_list.h"
#include "mx_string.h"

class LegoNamedPart {
public:
	LegoNamedPart(const char* p_name, LegoLODList* p_list)
		: m_name(p_name), m_list(p_list) {}
	~LegoNamedPart() {
		LegoLODListCursor cursor(m_list);
		LegoLOD* lod = nullptr;

		while (cursor.First(lod)) {
			cursor.Detach();
			delete lod;
		}

		delete m_list;
	}

	const MxString* GetName() const { return &m_name; }
	LegoLODList* GetList() { return m_list; }

private:
	MxString m_name;
	LegoLODList* m_list;
};

