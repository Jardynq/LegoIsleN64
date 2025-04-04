#pragma once

#include "mx_region.h"

class MxRegionCursor : public MxCore {
public:
	MxRegionCursor(MxRegion* p_region);
	~MxRegionCursor() override;

	virtual MxRect32* VTable0x14(MxRect32& p_rect);
	virtual MxRect32* VTable0x18();
	virtual MxRect32* VTable0x1c(MxRect32& p_rect);
	virtual MxRect32* VTable0x20();
	virtual MxRect32* VTable0x24(MxRect32& p_rect);
	virtual MxRect32* VTable0x28();
	virtual MxRect32* VTable0x2c(MxRect32& p_rect);
	virtual MxRect32* VTable0x30();

	virtual MxRect32* GetRect() { return m_rect; }

	virtual MxBool HasRect() { return m_rect != NULL; }

	virtual void Reset();

private:
	void ResetAndInitializeCursor(MxRegionLeftRightList& p_leftRightList);
	void UpdateRect(MxS32 p_left, MxS32 p_top, MxS32 p_right, MxS32 p_bottom);
	void ProcessRectOverlapAscending(MxRect32& p_rect);
	void ProcessOverlapWithRect(MxRect32& p_rect);

	MxRegion* m_region;
	MxRect32* m_rect;
	MxRegionTopBottomListCursor* m_topBottomCursor;
	MxRegionLeftRightListCursor* m_leftRightCursor;
};

// MxRegionCursor::`scalar deleting destructor'

