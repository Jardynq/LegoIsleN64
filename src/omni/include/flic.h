#ifndef FLIC_H
#define FLIC_H

#include <windows.h>

enum FLI_CHUNK_TYPE {
	FLI_CHUNK_COLOR256 = 4,  // 256-level color palette info
	FLI_CHUNK_SS2 = 7,       // Word-oriented delta compression
	FLI_CHUNK_COLOR64 = 11,  // 64-level color palette info
	FLI_CHUNK_LC = 12,       // Byte-oriented delta compression
	FLI_CHUNK_BLACK = 13,    // Entire frame is color index 0
	FLI_CHUNK_BRUN = 15,     // Byte run length compression
	FLI_CHUNK_COPY = 16,     // No compression
	FLI_CHUNK_PSTAMP = 18,   // Postage stamp sized image
	FLI_CHUNK_FRAME = 0xf1fa // Frame
};

#pragma pack(push, 1)
// A basic FLIC header structure from the "EGI" documentation. Source:
// https://www.compuphase.com/flic.htm#FLICHEADER This also goes over the FLIC
// structures:
// https://github.com/thinkbeforecoding/nomemalloc.handson/blob/master/flic.txt
typedef struct {
	DWORD size; /* Size of the chunk, including subchunks */
	WORD type;
} FLIC_CHUNK;

typedef struct : FLIC_CHUNK {
	WORD frames; /* Number of frames in first segment */
	WORD width;  /* FLIC width in pixels */
	WORD height; /* FLIC height in pixels */
	WORD depth;  /* Bits per pixel (usually 8) */
	WORD flags;  /* Set to zero or to three */
	DWORD speed; /* Delay between frames */
} FLIC_HEADER;
#pragma pack(pop)

typedef struct : FLIC_CHUNK {
	WORD chunks;   /* Number of subchunks */
	WORD delay;    /* Delay in milliseconds */
	WORD reserved; /* Always zero */
	WORD width;    /* Frame width override (if non-zero) */
	WORD height;   /* Frame height override (if non-zero) */
} FLIC_FRAME;

void DecodeFLCFrame(
	LPBITMAPINFOHEADER p_bitmapHeader,
	BYTE* p_pixelData,
	FLIC_HEADER* p_flcHeader,
	FLIC_FRAME* p_flcFrame,
	BYTE* p_decodedColorMap
);

#endif // FLIC_H
