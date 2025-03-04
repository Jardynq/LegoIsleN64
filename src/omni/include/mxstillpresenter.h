#ifndef MXSTILLPRESENTER_H
#define MXSTILLPRESENTER_H

#include "mxvideopresenter.h"

class MxStillPresenter : public MxVideoPresenter {
public:
	MxStillPresenter() { m_bitmapInfo = NULL; }

	~MxStillPresenter() override { Destroy(TRUE); }

	void Destroy() override { Destroy(FALSE); }

	static const char* HandlerClassName() { return "MxStillPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxStillPresenter::ClassName()) ||
			   MxVideoPresenter::IsA(p_name);
	}

	void StartingTickle() override;
	void StreamingTickle() override;
	void RepeatingTickle() override;
	void ParseExtra() override;
	void Enable(MxBool p_enable) override;
	void LoadHeader(MxStreamChunk* p_chunk) override;
	void CreateBitmap() override;
	void NextFrame() override;
	void LoadFrame(MxStreamChunk* p_chunk) override;
	void RealizePalette() override;
	virtual void SetPosition(MxS32 p_x, MxS32 p_y);
	virtual MxStillPresenter* Clone();

private:
	void Destroy(MxBool p_fromDestructor);

	MxLong m_chunkTime;
	MxBITMAPINFO* m_bitmapInfo;
};

// MxStillPresenter::`scalar deleting destructor'

#endif // MXSTILLPRESENTER_H
