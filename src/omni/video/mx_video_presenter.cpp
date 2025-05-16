#include "mx_video_presenter.h"

#include "mpeg2.h"
#include "mx_ds_media_action.h"
#include "mx_misc.h"
#include "mx_region_cursor.h"
#include "mx_video_manager.h"
#include "mxautolock.h"
#include "yuv.h"

MxVideoPresenter::AlphaMask::AlphaMask(const yuv_frame_t& p_bitmap) {
	m_width = p_bitmap.y.width;
	m_height = p_bitmap.y.height;

	MxS32 size = ((m_width * m_height) / 8) + 1;
	m_bitmask = new MxU8[size];
	memset(m_bitmask, 0, size);

	// The actual offset into the m_bitmask array. The two for-loops
	// are just for counting the pixels.
	MxS32 offset = 0;

	MxU8* bitmapSrcPtr = (u8*) p_bitmap.y.buffer;
	for (MxS32 j = 0; j < m_height; j++) {
		MxU8* tPtr = (u8*) bitmapSrcPtr;
		for (MxS32 i = 0; i < m_width; i++) {
			if (*tPtr) {
				MxU32 shift = abs(offset) & 7;
				m_bitmask[offset / 8] |= (1 << abs((MxS32) shift));
			}
			tPtr++;
			offset++;
		}
		// Seek to the start of the next row
		bitmapSrcPtr += p_bitmap.y.stride;
	}
}

MxVideoPresenter::AlphaMask::AlphaMask(
	const MxVideoPresenter::AlphaMask& p_alpha
) {
	m_width = p_alpha.m_width;
	m_height = p_alpha.m_height;

	MxS32 size = ((m_width * m_height) / 8) + 1;
	m_bitmask = new MxU8[size];
	memcpy(m_bitmask, p_alpha.m_bitmask, size);
}

MxVideoPresenter::AlphaMask::~AlphaMask() {
	if (m_bitmask) {
		delete[] m_bitmask;
	}
}

MxS32 MxVideoPresenter::AlphaMask::IsHit(MxU32 p_x, MxU32 p_y) {
	if (p_x >= m_width || p_y >= m_height) {
		return 0;
	}

	MxS32 pos = p_y * m_width + p_x;
	return m_bitmask[pos / 8] & (1 << abs(abs(pos) & 7)) ? 1 : 0;
}

void MxVideoPresenter::Init() {
	m_video = NULL;
	m_alpha = NULL;
	m_unk0x5c = 1;
	m_unk0x60 = -1;
	SetBit0(FALSE);

	if (MVideoManager() != NULL) {
		MVideoManager();
		SetBit1(TRUE);
		SetBit2(FALSE);
	}

	SetBit3(FALSE);
	SetBit4(FALSE);
}

void MxVideoPresenter::Destroy(MxBool p_fromDestructor) {
	if (MVideoManager() != NULL) {
		MVideoManager()->UnregisterPresenter(*this);
	}

	if (MVideoManager() && (m_alpha || m_video)) {
		// MxRect32 rect(m_location, MxSize32(GetWidth(), GetHeight()));
		MxS32 height = GetHeight();
		MxS32 width = GetWidth();
		MxS32 x = m_location.GetX();
		MxS32 y = m_location.GetY();

		MxRect32 rect(x, y, x + width, y + height);
		MVideoManager()->InvalidateRect(rect);
		MVideoManager()->UpdateView(
			rect.GetLeft(),
			rect.GetTop(),
			rect.GetWidth(),
			rect.GetHeight()
		);
	}

	mpeg2_close(m_video);
	m_video = nullptr;
	delete m_alpha;

	Init();

	if (!p_fromDestructor) {
		MxMediaPresenter::Destroy(FALSE);
	}
}

void MxVideoPresenter::NextFrame() {
	if (mpeg2_next_frame(m_video)) {
		m_frame = mpeg2_get_frame(m_video);
	}

	ProgressTickleState(e_repeating);
}

