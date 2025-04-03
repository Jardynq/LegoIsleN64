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
#define X(V) m_id##V = MxAtomId(#V, e_exact);
	FOR_MXOBJECTFACTORY_OBJECTS(X)
#undef X
}

MxCore* MxObjectFactory::Create(const char* p_name) {
	MxCore* object = NULL;
	MxAtomId atom(p_name, e_exact);

	if (0) {
	}
#define X(V)                                                                   \
	else if (m_id##V == atom) {                                                \
		object = new V;                                                        \
	}
	FOR_MXOBJECTFACTORY_OBJECTS(X)
#undef X
	return object;
}

void MxObjectFactory::Destroy(MxCore* p_object) {
	delete p_object;
}
