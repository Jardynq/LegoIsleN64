#include "color.h"

#include "storage.h"

LegoResult LegoColor::Read(LegoStorage* p_storage) {
	LegoResult result;
	if ((result = p_storage->Read(&m_red, sizeof(m_red))) != SUCCESS) {
		return result;
	}
	if ((result = p_storage->Read(&m_green, sizeof(m_green))) != SUCCESS) {
		return result;
	}
	if ((result = p_storage->Read(&m_blue, sizeof(m_blue))) != SUCCESS) {
		return result;
	}
	return SUCCESS;
}
