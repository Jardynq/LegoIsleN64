#ifndef ROI_H
#define ROI_H

// ROI stands for Real-time Object Instance.

#include "lod_list.h"
#include "mx_geometry_3d.h"

/*
 * A simple bounding box object with Min and Max accessor methods.
 */

class BoundingBox {
public:
	const Vector3& Min() const { return min; }
	Vector3& Min() { return min; }
	const Vector3& Max() const { return max; }
	Vector3& Max() { return max; }

private:
	Mx3DPointFloat min;
	Mx3DPointFloat max;
};

/*
 * A simple bounding sphere object with center and radius accessor methods.
 */

class BoundingSphere {
public:
	const Vector3& Center() const { return center; }
	Vector3& Center() { return center; }
	const float& Radius() const { return radius; }
	float& Radius() { return radius; }

	// BoundingSphere::operator=

private:
	Mx3DPointFloat center;
	float radius;
};

/*
 * Abstract base class representing a single LOD version of
 * a geometric object.
 */

class LODObject {
public:
	// LODObject();

	virtual ~LODObject() {}

	virtual double AveragePolyArea() const = 0;
	virtual int NVerts() const = 0;
	virtual int NumPolys() const = 0;
	virtual float VTable0x10() = 0;

	// LODObject::`scalar deleting destructor'
};

/*
 * A CompoundObject is simply a set of ROI objects which
 * all together represent a single object with sub-parts.
 */
class ROI;
// typedef std::set<ROI*, std::less<const ROI*> > CompoundObject;
typedef list<ROI*> CompoundObject;

/*
 * A ROIList is a list of ROI objects.
 */
typedef vector<const ROI*> ROIList;

/*
 * A simple list of integers.
 * Returned by RealtimeView::SelectLODs as indices into an ROIList.
 */
typedef vector<int> IntList;

class ROI {
public:
	ROI() : comp(0), lods(0), m_visible(true) {}
	virtual ~ROI() {
		// if derived class set the comp and lods, it should delete them
		assert(!comp);
		assert(!lods);
	}
	virtual float IntrinsicImportance() const = 0;
	virtual const float* GetWorldVelocity() const = 0;
	virtual const BoundingBox& GetWorldBoundingBox() const = 0;
	virtual const BoundingSphere& GetWorldBoundingSphere() const = 0;

	const LODListBase* GetLODs() const { return lods; }
	const LODObject* GetLOD(int i) const {
		assert(lods);
		return (*lods)[i];
	}
	int GetLODCount() const { return lods ? lods->Size() : 0; }

	const CompoundObject* GetComp() const { return comp; }

	unsigned char GetVisibility() { return m_visible; }

	void SetVisibility(unsigned char p_visible) { m_visible = p_visible; }

	// ROI::`scalar deleting destructor'

protected:
	CompoundObject* comp;
	LODListBase* lods;
	unsigned char m_visible;
};

// list<ROI *,allocator<ROI *> >::~list<ROI *,allocator<ROI *> >

// ROI::~ROI

#endif // ROI_H
