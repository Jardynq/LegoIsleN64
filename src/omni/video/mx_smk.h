#pragma once

#include "mx_rect_list.h"

#include <smack.h>

struct MxBITMAPINFO;

// These functions are not part of the public interface,
// but present in SMACK.LIB and used directly by Mindscape.
extern "C" {
u32 SmackGetSizeTables();
void SmackDoTables(
	u8* p_huffmanTrees,
	u8* p_huffmanTables,
	u32 p_codeSize,
	u32 p_abSize,
	u32 p_detailSize,
	u32 p_typeSize
);
void SmackDoFrameToBuffer(u8* p_source, u8* p_huffmanTables, u8* p_unk0x6b4);
u32 SmackGetSizeDeltas(u32 p_width, u32 p_height);
u8 SmackGetRect(u8* p_unk0x6b4, u32* p_rect);
}

struct MxSmk {
	SmackTag m_smackTag;
	undefined m_unk0x390[784];
	MxU32* m_frameSizes;
	MxU8* m_frameTypes;
	MxU8* m_huffmanTrees;
	MxU8* m_huffmanTables;
	MxU32 m_maxFrameSize;
	MxU8* m_unk0x6b4;
	static MxResult LoadHeader(MxU8* p_data, MxSmk* p_mxSmk);
	static void Destroy(MxSmk* p_mxSmk);
	static MxResult LoadFrame(
		MxBITMAPINFO* p_bitmapInfo,
		MxU8* p_bitmapData,
		MxSmk* p_mxSmk,
		MxU8* p_chunkData,
		MxBool p_paletteChanged,
		MxRectList* p_list
	);
	static MxBool
	GetRect(MxU8* p_unk0x6b4, MxU16* p_und, u32* p_smackRect, MxRect32* p_rect);
};

