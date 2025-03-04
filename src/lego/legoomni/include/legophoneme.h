#ifndef LEGOPHONEME_H
#define LEGOPHONEME_H

#include "mxstring.h"

class LegoTextureInfo;

class LegoPhoneme {
public:
	LegoPhoneme(const char* p_name, undefined4 p_unk0x14)
		: m_name(p_name), m_unk0x14(p_unk0x14) {

		m_name.ToUpperCase();
		Init();
	}
	~LegoPhoneme();

	virtual undefined4 VTable0x00();
	virtual void VTable0x04(undefined4 p_unk0x14);
	virtual LegoTextureInfo* VTable0x08();
	virtual void VTable0x0c(LegoTextureInfo* p_unk0x18);
	virtual LegoTextureInfo* VTable0x10();
	virtual void VTable0x14(LegoTextureInfo* p_unk0x1c);
	virtual void VTable0x18();
	virtual void Init();
	virtual void VTable0x20(undefined4);

	MxString& GetName() { return m_name; }

private:
	MxString m_name;
	undefined4 m_unk0x14;
	LegoTextureInfo* m_unk0x18;
	LegoTextureInfo* m_unk0x1c;
};

#endif // LEGOPHONEME_H
