#pragma once

#include "mx_presenter.h"

class MxEndActionNotificationParam;
class MxNotificationParam;

class MxCompositePresenterList : public list<MxPresenter*> {};

class MxCompositePresenter : public MxPresenter {
public:
	MxCompositePresenter();
	~MxCompositePresenter() override;

	MxLong Notify(MxParam& p_param) override;

	static const char* HandlerClassName() { return "MxCompositePresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxCompositePresenter::ClassName()) ||
			   MxPresenter::IsA(p_name);
	}

	MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action)
		override;
	void EndAction() override;
	void SetTickleState(TickleState p_tickleState) override;
	MxBool HasTickleStatePassed(TickleState p_tickleState) override;
	void Enable(MxBool p_enable) override;
	virtual void VTable0x58(MxEndActionNotificationParam& p_param);
	virtual void VTable0x5c(MxNotificationParam& p_param);
	virtual void VTable0x60(MxPresenter* p_presenter);

	virtual MxBool VTable0x64(undefined4 p_undefined) {
		if (m_compositePresenter) {
			return m_compositePresenter->VTable0x64(p_undefined);
		}
		return TRUE;
	}

	MxCompositePresenterList* GetList() { return &m_list; }

protected:
	MxCompositePresenterList m_list;
};

// list<MxPresenter *,allocator<MxPresenter *> >::_Buynode

// list<MxPresenter *,allocator<MxPresenter *> >::~list<MxPresenter
// *,allocator<MxPresenter *> >

// MxCompositePresenter::`scalar deleting destructor'

// MxCompositePresenterList::~MxCompositePresenterList

// List<MxPresenter *>::~List<MxPresenter *>

// MxList<MxDSAction *>::DeleteEntry

