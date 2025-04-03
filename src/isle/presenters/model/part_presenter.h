#pragma once

#include "named_part_list.h"
#include "mx_media_presenter.h"

class LegoPartPresenter : public MxMediaPresenter {
public:
	LegoPartPresenter() { Reset(); }

	~LegoPartPresenter() override { Destroy(TRUE); }

	void Destroy() override { Destroy(FALSE); }

	static const char* HandlerClassName() { return "LegoPartPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoPartPresenter::ClassName()) ||
			   MxMediaPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	MxResult AddToManager() override;

	static void configureLegoPartPresenter(MxS32, MxS32);

	// LegoPartPresenter::`scalar deleting destructor'

	void Reset() { m_parts = NULL; }

	MxResult Read(MxDSChunk& p_chunk);
	void Store();

private:
	void Destroy(MxBool p_fromDestructor);

	LegoNamedPartList* m_parts;
};

