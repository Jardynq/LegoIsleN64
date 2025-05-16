#pragma once

#include "mx_presenter.h"

class MxDSSubscriber;

class MxMediaPresenter : public MxPresenter {
public:
	MxMediaPresenter() { Init(); }

	~MxMediaPresenter() override { Destroy(TRUE); }

	void Destroy() override { Destroy(FALSE); }

	MxResult Tickle() override;

	static const char* HandlerClassName() { return "MxMediaPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxMediaPresenter::ClassName()) ||
			   MxPresenter::IsA(p_name);
	}

	void StreamingTickle() override;
	void RepeatingTickle() override;
	void DoneTickle() override;

	MxResult StartAction(MxStreamController*, MxDSAction*) override;
	void EndAction() override;
	void Enable(MxBool p_enable) override;

protected:
	void Init();
	void Destroy(MxBool p_fromDestructor);
};
