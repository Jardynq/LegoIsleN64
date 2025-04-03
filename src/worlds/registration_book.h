#ifndef REGISTRATIONBOOK_H
#define REGISTRATIONBOOK_H

#include "world.h"

class InfocenterState;
class MxControlPresenter;
class MxEndActionNotificationParam;
class MxStillPresenter;
class LegoControlManagerNotificationParam;
class LegoPathStructNotificationParam;

class RegistrationBook : public LegoWorld {
public:
	RegistrationBook();
	~RegistrationBook() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	static const char* ClassName() { return "RegistrationBook"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, RegistrationBook::ClassName()) ||
			   LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;

	inline static void PlayAction(MxU32 p_objectId);

	// RegistrationBook::`scalar deleting destructor'

private:
	MxS32 m_registerDialogueTimer;
	undefined m_unk0xfc;
	undefined m_unk0xfd[3];
	MxStillPresenter* m_alphabet[26];
	MxStillPresenter* m_name[10][7];
	struct {
		MxS16 m_letters[7];
		MxS16 m_cursorPos;
	} m_unk0x280;
	MxControlPresenter* m_checkmark[10];
	undefined2 m_unk0x2b8;
	InfocenterState* m_infocenterState;
	undefined m_unk0x2c0;
	undefined m_unk0x2c1;
	undefined m_unk0x2c2[0x02];
	LPDIRECTDRAWSURFACE m_checkboxHilite;
	LPDIRECTDRAWSURFACE m_checkboxSurface;
	LPDIRECTDRAWSURFACE m_checkboxNormal;
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);
	MxLong HandleKeyPress(MxU8 p_key);
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param);
	void FUN_100775c0(MxS16 p_playerIndex);
	void WriteInfocenterLetters(MxS16);
	void FUN_100778c0();
	MxBool CreateSurface();
};

#endif // REGISTRATIONBOOK_H
