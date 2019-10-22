//********************************************************************************
// Platform.cpp
//
// (C) 2019 TerseWorks. All rights reserved.
// TerseWorks Public Code License | https://www.terseworks.com/licensing
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
std::uint16_t byteSwap16(std::uint16_t value)
{
	std::uint16_t result = 0;

	result = result | (value & 0x00FF) << 8;
	result = result | (value & 0xFF00) >> 8;

	return result;
}

/*
Swap bytes in 32 bit unsigned value.
*/
std::uint32_t byteSwap32(std::uint32_t value)
{
	std::uint32_t result = 0;

	result = result | (value & 0x000000FF) << 24;
	result = result | (value & 0x0000FF00) << 8;
	result = result | (value & 0x00FF0000) >> 8;
	result = result | (value & 0xFF000000) >> 24;

	return result;
}

/*
Swap bytes in 64 bit unsigned value.
*/
std::uint64_t byteSwap64(std::uint64_t value)
{
	std::uint64_t result = 0;

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