#pragma once

#include "mx_flc_presenter.h"

class LegoTextureInfo;

class LegoFlcTexturePresenter : public MxFlcPresenter {
public:
	LegoFlcTexturePresenter();

	static const char* HandlerClassName() { return "LegoFlcTexturePresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	void StartingTickle() override;
	void LoadFrame(MxStreamChunk* p_chunk) override;
	void PutFrame() override;

	// LegoFlcTexturePresenter::`scalar deleting destructor'

private:
	void Init();

	MxS32 m_rectCount;
	LegoTextureInfo* m_texture;
};

