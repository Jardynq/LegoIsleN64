#include "mx_object_factory.h"

#include "mx_composite_presenter.h"
#include "mx_event_presenter.h"
#include "mx_flc_presenter.h"
#include "mx_looping_flc_presenter.h"
#include "mx_looping_midi_presenter.h"
#include "mx_looping_smk_presenter.h"
#include "mx_midi_presenter.h"
#include "mx_presenter.h"
#include "mx_smk_presenter.h"
#include "mx_still_presenter.h"
#include "mx_video_presenter.h"
#include "mx_wave_presenter.h"

MxObjectFactory::MxObjectFactory() {
	m_idMxPresenter = MxAtomId("MxPresenter", e_exact);
	m_idMxCompositePresenter = MxAtomId("MxCompositePresenter", e_exact);
	m_idMxVideoPresenter = MxAtomId("MxVideoPresenter", e_exact);
	m_idMxFlcPresenter = MxAtomId("MxFlcPresenter", e_exact);
	m_idMxSmkPresenter = MxAtomId("MxSmkPresenter", e_exact);
	m_idMxStillPresenter = MxAtomId("MxStillPresenter", e_exact);
	m_idMxWavePresenter = MxAtomId("MxWavePresenter", e_exact);
	m_idMxMIDIPresenter = MxAtomId("MxMIDIPresenter", e_exact);
	m_idMxEventPresenter = MxAtomId("MxEventPresenter", e_exact);
	m_idMxLoopingFlcPresenter = MxAtomId("MxLoopingFlcPresenter", e_exact);
	m_idMxLoopingSmkPresenter = MxAtomId("MxLoopingSmkPresenter", e_exact);
	m_idMxLoopingMIDIPresenter = MxAtomId("MxLoopingMIDIPresenter", e_exact);
}

MxCore* MxObjectFactory::Create(const char* p_name) {
	MxCore* object = NULL;
	MxAtomId atom(p_name, e_exact);

	if (m_idMxPresenter == atom) {
		object = (MxCore*) new MxPresenter;
	} else if (m_idMxCompositePresenter == atom) {
		object = (MxCore*) new MxCompositePresenter;
	} else if (m_idMxVideoPresenter == atom) {
		object = (MxCore*) new MxVideoPresenter;
	} else if (m_idMxFlcPresenter == atom) {
		object = (MxCore*) new MxFlcPresenter;
	} else if (m_idMxSmkPresenter == atom) {
		object = (MxCore*) new MxSmkPresenter;
	} else if (m_idMxStillPresenter == atom) {
		object = (MxCore*) new MxStillPresenter;
	} else if (m_idMxWavePresenter == atom) {
		object = (MxCore*) new MxWavePresenter;
	} else if (m_idMxMIDIPresenter == atom) {
		object = (MxCore*) new MxMIDIPresenter;
	} else if (m_idMxEventPresenter == atom) {
		object = (MxCore*) new MxEventPresenter;
	} else if (m_idMxLoopingFlcPresenter == atom) {
		object = (MxCore*) new MxLoopingFlcPresenter;
	} else if (m_idMxLoopingSmkPresenter == atom) {
		object = (MxCore*) new MxLoopingSmkPresenter;
	} else if (m_idMxLoopingMIDIPresenter == atom) {
		object = (MxCore*) new MxLoopingMIDIPresenter;
	}

	return object;
}

void MxObjectFactory::Destroy(MxCore* p_object) {
	delete p_object;
}
