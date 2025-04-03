#ifndef LEGOWORLDPRESENTER_H
#define LEGOWORLDPRESENTER_H

#include "entity_presenter.h"

#include <stdio.h>

class LegoWorld;
struct ModelDbPart;
struct ModelDbModel;

class LegoWorldPresenter : public LegoEntityPresenter {
public:
	LegoWorldPresenter();
	~LegoWorldPresenter() override;

	static void configureLegoWorldPresenter(MxS32 p_legoWorldPresenterQuality);

	static const char* HandlerClassName() { return "LegoWorldPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoWorldPresenter::ClassName()) ||
			   LegoEntityPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	void ParseExtra() override;
	MxResult StartAction(
		MxStreamController* p_controller,
		MxDSAction* p_action
	) override;
	void VTable0x60(MxPresenter* p_presenter) override;

	MxResult LoadWorld(char* p_worldName, LegoWorld* p_world);

private:
	MxResult FUN_10067360(ModelDbPart& p_part, FILE* p_wdbFile);
	MxResult
	FUN_100674b0(ModelDbModel& p_model, FILE* p_wdbFile, LegoWorld* p_world);

	undefined4 m_unk0x50;
};

#endif // LEGOWORLDPRESENTER_H
