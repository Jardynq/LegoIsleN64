#ifndef MXMIDIPRESENTER_H
#define MXMIDIPRESENTER_H

#include "mx_music_presenter.h"

class MxStreamChunk;

class MxMIDIPresenter : public MxMusicPresenter {
public:
	MxMIDIPresenter();
	~MxMIDIPresenter() override;

	static const char* HandlerClassName() { return "MxMIDIPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
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
