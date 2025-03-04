#ifndef MXEVENTPRESENTER_H
#define MXEVENTPRESENTER_H

#include "mxmediapresenter.h"

class MxEventPresenter : public MxMediaPresenter {
public:
	MxEventPresenter();
	~MxEventPresenter() override;

	static const char* HandlerClassName() { return "MxEventPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxEventPresenter::ClassName()) ||
			   MxMediaPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	MxResult AddToManager() override;
	void Destroy() override;
	MxResult PutData() override;
	virtual void CopyData(MxStreamChunk* p_chunk);

	// MxEventPresenter::`scalar deleting destructor'

private:
	void Init();

	MxU8* m_data;
};

#endif // MXEVENTPRESENTER_H
