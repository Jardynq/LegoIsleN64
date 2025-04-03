#include "graphics.h"
#include "t3d.h"
#include "t3dmodel.h"
#include "tgl.h"

namespace TglImpl {

using namespace Tgl;

// Utility function used by implementations
inline Result ResultVal(Result result) {
	return result;
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

public:
	inline Result Create();
	inline void Destroy();

private:
	Frame* m_data;
};

// Inlined only
void RendererImpl::Destroy() {
}

class DeviceImpl : public Device {
public:
	DeviceImpl() : m_data(0) {}
	~DeviceImpl() override {
		if (m_data) {
			free(m_data);
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

	Frame* ImplementationData() const { return m_data; }
	void SetImplementationData(Frame* device) { m_data = device; }

	friend class RendererImpl;

private:
	Frame* m_data;
};

class ViewImpl : public View {
public:
	ViewImpl() : m_data(0) {}
	~ViewImpl() override {
		if (m_data) {
			free(m_data);
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

	T3DViewport* ImplementationData() const { return m_data; }
	void SetImplementationData(T3DViewport* viewport) { m_data = viewport; }
	friend class RendererImpl;

private:
	T3DViewport* m_data;
};

class CameraImpl : public Camera {
public:
	CameraImpl() : m_data(0) {}
	~CameraImpl() override {
		if (m_data) {
			free(m_data);
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	Result SetTransformation(Matrix4&) override;

	Frame* ImplementationData() const { return m_data; }

	friend class RendererImpl;

private:
	Frame* m_data;
};

class LightImpl : public Light {
public:
	LightImpl() : m_data(0) {}
	~LightImpl() override {
		if (m_data) {
			free(m_data);
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	Result SetTransformation(Matrix4&) override;
	Result SetColor(float r, float g, float b) override;

	Frame* ImplementationData() const { return m_data; }

	friend class RendererImpl;

private:
	Frame* m_data;
};

class MeshImpl : public Mesh {
public:
	MeshImpl() : m_data(0) {}
	~MeshImpl() override {
		if (m_data) {
			free(m_data);
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

	typedef T3DModel* MeshDataType;

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
			free(m_data);
			m_data = NULL;
		}
	}

	void* ImplementationDataPtr() override;

	Result SetTransformation(Matrix4&) override;
	Result SetColor(float r, float g, float b, float a) override;

	Result SetTexture(const Texture*) override;
	Result GetTexture(Texture*&) override;
	Result SetMaterialMode(MaterialMode) override;
	Result Add(const Group*) override;

	Result Add(const MeshBuilder*) override;
	Result Remove(const Group*) override;
	Result Remove(const MeshBuilder*) override;
	Result RemoveAll() override;

	Result Bounds(float min[3], float max[3]) override;

	Frame* ImplementationData() const { return m_data; }

	friend class RendererImpl;

private:
	Frame* m_data;
};

class MeshBuilderImpl : public MeshBuilder {
public:
	MeshBuilderImpl() : m_data(0) {}
	~MeshBuilderImpl() override {
		if (m_data) {
			free(m_data);
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

	T3DModel* ImplementationData() const { return m_data; }

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

	T3DModel* m_data;
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

	sprite_t m_image;
	int m_texelsAllocatedByClient;
};

class TextureImpl : public Texture {
public:
	TextureImpl() : m_data(0) {}
	~TextureImpl() override {
		if (m_data) {
			free(m_data);
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

	sprite_t* ImplementationData() const { return m_data; }
	void SetImplementation(sprite_t* pData) { m_data = pData; }

	friend class RendererImpl;

	static Result SetImage(sprite_t* pSelf, TglD3DRMIMAGE* pImage);

private:
	sprite_t* m_data;
};

} /* namespace TglImpl */
