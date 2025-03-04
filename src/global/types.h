#ifndef TYPES_H
#define TYPES_H

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>
using std::list;
using std::map;
using std::multiset;
using std::pair;
using std::set;
using std::vector;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long int u64;
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long int i64;
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

typedef void* HCursor;
typedef void* HWindow;
typedef void* HInstance;
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
