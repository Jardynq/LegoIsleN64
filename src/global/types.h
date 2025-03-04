#ifndef TYPES_H
#define TYPES_H

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <stdint.h>
#include <utility>
#include <vector>
using std::list;
using std::map;
using std::multiset;
using std::pair;
using std::set;
using std::vector;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef uintptr_t usize;
typedef intptr_t isize;
typedef float f32;
typedef double f64;

typedef u8 undefined;
typedef u16 undefined2;
typedef u32 undefined4;

typedef i32 Time;
// typedef i32 LegoResult;
// typedef i32 MxResult;

typedef u8 MxU8;
typedef u16 MxU16;
typedef u32 MxU32;
typedef u64 MxU64;
typedef i8 MxS8;
typedef i16 MxS16;
typedef i32 MxS32;
typedef i64 MxS64;
typedef f32 MxFloat;
typedef f64 MxDouble;
typedef i32 MxLong;
typedef u32 MxULong;
typedef Time MxTime;
typedef i32 MxResult;
typedef u8 MxBool;

typedef u8 LegoU8;
typedef u16 LegoU16;
typedef u32 LegoU32;
typedef i8 LegoS8;
typedef i16 LegoS16;
typedef i32 LegoS32;
typedef f32 LegoFloat;
typedef char LegoChar;

typedef u8 LegoBool;
typedef Time LegoTime;
typedef i32 LegoResult;

/*
typedef bool BOOL;
typedef char* LPCSTR;
typedef char* LPSTR;
typedef u32 DWORD;
typedef usize WPARAM;
typedef isize LPARAM;
typedef isize LRESULT;
typedef u32 HRESULT;
typedef usize SIZE_T;
typedef void* LPVOID;
typedef const void* LPCVOID;

typedef void* HANDLE;
typedef void* HCURSOR;
typedef void* HWND;
typedef void* HINSTANCE;
typedef void* HMODULE;
typedef void* HICON;
typedef void* HBRUSH;
typedef void* HFONT;
typedef void* HPEN;
typedef void* HBITMAP;
typedef void* HDC;
typedef void* HMENU;
typedef void* HMONITOR;
typedef void* HHOOK;
typedef void* HGLOBAL;
typedef void* HKEY;
typedef void* HWINSTA;
typedef void* HDESK;
typedef void* HFILE;
typedef void* HRGN;
typedef void* HTASK;
typedef void* HGDIOBJ;
typedef void* HPALETTE;

typedef u16 ATOM;
typedef u16 WORD;
typedef u8 BYTE;
typedef i8 CHAR;
typedef u16 WCHAR;
typedef WCHAR* LPWSTR;
typedef const WCHAR* LPCWSTR;
typedef u32 UINT;
typedef i32 INT;
typedef i64 LONGLONG;
typedef u64 ULONGLONG;
typedef i32 LONG;
typedef u32 ULONG;
typedef i16 SHORT;
typedef u16 USHORT;
typedef u32 UINT_PTR;
typedef isize INT_PTR;
typedef isize LONG_PTR;
typedef usize ULONG_PTR;

typedef struct {
	i32 left;
	i32 top;
	i32 right;
	i32 bottom;
} RECT;
*/

#define TRUE true
#define FALSE false

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE (-1)
#endif

#ifndef NULL
#define NULL 0
#endif

/*
typedef i32 Result;

typedef enum _Result {
	Error = 0,
	Success = 1
} Result;
*/

/*
#ifndef Success
#define Success 0
#endif

#ifndef Failure
#define Failure -1
#endif


*/

#define TWOCC(a, b) (((a) << 0) | ((b) << 8))
#define FOURCC(a, b, c, d) (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24))

typedef union {
	struct {
		u8 m_bit0 : 1;
		u8 m_bit1 : 1;
		u8 m_bit2 : 1;
		u8 m_bit3 : 1;
		u8 m_bit4 : 1;
		u8 m_bit5 : 1;
		u8 m_bit6 : 1;
		u8 m_bit7 : 1;
	};
} FlagBitfield;
#endif // TYPES_H
