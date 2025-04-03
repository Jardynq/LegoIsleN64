#ifndef LEGOTEXTUREPRESENTER_H
#define LEGOTEXTUREPRESENTER_H

#include "named_texture_list.h"
#include "mx_media_presenter.h"

class LegoTexturePresenter : public MxMediaPresenter {
public:
	LegoTexturePresenter() : m_textures(NULL) {}
	~LegoTexturePresenter() override;

	static const char* HandlerClassName() { return "LegoTexturePresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoTexturePresenter::ClassName()) ||
			   MxMediaPresenter::IsA(p_name);
	}

	void DoneTickle() override;
	MxResult AddToManager() override;
	MxResult PutData() override;

	// LegoTexturePresenter::`scalar deleting destructor'

	MxResult Read(MxDSChunk& p_chunk);
	MxResult Store();

private:
	LegoNamedTextureList* m_textures;
};

#endif // LEGOTEXTUREPRESENTER_H
