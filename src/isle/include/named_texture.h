#ifndef LEGONAMEDTEXTURE_H
#define LEGONAMEDTEXTURE_H

#include "texture.h"
#include "mx_string.h"

class LegoNamedTexture {
public:
	LegoNamedTexture(const char* p_name, LegoTexture* p_texture) {
		m_name = p_name;
		m_texture = p_texture;
	}
	~LegoNamedTexture() { delete m_texture; }

	const MxString* GetName() const { return &m_name; }

	LegoTexture* GetTexture() { return m_texture; }

private:
	MxString m_name;
	LegoTexture* m_texture;
};

#endif // LEGONAMEDTEXTURE_H
