#ifndef MXFLCPRESENTER_H
#define MXFLCPRESENTER_H

#include "mxvideopresenter.h"

#include <flic.h>

class MxFlcPresenter : public MxVideoPresenter {
public:
	MxFlcPresenter();
	~MxFlcPresenter() override;

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxFlcPresenter::ClassName()) ||
			   MxVideoPresenter::IsA(p_name);
	}

	static const char* HandlerClassName() { return "MxFlcPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	void LoadHeader(MxStreamChunk* p_chunk) override;
	void CreateBitmap() override;
	void LoadFrame(MxStreamChunk* p_chunk) override;
	void RealizePalette() override;

	// MxFlcPresenter::`scalar deleting destructor'

protected:
	FLIC_HEADER* m_flcHeader;
};

#endif // MXFLCPRESENTER_H
