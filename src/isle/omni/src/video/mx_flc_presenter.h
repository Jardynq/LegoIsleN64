#pragma once

#include "mx_video_presenter.h"

class MxFlcPresenter : public MxVideoPresenter {
public:
	MxFlcPresenter();
	~MxFlcPresenter() override;

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxFlcPresenter::ClassName()) ||
			   MxVideoPresenter::IsA(p_name);
	}

	static const char* HandlerClassName() { return "MxFlcPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	void LoadHeader(MxStreamChunk* p_chunk) override;
	void CreateBitmap() override;
	void LoadFrame(MxStreamChunk* p_chunk) override;
	void RealizePalette() override;

	// MxFlcPresenter::`scalar deleting destructor'

protected:
	FLIC_HEADER* m_flcHeader;
};

