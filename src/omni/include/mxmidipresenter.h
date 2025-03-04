#ifndef MXMIDIPRESENTER_H
#define MXMIDIPRESENTER_H

#include "mxmusicpresenter.h"

class MxStreamChunk;

class MxMIDIPresenter : public MxMusicPresenter {
public:
	MxMIDIPresenter();
	~MxMIDIPresenter() override;

	static const char* HandlerClassName() { return "MxMIDIPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxMIDIPresenter::ClassName()) ||
			   MxMusicPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	void StreamingTickle() override;
	void DoneTickle() override;
	void Destroy() override;
	void EndAction() override;
	MxResult PutData() override;
	void SetVolume(MxS32 p_volume) override;

	// MxMIDIPresenter::`scalar deleting destructor'

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);

protected:
	MxStreamChunk* m_chunk;
};

#endif // MXMIDIPRESENTER_H
