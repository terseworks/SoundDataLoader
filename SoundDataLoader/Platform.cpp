//********************************************************************************
// Platform.cpp
//
// Written by: John Meschke
// Description: Platform-specific values, data types, and utilities.
//********************************************************************************

#include "Platform.h"

//********************************************************************************
// Functions
//********************************************************************************

/*
Swap bytes in 16 bit unsigned value.
*/
utype16 byteSwap16(utype16 value)
{
	utype16 result = 0;

	result = result | (value & 0x00FF) << 8;
	result = result | (value & 0xFF00) >> 8;

	return result;
}

/*
Swap bytes in 32 bit unsigned value.
*/
utype32 byteSwap32(utype32 value)
{
	utype32 result = 0;

	result = result | (value & 0x000000FF) << 24;
	result = result | (value & 0x0000FF00) << 8;
	result = result | (value & 0x00FF0000) >> 8;
	result = result | (value & 0xFF000000) >> 24;

	return result;
}

/*
Swap bytes in 64 bit unsigned value.
*/
utype64 byteSwap64(utype64 value)
{
	utype64 result = 0;

	result = result | (value & 0x00000000000000FF) << 56;
	result = result | (value & 0x000000000000FF00) << 40;
	result = result | (value & 0x0000000000FF0000) << 24;
	result = result | (value & 0x00000000FF000000) << 8;
	result = result | (value & 0x000000FF00000000) >> 8;
	result = result | (value & 0x0000FF0000000000) >> 24;
	result = result | (value & 0x00FF000000000000) >> 40;
	result = result | (value & 0xFF00000000000000) >> 56;

	return result;
}