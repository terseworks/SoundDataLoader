//********************************************************************************
// Platform.h
//
// Written by: John Meschke
// Description: Platform-specific values, data types, and utilities.
//********************************************************************************

#ifndef INCLUDE_PLATFORM
#define INCLUDE_PLATFORM

#ifdef _WIN32

//********************************************************************************
// Windows / Visual C++
//********************************************************************************

#define NOMINMAX
#define STRICT
#define UNICODE
#define _UNICODE
#define WIN32_LEAN_AND_MEAN

typedef signed __int8 stype8;
typedef	unsigned __int8 utype8;
typedef signed __int16 stype16;
typedef unsigned __int16 utype16;
typedef signed __int32 stype32;
typedef unsigned __int32 utype32;
typedef signed __int64 stype64;
typedef unsigned __int64 utype64;

const bool IS_BIG_ENDIAN = false;
const bool IS_LITTLE_ENDIAN = true;

#else

//********************************************************************************
// Undefined
//********************************************************************************

#error "Must have a target platform defined."

#endif

//********************************************************************************
// Functions
//********************************************************************************

utype16 byteSwap16(utype16 value);
utype32 byteSwap32(utype32 value);
utype64 byteSwap64(utype64 value);

#endif