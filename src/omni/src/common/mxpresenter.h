#ifndef MXPRESENTER_H
#define MXPRESENTER_H

#include "mxcore.h"
#include "mxcriticalsection.h"
#include "mxpoint32.h"

class MxCompositePresenter;
class MxDSAction;
class MxOmni;
class MxStreamController;
class MxEntity;

class MxPresenter : public MxCore {
public:
	enum TickleState {
		e_idle = 0,
		e_ready,
		e_starting,
		e_streaming,
		e_repeating,
		e_freezing,
		e_done,
	};

	MxPresenter() { Init(); }

	MxResult Tickle() override;

	virtual void VTable0x14() {}

	virtual void ReadyTickle() {
		ParseExtra();
		ProgressTickleState(e_starting);
	}

	virtual void StartingTickle() { ProgressTickleState(e_streaming); }

	virtual void StreamingTickle() { ProgressTickleState(e_repeating); }

	virtual void RepeatingTickle() { ProgressTickleState(e_freezing); }

	virtual void FreezingTickle() { ProgressTickleState(e_done); }

protected:
	virtual void DoneTickle() { ProgressTickleState(e_idle); }

	virtual void ParseExtra();

	void ProgressTickleState(TickleState p_tickleState) {
		m_previousTickleStates |= 1 << (MxU8) m_currentTickleState;
		m_currentTickleState = p_tickleState;
	}

public:
	~MxPresenter() override {}

	virtual MxResult AddToManager() { return SUCCESS; }

	virtual void Destroy() { Init(); }

	virtual MxResult StartAction(MxStreamController*, MxDSAction*);
	virtual void EndAction();

	virtual void SetTickleState(TickleState p_tickleState) {
		ProgressTickleState(p_tickleState);
	}

	virtual MxBool HasTickleStatePassed(TickleState p_tickleState) {
		return m_previousTickleStates & (1 << (MxU8) p_tickleState);
	}

	virtual MxResult PutData() { return SUCCESS; }

	virtual MxBool IsHit(MxS32 /*p_x*/, MxS32 /*p_y*/) { return FALSE; }

	virtual void Enable(MxBool p_enable);

	static const char* HandlerClassName() { return "MxPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxPresenter::ClassName()) || MxCore::IsA(p_name);
	}

	MxEntity* CreateEntity(const char* p_defaultName);
	void SendToCompositePresenter(MxOmni* p_omni);
	MxBool IsEnabled();

	MxS32 GetCurrentTickleState() const { return this->m_currentTickleState; }
	MxPoint32 GetLocation() const { return this->m_location; }
	MxS32 GetX() const { return this->m_location.GetX(); }
	MxS32 GetY() const { return this->m_location.GetY(); }
	MxS32 GetDisplayZ() const { return this->m_displayZ; }

	MxDSAction* GetAction() { return this->m_action; }

	void SetAction(MxDSAction* p_action) { m_action = p_action; }

	void SetCompositePresenter(MxCompositePresenter* p_compositePresenter) {
		m_compositePresenter = p_compositePresenter;
	}

	void SetDisplayZ(MxS32 p_displayZ) { m_displayZ = p_displayZ; }

	// MxPresenter::`scalar deleting destructor'

protected:
	void Init();

	TickleState m_currentTickleState;
	MxU32 m_previousTickleStates;
	MxPoint32 m_location;
	MxS32 m_displayZ;
	MxDSAction* m_action;
	MxCriticalSection m_criticalSection;
	MxCompositePresenter* m_compositePresenter;
};

const char* PresenterNameDispatch(const MxDSAction&);

#endif // MXPRESENTER_H
