#ifndef _Lego3DView_h
#define _Lego3DView_h

#include "view1.h"

class ViewManager;
class ViewROI;

/////////////////////////////////////////////////////////////////////////////
// Lego3DView

class Lego3DView : public LegoView1 {
public:
	Lego3DView();
	~Lego3DView() override;

	BOOL Create(Tgl::Renderer*);
	void Destroy() override;

	BOOL Add(ViewROI&);
	BOOL Remove(ViewROI&);
	BOOL Moved(ViewROI&);
	BOOL SetPointOfView(ViewROI&);

	double Render(double p_und);

	ViewROI* Pick(unsigned int x, unsigned int y);

	ViewROI* GetPointOfView();
	ViewManager* GetViewManager();

private:
	ViewManager* m_pViewManager;
	double m_previousRenderTime;
	double m_unk0x98;
	ViewROI* m_pPointOfView;
};

// Lego3DView::`scalar deleting destructor'

/////////////////////////////////////////////////////////////////////////////
//
// Lego3DView implementation

inline ViewManager* Lego3DView::GetViewManager() {
	return m_pViewManager;
}

inline ViewROI* Lego3DView::GetPointOfView() {
	return m_pPointOfView;
}

#endif /* _Lego3DView_h */
