#pragma once

#include "tgl.h"

#include <d3drmobj.h>
#include <ddraw.h>

class LegoTexture;

class LegoTextureInfo {
public:
	LegoTextureInfo();
	~LegoTextureInfo();

	static LegoTextureInfo* Create(const char* p_name, LegoTexture* p_texture);
	static BOOL
	SetGroupTexture(Tgl::Mesh* pMesh, LegoTextureInfo* p_textureInfo);
	static BOOL
	GetGroupTexture(Tgl::Mesh* pMesh, LegoTextureInfo*& p_textureInfo);

	LegoResult FUN_10066010(const LegoU8* p_bits);

	// private:
	char* m_name;
	LPDIRECTDRAWSURFACE m_surface;
	LPDIRECTDRAWPALETTE m_palette;
	LPDIRECT3DRMTEXTURE2 m_texture;
};

// IID_IDirect3DRMTexture2

