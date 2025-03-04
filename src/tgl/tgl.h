
#ifndef _tgl_h
#define _tgl_h

#include "tglvector.h"

#include <d3d.h>
#include <ddraw.h>
#include <windows.h>

namespace Tgl {

enum ColorModel {
	// Note: Not used in shipped game, no way to verify contents.
	Ramp,
	RGB
};

enum ShadingModel { Wireframe, UnlitFlat, Flat, Gouraud, Phong };

enum LightType { Ambient, Point, Spot, Directional, ParallelPoint };

enum ProjectionType { Perspective, Orthographic };

enum TextureMappingMode { Linear, PerspectiveCorrect };

// Not in the Tgl leak, inferred from the assembly
enum MaterialMode {
	FromParent,
	FromFrame,
	FromMesh,
};

struct PaletteEntry {
	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;
};

struct DeviceDirect3DCreateData {
	IDirect3D2* m_pDirect3D;
	IDirect3DDevice2* m_pDirect3DDevice;
};

struct DeviceDirectDrawCreateData {
	const GUID* m_driverGUID;
	HWND m_hWnd;
	IDirectDraw* m_pDirectDraw;
	IDirectDrawSurface* m_pFrontBuffer;
	IDirectDrawSurface* m_pBackBuffer;

	// These have possibly been removed in the shipped game
	// (Put them back if we can verify when we find a callsite
	// which constructs this type)
	// IDirectDrawPalette* m_pPalette;
	// int m_isFullScreen;
};

// Result type used for all methods in the Tgl API
enum Result { Error = 0, Success = 1 };

inline int Succeeded(Result result) {
	return (result == Success);
}

// Forward declarations
class Renderer;
class Object;
class Device;
class View;
class Light;
class Camera;
class Group;
class Mesh;
class Texture;
class MeshBuilder;

class Object {
public:
	virtual ~Object() {}

	virtual void* ImplementationDataPtr() = 0;

	// Tgl::Object::`scalar deleting destructor'
};

class Renderer : public Object {
public:
	virtual Device* CreateDevice(const DeviceDirectDrawCreateData&) = 0;
	virtual Device* CreateDevice(const DeviceDirect3DCreateData&) = 0;

	virtual View* CreateView(
		const Device*,
		const Camera*,
		unsigned int x,
		unsigned int y,
		unsigned int width,
		unsigned int height
	) = 0;
	virtual Camera* CreateCamera() = 0;
	virtual Light* CreateLight(LightType, float r, float g, float b) = 0;
	virtual Group* CreateGroup(const Group* pParent = 0) = 0;

	virtual MeshBuilder* CreateMeshBuilder() = 0;
	virtual Texture* CreateTexture(
		int width,
		int height,
		int bitsPerTexel,
		const void* pTexels,
		int pTexelsArePersistent,
		int paletteEntryCount,
		const PaletteEntry* pEntries
	) = 0;
	virtual Texture* CreateTexture() = 0;
	virtual Result SetTextureDefaultShadeCount(unsigned int) = 0;

	virtual Result SetTextureDefaultColorCount(unsigned int) = 0;

	// Tgl::Renderer::~Renderer

	// Tgl::Renderer::`scalar deleting destructor'
};

Renderer* CreateRenderer();

class Device : public Object {
public:
	virtual unsigned int GetWidth() = 0;
	virtual unsigned int GetHeight() = 0;

	virtual Result SetColorModel(ColorModel) = 0;
	virtual Result SetShadingModel(ShadingModel) = 0;
	virtual Result SetShadeCount(unsigned int) = 0;
	virtual Result SetDither(int) = 0;

	virtual Result Update() = 0;
	virtual void HandleActivate(WORD) = 0;
	virtual void HandlePaint(HDC) = 0;

	// Tgl::Device::~Device

	// Tgl::Device::`scalar deleting destructor'
};

class View : public Object {
public:
	virtual Result Add(const Light*) = 0;
	virtual Result Remove(const Light*) = 0;

	virtual Result SetCamera(const Camera*) = 0;
	virtual Result SetProjection(ProjectionType) = 0;
	virtual Result SetFrustrum(
		float frontClippingDistance,
		float backClippingDistance,
		float degrees
	) = 0;
	virtual Result SetBackgroundColor(float r, float g, float b) = 0;

	virtual Result GetBackgroundColor(float* r, float* g, float* b) = 0;
	virtual Result Clear() = 0;
	virtual Result Render(const Group*) = 0;
	virtual Result ForceUpdate(
		unsigned int x,
		unsigned int y,
		unsigned int width,
		unsigned int height
	) = 0;

	virtual Result
	TransformWorldToScreen(const float world[3], float screen[4]) = 0;
	virtual Result
	TransformScreenToWorld(const float screen[4], float world[3]) = 0;

