#ifndef MXVIDEOPRESENTER_H
#define MXVIDEOPRESENTER_H

#include "mx_media_presenter.h"

class MxVideoPresenter : public MxMediaPresenter {
public:
	MxVideoPresenter() { Init(); }

	virtual void LoadHeader(MxStreamChunk* p_chunk) {}

	virtual void CreateBitmap() {}

	virtual void NextFrame();

	virtual void LoadFrame(MxStreamChunk* p_chunk) {}

	virtual void PutFrame();

	virtual void RealizePalette() {}

	virtual undefined VTable0x74();

	~MxVideoPresenter() override { Destroy(TRUE); }

	void Destroy() override { Destroy(FALSE); }

	virtual LPDIRECTDRAWSURFACE VTable0x78() { return m_unk0x58; }

	virtual MxBool VTable0x7c() {
		return m_frameBitmap != NULL || m_alpha != NULL;
	}

	virtual MxS32 GetWidth() {
		return m_alpha ? m_alpha->m_width : m_frameBitmap->GetBmiWidth();
	}

	virtual MxS32 GetHeight() {
		return m_alpha ? m_alpha->m_height : m_frameBitmap->GetBmiHeightAbs();
	}

	static const char* HandlerClassName() { return "MxVideoPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxVideoPresenter::ClassName()) ||
			   MxMediaPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	void StreamingTickle() override;
	void RepeatingTickle() override;
	void FreezingTickle() override;
	MxResult AddToManager() override;
	void EndAction() override;
	MxResult PutData() override;
	MxBool IsHit(MxS32 p_x, MxS32 p_y) override;

	struct AlphaMask {
		MxU8* m_bitmask;
		MxU16 m_width;
		MxU16 m_height;

		AlphaMask(const MxBitmap&);
		AlphaMask(const AlphaMask&);
		virtual ~AlphaMask();

		MxS32 IsHit(MxU32 p_x, MxU32 p_y);

		// MxVideoPresenter::AlphaMask::`scalar deleting destructor'
	};

	inline MxS32 PrepareRects(RECT& p_rectDest, RECT& p_rectSrc);
	MxBitmap* GetBitmap() { return m_frameBitmap; }
	AlphaMask* GetAlphaMask() { return m_alpha; }

	MxU8* GetBitmapStart(MxS32 p_left, MxS32 p_top) {
		return m_frameBitmap->GetStart(p_left, p_top);
	}

	void SetBit0(BOOL p_e) { m_flags.m_bit0 = p_e; }
	void SetBit1(BOOL p_e) { m_flags.m_bit1 = p_e; }
	void SetBit2(BOOL p_e) { m_flags.m_bit2 = p_e; }
	void SetBit3(BOOL p_e) { m_flags.m_bit3 = p_e; }
	void SetBit4(BOOL p_e) { m_flags.m_bit4 = p_e; }

	BYTE GetBit0() { return m_flags.m_bit0; }
	BYTE GetBit1() { return m_flags.m_bit1; }
	BYTE GetBit2() { return m_flags.m_bit2; }
	BYTE GetBit3() { return m_flags.m_bit3; }
	BYTE GetBit4() { return m_flags.m_bit4; }

	// MxVideoPresenter::`scalar deleting destructor'

private:
	void Init();

protected:
	void Destroy(MxBool p_fromDestructor);

	MxBitmap* m_frameBitmap;
	AlphaMask* m_alpha;
	LPDIRECTDRAWSURFACE m_unk0x58;
	MxS16 m_unk0x5c;
	FlagBitfield m_flags;
	MxLong m_unk0x60;
};

#endif // MXVIDEOPRESENTER_H
