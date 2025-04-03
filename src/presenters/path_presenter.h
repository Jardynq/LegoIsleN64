#ifndef LEGOPATHPRESENTER_H
#define LEGOPATHPRESENTER_H

#include "mx_atom.h"
#include "mx_media_presenter.h"

class LegoPathPresenter : public MxMediaPresenter {
public:
	LegoPathPresenter();
	~LegoPathPresenter() override;

	static const char* HandlerClassName() { return "LegoPathPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoPathPresenter::ClassName()) ||
			   MxMediaPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StreamingTickle() override;
	void RepeatingTickle() override;
	void ParseExtra() override;
	MxResult AddToManager() override;
	void Destroy() override;

	// LegoPathPresenter::`scalar deleting destructor'

private:
	void Init();

protected:
	void Destroy(MxBool p_fromDestructor);

	MxAtomId m_trigger;
};

#endif // LEGOPATHPRESENTER_H