	// Pick():
	//  x, y:
	//      view coordinates
	//
	//  ppGroupsToPickFrom:
	//      array of (Group*) in any order
	//      Groups to pick from
	//
	//  groupsToPickFromCount:
	//      size of ppGroupsToPickFrom
	//
	//  rppPickedGroups:
	//      output parameter
	//      array of (Group*) representing a Group hierarchy
	//      top-down order (element 0 is root/scene)
	//      caller must deallocate array
	//      ref count of each element (Group*) has not been increased
	//      an element will be 0, if a corresponding Group was not found in
	//      ppGroupsToPickFrom
	//
	//  rPickedGroupCount:
	//      output parameter
	//      size of rppPickedGroups
	virtual Result Pick(
		unsigned int x,
		unsigned int y,
		const Group** ppGroupsToPickFrom,
		int groupsToPickFromCount,
		const Group**& rppPickedGroups,
		int& rPickedGroupCount
	) = 0;

	// Tgl::View::~View

	// Tgl::View::`scalar deleting destructor'
};

class Camera : public Object {
public:
	virtual Result SetTransformation(FloatMatrix4&) = 0;

	// Tgl::Camera::~Camera

	// Tgl::Camera::`scalar deleting destructor'
};

class Light : public Object {
public:
	virtual Result SetTransformation(FloatMatrix4&) = 0;
	virtual Result SetColor(float r, float g, float b) = 0;

	// Tgl::Light::~Light

	// Tgl::Light::`scalar deleting destructor'
};

class Mesh : public Object {
public:
	// Tgl::Mesh::~Mesh

	virtual Result SetColor(float r, float g, float b, float a) = 0;
	virtual Result SetTexture(const Texture*) = 0;
	virtual Result GetTexture(Texture*&) = 0;

	virtual Result SetTextureMappingMode(TextureMappingMode) = 0;
	virtual Result SetShadingModel(ShadingModel) = 0;

	// Clone data in underlying group
	virtual Mesh* DeepClone(MeshBuilder*) = 0;

	// Just get another Group pointing to the same underlying data
	virtual Mesh* ShallowClone(MeshBuilder*) = 0;

	// Tgl::Mesh::`scalar deleting destructor'
};

class Group : public Object {
public:
	virtual Result SetTransformation(FloatMatrix4&) = 0;
	virtual Result SetColor(float r, float g, float b, float a) = 0;
	virtual Result SetTexture(const Texture*) = 0;
	virtual Result GetTexture(Texture*&) = 0;
	virtual Result SetMaterialMode(MaterialMode) = 0;
	virtual Result Add(const Group*) = 0;
	virtual Result Add(const MeshBuilder*) = 0;
	virtual Result Remove(const Group*) = 0;
	virtual Result Remove(const MeshBuilder*) = 0;
	virtual Result RemoveAll() = 0;

	// This is TransformLocalToWorld in the leak, however it seems
	// to have been replaced by something else in the shipped code.
	virtual Result Bounds(D3DVECTOR*, D3DVECTOR*) = 0;

	// Tgl::Group::~Group

	// Tgl::Group::`scalar deleting destructor'
};

// Don't know what this is. Seems like another Tgl object which
// was not in the leaked Tgl code. My suspicion is that it's
// some kind of builder class for creating meshes.

class MeshBuilder : public Object {
public:
	virtual Mesh* CreateMesh(
		unsigned int faceCount,
		unsigned int vertexCount,
		float (*pPositions)[3],
		float (*pNormals)[3],
		float (*pTextureCoordinates)[2],
		unsigned int (*pFaceIndices)[3],
		unsigned int (*pTextureIndices)[3],
		ShadingModel shadingModel
	) = 0;
	virtual Result GetBoundingBox(float min[3], float max[3]) const = 0;
	virtual MeshBuilder* Clone() = 0;

	// Tgl::MeshBuilder::~MeshBuilder

	// Tgl::MeshBuilder::`scalar deleting destructor'
};

class Texture : public Object {
public:
	virtual Result
	SetTexels(int width, int height, int bitsPerTexel, void* pTexels) = 0;
	virtual void FillRowsOfTexture(int y, int height, void* pBuffer) = 0;

	virtual Result Changed(int texelsChanged, int paletteChanged) = 0;
	virtual Result GetBufferAndPalette(
		int* pWidth,
		int* pHeight,
		int* pDepth,
		void** ppBuffer,
		int* pPaletteSize,
		PaletteEntry** ppPalette
	) = 0;
	virtual Result SetPalette(int entryCount, PaletteEntry* pEntries) = 0;

	// Tgl::Texture::~Texture

	// Tgl::Texture::`scalar deleting destructor'
};

} // namespace Tgl

#endif /* _tgl_h */
