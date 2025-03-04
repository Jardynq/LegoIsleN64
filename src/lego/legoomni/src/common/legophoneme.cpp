#include "legophoneme.h"

LegoPhoneme::~LegoPhoneme() {
}

undefined4 LegoPhoneme::VTable0x00() {
	return m_unk0x14;
}

void LegoPhoneme::VTable0x04(undefined4 p_unk0x14) {
	m_unk0x14 = p_unk0x14;
}

LegoTextureInfo* LegoPhoneme::VTable0x08() {
	return m_unk0x18;
}

void LegoPhoneme::VTable0x0c(LegoTextureInfo* p_unk0x18) {
	m_unk0x18 = p_unk0x18;
}

LegoTextureInfo* LegoPhoneme::VTable0x10() {
	return m_unk0x1c;
}

void LegoPhoneme::VTable0x14(LegoTextureInfo* p_unk0x1c) {
	m_unk0x1c = p_unk0x1c;
}

void LegoPhoneme::VTable0x18() {
}

void LegoPhoneme::Init() {
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
}

void LegoPhoneme::VTable0x20(undefined4) {
}
