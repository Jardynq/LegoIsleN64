#ifndef MXSMKPRESENTER_H
#define MXSMKPRESENTER_H

#include "mxsmk.h"
#include "mxvideopresenter.h"

class MxSmkPresenter : public MxVideoPresenter {
public:
	MxSmkPresenter();
	~MxSmkPresenter() override;

	static const char* HandlerClassName() { return "MxSmkPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxSmkPresenter::ClassName()) ||
			   MxVideoPresenter::IsA(p_name);
	}

	MxResult AddToManager() override;
	void Destroy() override;
	void LoadHeader(MxStreamChunk* p_chunk) override;
	void CreateBitmap() override;
	void LoadFrame(MxStreamChunk* p_chunk) override;
	void RealizePalette() override;
	virtual void VTable0x88();

	// MxSmkPresenter::`scalar deleting destructor'

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);

protected:
	MxSmk m_mxSmk;
	MxU32 m_currentFrame;
};

#endif // MXSMKPRESENTER_H
