#ifndef LEGOTEXTUREPRESENTER_H
#define LEGOTEXTUREPRESENTER_H

#include "legonamedtexturelist.h"
#include "mxmediapresenter.h"

class LegoTexturePresenter : public MxMediaPresenter {
public:
	LegoTexturePresenter() : m_textures(NULL) {}
	~LegoTexturePresenter() override;

	static const char* HandlerClassName() { return "LegoTexturePresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
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
