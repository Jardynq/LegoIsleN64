#pragma once

#include "mx_rect16.h"
#include "mx_still_presenter.h"
#include "mx_string.h"

struct MeterRect : public MxRect16 {

	MeterRect() {}
};

class LegoMeterPresenter : public MxStillPresenter {
public:
	LegoMeterPresenter();
	~LegoMeterPresenter() override;

	// MxStillPresenter's `::ClassName` and `::IsA` are used.

	void StreamingTickle() override;
	void RepeatingTickle() override;
	void ParseExtra() override;

private:
	enum MeterLayout {
		e_leftToRight = 0,
		e_rightToLeft,
		e_bottomToTop,
		e_topToBottom
	};

	void DrawMeter();

	MxU8* m_meterPixels;
	MxU16 m_fillColor;
	MxString m_variable;
	MxFloat m_curPercent;
	MeterRect m_meterRect;
	MxS16 m_layout;
};

// LegoMeterPresenter::`scalar deleting destructor'

