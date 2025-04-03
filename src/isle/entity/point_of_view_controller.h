#pragma once

#include "mx_core.h"
#include "mx_point32.h"

class Lego3DView;
class LegoEntity;
class LegoNavController;

//////////////////////////////////////////////////////////////////////////////
//
// LegoMouseController

class LegoMouseController : public MxCore {
public:
	LegoMouseController();
	~LegoMouseController() override;

	virtual void LeftDown(int, int);
	virtual void LeftDrag(int, int);
	virtual void LeftUp(int, int);
	virtual void RightDown(int, int);
	virtual void RightDrag(int, int);
	virtual void RightUp(int, int);

	BOOL GetIsButtonDown() { return m_isButtonDown; }
	MxDouble GetButtonX() { return m_buttonX; }
	MxDouble GetButtonY() { return m_buttonY; }

private:
	BOOL m_isButtonDown;
	undefined4 m_unk0x0c;
	MxDouble m_buttonX;
	MxDouble m_buttonY;
};

// LegoMouseController::`scalar deleting destructor'

class LegoPointOfViewController : public LegoMouseController {
public:
	LegoPointOfViewController();
	~LegoPointOfViewController() override;

	MxResult Tickle() override;
	void LeftDown(int p_x, int p_y) override;
	void LeftDrag(int p_x, int p_y) override;

	void LeftUp(int p_x, int p_y) override {
		LegoMouseController::LeftUp(p_x, p_y);
		AffectPointOfView();
	}

	void RightDown(int p_x, int p_y) override {
		LegoMouseController::RightDown(p_x, p_y);
		AffectPointOfView();
	}

	void RightDrag(int p_x, int p_y) override {
		LegoMouseController::RightDrag(p_x, p_y);
		AffectPointOfView();
	}

	void RightUp(int p_x, int p_y) override {
		LegoMouseController::RightUp(p_x, p_y);
		AffectPointOfView();
	}
	virtual void SetEntity(LegoEntity* p_entity);

	MxResult Create(Lego3DView* p_lego3DView);
	void OnViewSize(int p_width, int p_height);

	LegoEntity* GetEntity() { return m_entity; }
	LegoNavController* GetNavController() { return m_nav; }

protected:
	void AffectPointOfView();

	Lego3DView* m_lego3DView;
	LegoEntity* m_entity;
	MxDouble m_entityOffsetUp;
	LegoNavController* m_nav;
};

// LegoPointOfViewController::`scalar deleting destructor'

