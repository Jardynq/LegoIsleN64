#ifndef _LegoView1_h
#define _LegoView1_h

#include "tglsurface.h"

namespace Tgl {
class Camera;
class Light;
} // namespace Tgl

/////////////////////////////////////////////////////////////////////////////
// LegoView

class LegoView : public TglSurface {
public:
	LegoView();
	~LegoView() override;

	BOOL Create(const CreateStruct&, Tgl::Renderer*);
	void Destroy() override;

	Tgl::Group* GetScene() const;
	Tgl::Camera* GetCamera() const;

protected:
	Tgl::View* CreateView(Tgl::Renderer*, Tgl::Device*) override;

private:
	Tgl::Group* m_pScene;
	Tgl::Camera* m_pCamera;
};

/////////////////////////////////////////////////////////////////////////////
// LegoView implementation

inline Tgl::Group* LegoView::GetScene() const {
	return m_pScene;
}

inline Tgl::Camera* LegoView::GetCamera() const {
	return m_pCamera;
}

// LegoView::`scalar deleting destructor'

/////////////////////////////////////////////////////////////////////////////
// LegoView1

class LegoView1 : public LegoView {
public:
	LegoView1();
	~LegoView1() override;

	BOOL AddLightsToViewport();
	BOOL Create(const TglSurface::CreateStruct&, Tgl::Renderer*);
	void Destroy() override;

	void SetLightTransform(BOOL bDirectionalLight, Tgl::FloatMatrix4& rMatrix);
	void
	SetLightColor(BOOL bDirectionalLight, float red, float green, float blue);

private:
	void SetLightTransform(Tgl::Light* pLight, Tgl::FloatMatrix4& rMatrix);
	void SetLightColor(Tgl::Light* pLight, float red, float green, float blue);

	Tgl::Light* m_pSunLight;
	Tgl::Light* m_pDirectionalLight;
	Tgl::Light* m_pAmbientLight;
};

// LegoView1::`scalar deleting destructor'

#endif /* _LegoView1_h */
