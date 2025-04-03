#ifndef LEGOPHONEMEPRESENTER_H
#define LEGOPHONEMEPRESENTER_H

#include "mx_flc_presenter.h"
#include "mx_string.h"

class LegoTextureInfo;

class LegoPhonemePresenter : public MxFlcPresenter {
public:
	LegoPhonemePresenter();
	~LegoPhonemePresenter() override;

	static const char* HandlerClassName() { return "LegoPhonemePresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	void StartingTickle() override;
	void EndAction() override;
	void LoadFrame(MxStreamChunk* p_chunk) override;
	void PutFrame() override;

	// LegoPhonemePresenter::`scalar deleting destructor'

private:
	void Init();

	MxS32 m_rectCount;
	LegoTextureInfo* m_textureInfo;
	MxBool m_unk0x70;
	MxString m_roiName;
	MxBool m_unk0x84;
};

// MxListEntry<LegoPhoneme *>::MxListEntry<LegoPhoneme *>

#endif // LEGOPHONEMEPRESENTER_H