MxBool MxVideoPresenter::IsHit(MxS32 p_x, MxS32 p_y) {
	MxDSAction* action = GetAction();
	if ((action == NULL) ||
		(((action->GetFlags() & MxDSAction::c_bit11) == 0) && !IsEnabled()) ||
		(!m_video && !m_alpha)) {
		return FALSE;
	}

	if (!m_video) {
		return m_alpha->IsHit(p_x - m_location.GetX(), p_y - m_location.GetY());
	}

	MxLong heightAbs = m_frame.y.height;

	MxLong minX = m_location.GetX();
	MxLong minY = m_location.GetY();

	MxLong maxY = minY + heightAbs;
	MxLong maxX = minX + m_frame.y.width;

	if (p_x < minX || p_x >= maxX || p_y < minY || p_y >= maxY) {
		return FALSE;
	}

	MxLong x = p_y - m_location.GetY();
	MxLong y = p_x - m_location.GetX();
	MxU8* pixel = (u8*) m_frame.y.buffer + m_frame.y.stride * y - x;

	if (GetBit4()) {
		return (MxBool) *pixel;
	}

	if ((GetAction()->GetFlags() & MxDSAction::c_bit4) && *pixel == 0) {
		return FALSE;
	}

	return TRUE;
}

inline MxS32 MxVideoPresenter::PrepareRects(RECT& p_rectDest, RECT& p_rectSrc) {
	if (p_rectDest.top > 480 || p_rectDest.left > 640 || p_rectSrc.top > 480 ||
		p_rectSrc.left > 640) {
		return -1;
	}

	if (p_rectDest.bottom > 480) {
		p_rectDest.bottom = 480;
	}

	if (p_rectDest.right > 640) {
		p_rectDest.right = 640;
	}

	if (p_rectSrc.bottom > 480) {
		p_rectSrc.bottom = 480;
	}

	if (p_rectSrc.right > 640) {
		p_rectSrc.right = 640;
	}

	LONG height = 0, width = 0;
	if ((height = (p_rectDest.bottom - p_rectDest.top) + 1) <= 1 ||
		(width = (p_rectDest.right - p_rectDest.left) + 1) <= 1) {
		return -1;
	} else if ((p_rectSrc.right - p_rectSrc.left + 1) == width &&
			   (p_rectSrc.bottom - p_rectSrc.top + 1) == height) {
		return 1;
	} else {
		p_rectSrc.right = (p_rectSrc.left + width) - 1;
		p_rectSrc.bottom = (p_rectSrc.top + height) - 1;
		return 0;
	}
}

void MxVideoPresenter::PutFrame() {
	MxRegion* region = MVideoManager()->GetRegion();
	MxRect32 rect(MxPoint32(0, 0), MxSize32(GetWidth(), GetHeight()));
	rect.AddPoint(GetLocation());

	if (m_action->GetFlags() & MxDSAction::c_bit5) {
		RECT src, dest;
		src.top = 0;
		src.left = 0;
		src.right = GetWidth();
		src.bottom = GetHeight();

		dest.left = GetX();
		dest.top = GetY();
		dest.right = dest.left + GetWidth();
		dest.bottom = dest.top + GetHeight();

		if (PrepareRects(src, dest) >= 0) {
			// Todo, maybe consider scaling based on src/dest?
			if (m_yuv.block != nullptr) {
				yuv_blitter_free(&m_yuv);
			}
			m_yuv = yuv_blitter_new(
				dest.left,
				dest.top,
				GetWidth(),
				GetHeight(),
				nullptr,
				nullptr
			);
			yuv_blitter_run(&m_yuv, &m_frame);
		}
	} else {
		MxRegionCursor cursor(region);
		MxRect32* regionRect = nullptr;

		while ((regionRect = cursor.VTable0x24(rect))) {
			if (regionRect->GetWidth() >= 1 && regionRect->GetHeight() >= 1) {
				RECT src, dest;

				src.left = regionRect->GetLeft() - GetX();
				src.top = regionRect->GetTop() - GetY();
				src.right = src.left + regionRect->GetWidth();
				src.bottom = src.top + regionRect->GetHeight();

				dest.left = regionRect->GetLeft();
				dest.top = regionRect->GetTop();
				dest.right = dest.left + regionRect->GetWidth();
				dest.bottom = dest.top + regionRect->GetHeight();

				if (PrepareRects(src, dest) >= 0) {
					// Todo, maybe consider scaling based on src/dest?
					if (m_yuv.block != nullptr) {
						yuv_blitter_free(&m_yuv);
					}
					m_yuv = yuv_blitter_new(
						dest.left,
						dest.top,
						GetWidth(),
						GetHeight(),
						nullptr,
						nullptr
					);
					yuv_blitter_run(&m_yuv, &m_frame);
				}
			}
		}
	}
}

