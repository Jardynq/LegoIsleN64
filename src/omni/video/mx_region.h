#pragma once

#include "mx_core.h"
#include "mx_rect32.h"
#include "mx_region_list.h"

class MxRegion : public MxCore {
public:
	MxRegion();
	~MxRegion() override;

	virtual void Reset();
	virtual void VTable0x18(MxRect32& p_rect);
	virtual MxBool VTable0x1c(MxRect32& p_rect);
	virtual MxBool VTable0x20();

	MxRegionTopBottomList* GetTopBottomList() const { return m_list; }
	const MxRect32& GetRect() const { return m_rect; }

	friend class MxRegionCursor;

private:
	MxRegionTopBottomList* m_list;
	MxRect32 m_rect;
};

