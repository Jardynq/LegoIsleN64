#ifndef MXACTIONNOTIFICATIONPARAM_H
#define MXACTIONNOTIFICATIONPARAM_H

#include "mxdsaction.h"
#include "mxnotificationparam.h"

class MxPresenter;

class MxActionNotificationParam : public MxNotificationParam {
public:
	MxActionNotificationParam(
		NotificationId p_type,
		MxCore* p_sender,
		MxDSAction* p_action,
		MxBool p_reallocAction
	)
		: MxNotificationParam(p_type, p_sender) {
		MxDSAction* oldAction = p_action;
		m_realloc = p_reallocAction;

		if (p_reallocAction) {
			m_action = new MxDSAction();
		} else {
			m_action = oldAction;
			return;
		}

		m_action->SetAtomId(oldAction->GetAtomId());
		m_action->SetObjectId(oldAction->GetObjectId());
		m_action->SetUnknown24(oldAction->GetUnknown24());
	}

	~MxActionNotificationParam() override {
		if (!m_realloc) {
			return;
		}

		if (m_action) {
			delete m_action;
		}
	}

	MxNotificationParam* Clone() const override {
		return new MxActionNotificationParam(
			m_type,
			m_sender,
			m_action,
			m_realloc
		);
	}

	MxDSAction* GetAction() { return m_action; }

protected:
	MxDSAction* m_action;
	MxBool m_realloc;
};

class MxStartActionNotificationParam : public MxActionNotificationParam {
public:
	MxStartActionNotificationParam(
		NotificationId p_type,
		MxCore* p_sender,
		MxDSAction* p_action,
		MxBool p_reallocAction
	)
		: MxActionNotificationParam(
			  p_type,
			  p_sender,
			  p_action,
			  p_reallocAction
		  ) {}

	MxNotificationParam* Clone() const override;
};

class MxEndActionNotificationParam : public MxActionNotificationParam {
public:
	MxEndActionNotificationParam(
		NotificationId p_type,
		MxCore* p_sender,
		MxDSAction* p_action,
		MxBool p_reallocAction
	)
		: MxActionNotificationParam(
			  p_type,
			  p_sender,
			  p_action,
			  p_reallocAction
		  ) {}

	MxNotificationParam* Clone() const override {
		return new MxEndActionNotificationParam(
			c_notificationEndAction,
			m_sender,
			m_action,
			m_realloc
		);
	}
};

class MxType4NotificationParam : public MxActionNotificationParam {
public:
	MxType4NotificationParam(
		MxCore* p_sender,
		MxDSAction* p_action,
		MxPresenter* p_unk0x14
	)
		: MxActionNotificationParam(
			  c_notificationType4,
			  p_sender,
			  p_action,
			  FALSE
		  ) {
		m_unk0x14 = p_unk0x14;
	}

	MxNotificationParam* Clone() const override;

private:
	MxPresenter* m_unk0x14;
};

// MxActionNotificationParam::`scalar deleting destructor'

// MxEndActionNotificationParam::`scalar deleting destructor'

// MxEndActionNotificationParam::~MxEndActionNotificationParam

// MxStartActionNotificationParam::`scalar deleting destructor'

// MxStartActionNotificationParam::~MxStartActionNotificationParam

// MxType4NotificationParam::`scalar deleting destructor'

// MxType4NotificationParam::~MxType4NotificationParam

#endif
