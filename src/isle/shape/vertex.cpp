#include "vertex.h"

#include "storage.h"

LegoVertex::LegoVertex() {
	m_coordinates[0] = 0.0F;
	m_coordinates[1] = 0.0F;
	m_coordinates[2] = 0.0F;
}

LegoResult LegoVertex::Read(LegoStorage* p_storage) {
	LegoResult result;
	if ((result = p_storage->Read(&m_coordinates[0], sizeof(m_coordinates[0]))
		) != SUCCESS) {
		return result;
	}
	if ((result = p_storage->Read(&m_coordinates[1], sizeof(m_coordinates[1]))
		) != SUCCESS) {
		return result;
	}
	if ((result = p_storage->Read(&m_coordinates[2], sizeof(m_coordinates[2]))
		) != SUCCESS) {
		return result;
	}
	return SUCCESS;
}
