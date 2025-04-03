#include "texture.h"

#include "image.h"
#include "storage.h"

LegoTexture::LegoTexture() {
	m_image = new LegoImage();
}

LegoTexture::~LegoTexture() {
	delete m_image;
}

LegoResult LegoTexture::Read(LegoStorage* p_storage, LegoU32 p_square) {
	return m_image->Read(p_storage, p_square);
}

LegoResult LegoTexture::Write(LegoStorage* p_storage) {
	return m_image->Write(p_storage);
}
