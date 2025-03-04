#ifndef LEGOPARTPRESENTER_H
#define LEGOPARTPRESENTER_H

#include "legonamedpartlist.h"
#include "mxmediapresenter.h"

class LegoPartPresenter : public MxMediaPresenter {
public:
	LegoPartPresenter() { Reset(); }

	~LegoPartPresenter() override { Destroy(TRUE); }

	void Destroy() override { Destroy(FALSE); }

	static const char* HandlerClassName() { return "LegoPartPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
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

#endif // LEGOPARTPRESENTER_H
