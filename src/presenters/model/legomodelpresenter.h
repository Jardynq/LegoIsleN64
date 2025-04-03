#ifndef LEGOMODELPRESENTER_H
#define LEGOMODELPRESENTER_H

#include "mxvideopresenter.h"

class LegoROI;
class LegoWorld;
class LegoEntity;
class MxDSChunk;

class LegoModelPresenter : public MxVideoPresenter {
public:
	LegoModelPresenter() { Reset(); }

	~LegoModelPresenter() override { Destroy(TRUE); }

	void Destroy() override { Destroy(FALSE); }

	static void configureLegoModelPresenter(MxS32 p_modelPresenterConfig);

	static const char* HandlerClassName() { return "LegoModelPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, ClassName()) || MxVideoPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void ParseExtra() override;

	MxResult FUN_1007ff70(
		MxDSChunk& p_chunk,
		LegoEntity* p_entity,
		MxBool p_roiVisible,
		LegoWorld* p_world
	);

	void Reset() {
		m_roi = NULL;
		m_addedToView = FALSE;
	}

	// LegoModelPresenter::`scalar deleting destructor'

protected:
	void Destroy(MxBool p_fromDestructor);

private:
	LegoROI* m_roi;
	MxBool m_addedToView;
	MxResult CreateROI(MxDSChunk* p_chunk);
};

#endif // LEGOMODELPRESENTER_H
