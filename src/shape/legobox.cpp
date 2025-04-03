#include "legobox.h"

LegoResult LegoBox::Read(LegoStorage* p_storage) {
	LegoResult result;
	if ((result = m_min.Read(p_storage)) != SUCCESS) {
		return result;
	}
	if ((result = m_max.Read(p_storage)) != SUCCESS) {
		return result;
	}
	return SUCCESS;
}
