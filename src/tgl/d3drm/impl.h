
#include "tgl/tgl.h"

#include <d3drm.h>

#ifdef DIRECTX5_SDK
typedef DWORD LPD3DRM_APPDATA;
#else
typedef LPVOID LPD3DRM_APPDATA;
#endif

// Forward declare D3D types
struct IDirect3DRM2;
struct IDirect3DRMDevice2;
struct IDirect3DRMViewport;
struct IDirect3DRMFrame2;
struct IDirect3DRMMesh;
struct IDirect3DRMMeshBuilder;
struct IDirect3DRMTexture;

namespace TglImpl {

using namespace Tgl;

// Utility function used by implementations
inline Result ResultVal(HRESULT result) {
	return SUCCEEDED(result) ? Success : Error;
}

// Forward declare implementations
class RendererImpl;
class DeviceImpl;
class ViewImpl;
class LightImpl;
class CameraImpl;
class GroupImpl;
class MeshImpl;
class TextureImpl;
class MeshBuilderImpl;

class RendererImpl : public Renderer {
public:
	RendererImpl() : m_data(0) {}
	~RendererImpl() override { Destroy(); }

	void* ImplementationDataPtr() override;

	Device* CreateDevice(const DeviceDirectDrawCreateData&) override;
	Device* CreateDevice(const DeviceDirect3DCreateData&) override;

	View* CreateView(
		const Device*,
		const Camera*,
		unsigned int x,
		unsigned int y,
		unsigned int width,
		unsigned int height
	) override;
	Camera* CreateCamera() override;
	Light* CreateLight(LightType, float r, float g, float b) override;
	Group* CreateGroup(const Group* pParent) override;

	MeshBuilder* CreateMeshBuilder() override;
	Texture* CreateTexture(
		int width,
		int height,
		int bitsPerTexel,
		const void* pTexels,
		int pTexelsArePersistent,
		int paletteEntryCount,
		const PaletteEntry* pEntries
	) override;
	Texture* CreateTexture() override;

	Result SetTextureDefaultShadeCount(unsigned int) override;

	Result SetTextureDefaultColorCount(unsigned int) override;

	HRESULT CreateTextureFromSurface(
		LPDIRECTDRAWSURFACE pSurface,
		LPDIRECT3DRMTEXTURE2* pTexture2
	) {
		return m_data->CreateTextureFromSurface(pSurface, pTexture2);
	}

