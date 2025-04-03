#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "realtime_view.h"
#include "view_roi.h"

class ViewManager {
public:
	enum Flags { c_bit1 = 0x01, c_bit2 = 0x02, c_bit3 = 0x04, c_bit4 = 0x08 };

	ViewManager(
		Tgl::Renderer* pRenderer,
		Tgl::Group* scene,
		const OrientableROI* point_of_view
	);
	virtual ~ViewManager();

	void Remove(ViewROI* p_roi);
	void RemoveAll(ViewROI* p_roi);
	unsigned int IsBoundingBoxInFrustum(const BoundingBox& p_bounding_box);
	void UpdateROIDetailBasedOnLOD(ViewROI* p_roi, int p_und);
	void RemoveROIDetailFromScene(ViewROI* p_roi);
	void SetPOVSource(const OrientableROI* point_of_view);
	float ProjectedSize(const BoundingSphere& p_bounding_sphere);
	ViewROI* Pick(Tgl::View* p_view, unsigned int x, unsigned int y);
	void SetResolution(int width, int height);
	void SetFrustrum(float fov, float front, float back);
	inline void ManageVisibilityAndDetailRecursively(ViewROI* p_roi, int p_und);
	void Update(float p_previousRenderTime, float);
	inline int CalculateFrustumTransformations();
	void UpdateViewTransformations();

	inline static int
	CalculateLODLevel(float p_und1, float p_und2, ViewROI* p_roi);
	inline static int IsROIVisibleAtLOD(ViewROI* p_roi);

	const CompoundObject& GetROIs() { return rois; }

	void Add(ViewROI* p_roi) { rois.push_back(p_roi); }

	// ViewManager::`scalar deleting destructor'

private:
	Tgl::Group* scene;
	CompoundObject rois;
	RealtimeView rt_view;
	ROIList visible_rois;
	float prev_render_time;
	float view_area_at_one;
	unsigned int flags;
	float width;
	float height;
	float view_angle;
	MxMatrix pov;
	float front;
	float back;
	float frustum_vertices[8][3];
	float transformed_points[8][3];
	float frustum_planes[6][4];
	Tgl::Frame* frame;
	float seconds_allowed;
};

// list<ROI *,allocator<ROI *> >::insert

// List<ROI *>::~List<ROI *>

// Vector<ROI const *>::~Vector<ROI const *>

// vector<ROI const *,allocator<ROI const *> >::~vector<ROI const
// *,allocator<ROI const *> >

#endif // VIEWMANAGER_H
