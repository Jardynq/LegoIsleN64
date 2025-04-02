#ifndef MXMEDIAPRESENTER_H
#define MXMEDIAPRESENTER_H

#include "mxpresenter.h"
#include "mxstreamchunklist.h"

class MxDSSubscriber;

class MxMediaPresenter : public MxPresenter {
public:
	MxMediaPresenter() { Init(); }

	~MxMediaPresenter() override { Destroy(TRUE); }

	void Destroy() override { Destroy(FALSE); }

	MxResult Tickle() override;

	static const char* HandlerClassName() { return "MxMediaPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxMediaPresenter::ClassName()) ||
			   MxPresenter::IsA(p_name);
	}

	void StreamingTickle() override;
	void RepeatingTickle() override;
	void DoneTickle() override;

	MxResult StartAction(MxStreamController*, MxDSAction*) override;
	void EndAction() override;
	void Enable(MxBool p_enable) override;
	virtual void LoopChunk(MxStreamChunk* p_chunk);

	MxStreamChunk* CurrentChunk();
	MxStreamChunk* NextChunk();

	// MxMediaPresenter::`scalar deleting destructor'

protected:
	MxDSSubscriber* m_subscriber;
	MxStreamChunkList* m_loopingChunks;
	MxStreamChunkListCursor* m_loopingChunkCursor;
	MxStreamChunk* m_currentChunk;
	void Init();
	void Destroy(MxBool p_fromDestructor);
};

// MxStreamChunkListCursor::`scalar deleting destructor'

// MxListCursor<MxStreamChunk *>::~MxListCursor<MxStreamChunk *>

// MxListCursor<MxStreamChunk *>::`scalar deleting destructor'

// MxStreamChunkListCursor::~MxStreamChunkListCursor

#endif // MXMEDIAPRESENTER_H