	IDirect3DRM2* ImplementationData() const { return m_data; }

public:
	inline Result Create();
	inline void Destroy();

private:
	IDirect3DRM2* m_data;
};

extern IDirect3DRM2* g_pD3DRM;

inline void RendererDestroy(IDirect3DRM2* pRenderer) {
	int refCount = pRenderer->Release();
	if (refCount <= 0) {
		g_pD3DRM = NULL;
	}
}

// Inlined only
void RendererImpl::Destroy() {
	if (m_data) {
		RendererDestroy(m_data);
		m_data = NULL;
	}
}

class DeviceImpl : public Device {
public:
	DeviceImpl() : m_data(0) {}
	~DeviceImpl() override {
		if (m_data) {
			m_data->Release();
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	unsigned int GetWidth() override;
	unsigned int GetHeight() override;

	Result SetColorModel(ColorModel) override;
	Result SetShadingModel(ShadingModel) override;
	Result SetShadeCount(unsigned int) override;
	Result SetDither(int) override;

	Result Update() override;
	void HandleActivate(WORD) override;
	void HandlePaint(HDC) override;

	IDirect3DRMDevice2* ImplementationData() const { return m_data; }
	void SetImplementationData(IDirect3DRMDevice2* device) { m_data = device; }

	friend class RendererImpl;

private:
	IDirect3DRMDevice2* m_data;
};

class ViewImpl : public View {
public:
	ViewImpl() : m_data(0) {}
	~ViewImpl() override {
		if (m_data) {
			m_data->Release();
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	Result Add(const Light*) override;
	Result Remove(const Light*) override;

	Result SetCamera(const Camera*) override;
	Result SetProjection(ProjectionType) override;
	Result SetFrustrum(
		float frontClippingDistance,
		float backClippingDistance,
		float degrees
	) override;
	Result SetBackgroundColor(float r, float g, float b) override;

	Result GetBackgroundColor(float* r, float* g, float* b) override;
	Result Clear() override;
	Result Render(const Group*) override;
	Result ForceUpdate(
		unsigned int x,
		unsigned int y,
		unsigned int width,
		unsigned int height
	) override;

	Result
	TransformWorldToScreen(const float world[3], float screen[4]) override;
	Result
	TransformScreenToWorld(const float screen[4], float world[3]) override;
	Result Pick(
		unsigned int x,
		unsigned int y,
		const Group** ppGroupsToPickFrom,
		int groupsToPickFromCount,
		const Group**& rppPickedGroups,
		int& rPickedGroupCount
	) override;

	IDirect3DRMViewport* ImplementationData() const { return m_data; }
	void SetImplementationData(IDirect3DRMViewport* viewport) {
		m_data = viewport;
	}

	static Result
	ViewportCreateAppData(IDirect3DRM2*, IDirect3DRMViewport*, IDirect3DRMFrame2*);

	friend class RendererImpl;

private:
	IDirect3DRMViewport* m_data;
};

class CameraImpl : public Camera {
public:
	CameraImpl() : m_data(0) {}
	~CameraImpl() override {
		if (m_data) {
			m_data->Release();
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	Result SetTransformation(FloatMatrix4&) override;

	IDirect3DRMFrame2* ImplementationData() const { return m_data; }

	friend class RendererImpl;

private:
	IDirect3DRMFrame2* m_data;
};

class LightImpl : public Light {
public:
	LightImpl() : m_data(0) {}
	~LightImpl() override {
		if (m_data) {
			m_data->Release();
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	Result SetTransformation(FloatMatrix4&) override;
	Result SetColor(float r, float g, float b) override;

	IDirect3DRMFrame2* ImplementationData() const { return m_data; }

	friend class RendererImpl;

private:
	IDirect3DRMFrame2* m_data;
};

class MeshImpl : public Mesh {
public:
	MeshImpl() : m_data(0) {}
	~MeshImpl() override {
		if (m_data) {
			delete m_data;
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	Result SetColor(float r, float g, float b, float a) override;
	Result SetTexture(const Texture*) override;

	Result GetTexture(Texture*&) override;
	Result SetTextureMappingMode(TextureMappingMode) override;
	Result SetShadingModel(ShadingModel) override;
	Mesh* DeepClone(MeshBuilder*) override;

	Mesh* ShallowClone(MeshBuilder*) override;

	struct MeshData {
		IDirect3DRMMesh* groupMesh;
		D3DRMGROUPINDEX groupIndex;
	};

	typedef MeshData* MeshDataType;

	const MeshDataType& ImplementationData() const { return m_data; }
	MeshDataType& ImplementationData() { return m_data; }

	friend class RendererImpl;

private:
	MeshDataType m_data;
};

class GroupImpl : public Group {
public:
	GroupImpl() : m_data(0) {}
	~GroupImpl() override {
		if (m_data) {
			m_data->Release();
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	Result SetTransformation(FloatMatrix4&) override;
	Result SetColor(float r, float g, float b, float a) override;

	Result SetTexture(const Texture*) override;
	Result GetTexture(Texture*&) override;
	Result SetMaterialMode(MaterialMode) override;
	Result Add(const Group*) override;

	Result Add(const MeshBuilder*) override;
	Result Remove(const Group*) override;
	Result Remove(const MeshBuilder*) override;
	Result RemoveAll() override;

	Result Bounds(D3DVECTOR* p_min, D3DVECTOR* p_max) override;

	IDirect3DRMFrame2* ImplementationData() const { return m_data; }

	friend class RendererImpl;

private:
	IDirect3DRMFrame2* m_data;
};

class MeshBuilderImpl : public MeshBuilder {
public:
	MeshBuilderImpl() : m_data(0) {}
	~MeshBuilderImpl() override {
		if (m_data) {
			m_data->Release();
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	Mesh* CreateMesh(
		unsigned int faceCount,
		unsigned int vertexCount,
		float (*pPositions)[3],
		float (*pNormals)[3],
		float (*pTextureCoordinates)[2],
		unsigned int (*pFaceIndices)[3],
		unsigned int (*pTextureIndices)[3],
		ShadingModel shadingModel
	) override;
	Result GetBoundingBox(float min[3], float max[3]) const override;

	MeshBuilder* Clone() override;

	IDirect3DRMMesh* ImplementationData() const { return m_data; }

	friend class RendererImpl;

private:
	inline Result CreateMeshImpl(
		MeshImpl* pMeshImpl,
		unsigned int faceCount,
		unsigned int vertexCount,
		float (*pPositions)[3],
		float (*pNormals)[3],
		float (*pTextureCoordinates)[2],
		unsigned int (*pFaceIndices)[3],
		unsigned int (*pTextureIndices)[3],
		ShadingModel shadingModel
	);

	IDirect3DRMMesh* m_data;
};

// No vtable, this is just a simple wrapper around D3DRMIMAGE
class TglD3DRMIMAGE {
public:
	TglD3DRMIMAGE(
		int width,
		int height,
		int depth,
		void* pBuffer,
		int useBuffer,
		int paletteSize,
		PaletteEntry* pEntries
	);
	~TglD3DRMIMAGE() { Destroy(); }

	Result CreateBuffer(
		int width,
		int height,
		int depth,
		void* pBuffer,
		int useBuffer
	);
	void Destroy();
	Result FillRowsOfTexture(int y, int height, char* content);
	Result InitializePalette(int paletteSize, PaletteEntry* pEntries);

	D3DRMIMAGE m_image;
	int m_texelsAllocatedByClient;
};

class TextureImpl : public Texture {
public:
	TextureImpl() : m_data(0) {}
	~TextureImpl() override {
		if (m_data) {
			m_data->Release();
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	Result
	SetTexels(int width, int height, int bitsPerTexel, void* pTexels) override;
	void FillRowsOfTexture(int y, int height, void* pBuffer) override;

	Result Changed(int texelsChanged, int paletteChanged) override;
	Result GetBufferAndPalette(
		int* pWidth,
		int* pHeight,
		int* pDepth,
		void** ppBuffer,
		int* ppPaletteSize,
		PaletteEntry** ppPalette
	) override;
	Result SetPalette(int entryCount, PaletteEntry* entries) override;

	IDirect3DRMTexture* ImplementationData() const { return m_data; }
	void SetImplementation(IDirect3DRMTexture* pData) { m_data = pData; }

	friend class RendererImpl;

	static Result SetImage(IDirect3DRMTexture* pSelf, TglD3DRMIMAGE* pImage);

private:
	IDirect3DRMTexture* m_data;
};

// Translation helpers
inline D3DRMRENDERQUALITY Translate(ShadingModel tglShadingModel) {
	D3DRMRENDERQUALITY renderQuality;

	switch (tglShadingModel) {
	case Wireframe:
		renderQuality = D3DRMRENDER_WIREFRAME;
		break;
	case UnlitFlat:
		renderQuality = D3DRMRENDER_UNLITFLAT;
		break;
	case Flat:
		renderQuality = D3DRMRENDER_FLAT;
		break;
	case Gouraud:
		renderQuality = D3DRMRENDER_GOURAUD;
		break;
	case Phong:
		renderQuality = D3DRMRENDER_PHONG;
		break;
	default:
		renderQuality = D3DRMRENDER_FLAT;
		break;
	}

	return renderQuality;
}

inline D3DRMPROJECTIONTYPE Translate(ProjectionType tglProjectionType) {
	D3DRMPROJECTIONTYPE projectionType;
	switch (tglProjectionType) {
	case Perspective:
		projectionType = D3DRMPROJECT_PERSPECTIVE;
		break;
	case Orthographic:
		projectionType = D3DRMPROJECT_ORTHOGRAPHIC;
		break;
	default:
		projectionType = D3DRMPROJECT_PERSPECTIVE;
		break;
	}
	return projectionType;
}

// Yes this function serves no purpose, originally they intended it to
// convert from doubles to floats but ended up using floats throughout
// the software stack.
inline D3DRMMATRIX4D*
Translate(FloatMatrix4& tglMatrix4x4, D3DRMMATRIX4D& rD3DRMMatrix4x4) {
	for (int i = 0; i < (sizeof(rD3DRMMatrix4x4) / sizeof(rD3DRMMatrix4x4[0]));
		 i++) {
		for (int j = 0;
			 j < (sizeof(rD3DRMMatrix4x4[0]) / sizeof(rD3DRMMatrix4x4[0][0]));
			 j++) {
			rD3DRMMatrix4x4[i][j] = D3DVAL(tglMatrix4x4[i][j]);
		}
	}
	return &rD3DRMMatrix4x4;
}

// TglImpl::RendererImpl::`scalar deleting destructor'

// TglImpl::DeviceImpl::`scalar deleting destructor'

// TglImpl::ViewImpl::`scalar deleting destructor'

// TglImpl::GroupImpl::`scalar deleting destructor'

// TglImpl::CameraImpl::`scalar deleting destructor'

// TglImpl::LightImpl::`scalar deleting destructor'

// TglImpl::MeshBuilderImpl::`scalar deleting destructor'

// TglImpl::TextureImpl::`scalar deleting destructor'

// TglImpl::MeshImpl::`scalar deleting destructor'

// IID_IDirect3DRMMeshBuilder

} /* namespace TglImpl */
