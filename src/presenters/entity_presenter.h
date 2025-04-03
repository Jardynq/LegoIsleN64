#ifndef LEGOENTITYPRESENTER_H
#define LEGOENTITYPRESENTER_H

#include "mx_composite_presenter.h"

class LegoEntity;
class Vector3;

class LegoEntityPresenter : public MxCompositePresenter {
public:
	LegoEntityPresenter();
	~LegoEntityPresenter() override;

	static const char* HandlerClassName() { return "LegoEntityPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoEntityPresenter::ClassName()) ||
			   MxCompositePresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void RepeatingTickle() override;
	void ParseExtra() override;
	void Destroy() override;
	MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action)
		override;
	virtual void Init();
	virtual undefined4 SetEntity(LegoEntity* p_entity);

	void SetEntityLocation(
		const Vector3& p_location,
		const Vector3& p_direction,
		const Vector3& p_up
	);

	LegoEntity* GetInternalEntity() { return m_entity; }
	void SetInternalEntity(LegoEntity* p_entity) { m_entity = p_entity; }

	// LegoEntityPresenter::`scalar deleting destructor'

private:
	void Destroy(MxBool p_fromDestructor);

protected:
	LegoEntity* m_entity;
};

#endif // LEGOENTITYPRESENTER_H
