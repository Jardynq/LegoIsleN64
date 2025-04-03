#ifndef LEGONAMEDTEXTURELIST_H
#define LEGONAMEDTEXTURELIST_H

#include "legonamedtexture.h"
#include "mxlist.h"

// class MxCollection<LegoNamedTexture *>

// class MxList<LegoNamedTexture *>

// class MxPtrList<LegoNamedTexture>

class LegoNamedTextureList : public MxPtrList<LegoNamedTexture> {
public:
	LegoNamedTextureList() : MxPtrList<LegoNamedTexture>(TRUE) {}

	// LegoNamedTextureList::`scalar deleting destructor'
};

// class MxListCursor<LegoNamedTexture *>

// class MxPtrListCursor<LegoNamedTexture>

class LegoNamedTextureListCursor : public MxPtrListCursor<LegoNamedTexture> {
public:
	LegoNamedTextureListCursor(LegoNamedTextureList* p_list)
		: MxPtrListCursor<LegoNamedTexture>(p_list) {}
};

// LegoNamedTextureListCursor::`scalar deleting destructor'

// MxPtrListCursor<LegoNamedTexture>::~MxPtrListCursor<LegoNamedTexture>

// MxListCursor<LegoNamedTexture *>::`scalar deleting destructor'

// MxPtrListCursor<LegoNamedTexture>::`scalar deleting destructor'

// MxListCursor<LegoNamedTexture *>::~MxListCursor<LegoNamedTexture *>

// LegoNamedTextureListCursor::~LegoNamedTextureListCursor

// MxCollection<LegoNamedTexture *>::Compare

// MxCollection<LegoNamedTexture *>::~MxCollection<LegoNamedTexture *>

// MxCollection<LegoNamedTexture *>::Destroy

// MxList<LegoNamedTexture *>::~MxList<LegoNamedTexture *>

// MxPtrList<LegoNamedTexture>::Destroy

// MxPtrList<LegoNamedTexture>::~MxPtrList<LegoNamedTexture>

// MxCollection<LegoNamedTexture *>::`scalar deleting destructor'

// MxList<LegoNamedTexture *>::`scalar deleting destructor'

// MxPtrList<LegoNamedTexture>::`scalar deleting destructor'

#endif // LEGONAMEDTEXTURELIST_H