void MxVideoPresenter::ReadyTickle() {
	ParseExtra();
	ProgressTickleState(e_starting);
}

void MxVideoPresenter::StartingTickle() {
	if (m_action->GetElapsedTime() >= node->start_time) {
		CreateBitmap();
		ProgressTickleState(e_streaming);
	}
}

void MxVideoPresenter::StreamingTickle() {
	if (m_action->GetFlags() & MxDSAction::c_bit10) {
	} else {
		for (MxS16 i = 0; i < m_unk0x5c; i++) {
			if (m_action->GetElapsedTime() < node->start_time) {
				break;
			}

			SetBit0(TRUE);

			if (m_currentTickleState != e_streaming) {
				break;
			}
		}

		if (GetBit0()) {
			m_unk0x5c = 5;
		}
	}
}

void MxVideoPresenter::RepeatingTickle() {
	if (IsEnabled()) {
		if (m_action->GetFlags() & MxDSAction::c_bit10) {
		} else {
			for (MxS16 i = 0; i < m_unk0x5c; i++) {
				if (m_action->GetElapsedTime() % m_action->GetLoopCount() <
					node->start_time) {
					break;
				}

				SetBit0(TRUE);
				if (m_currentTickleState != e_repeating) {
					break;
				}
			}

			if (GetBit0()) {
				m_unk0x5c = 5;
			}
		}
	}
}

void MxVideoPresenter::FreezingTickle() {
	MxLong sustainTime = ((MxDSMediaAction*) m_action)->GetSustainTime();

	if (sustainTime != -1) {
		if (sustainTime) {
			if (m_unk0x60 == -1) {
				m_unk0x60 = m_action->GetElapsedTime();
			}

			if (m_action->GetElapsedTime() >=
				m_unk0x60 + ((MxDSMediaAction*) m_action)->GetSustainTime()) {
				ProgressTickleState(e_done);
			}
		} else {
			ProgressTickleState(e_done);
		}
	}
}

MxResult MxVideoPresenter::AddToManager() {
	MxResult result = FAILURE;

	if (MVideoManager()) {
		result = SUCCESS;
		MVideoManager()->RegisterPresenter(*this);
	}

	return result;
}

void MxVideoPresenter::EndAction() {
	if (m_action) {
		MxMediaPresenter::EndAction();

		if (m_video) {
			MxLong height = m_frame.y.height;
			MxLong width = m_frame.y.width;
			MxS32 x = m_location.GetX();
			MxS32 y = m_location.GetY();

			MxRect32 rect(x, y, x + width, y + height);

			MVideoManager()->InvalidateRect(rect);
		}
	}
}

MxResult MxVideoPresenter::PutData() {
	if (IsEnabled() && m_currentTickleState >= e_streaming &&
		m_currentTickleState <= e_freezing) {
		PutFrame();
	}

	return SUCCESS;
}

undefined MxVideoPresenter::VTable0x74() {
	return 0;
}
