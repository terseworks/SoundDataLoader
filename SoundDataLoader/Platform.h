//********************************************************************************
// Platform.h
//
// Written by: John Meschke
// Description: Platform-specific values, data types, and utilities.
//********************************************************************************

#ifndef INCLUDE_PLATFORM
#define INCLUDE_PLATFORM

#include <cstdint>

#ifdef _WIN32

//********************************************************************************
// Windows / Visual C++
//********************************************************************************

#define NOMINMAX
#define STRICT
#define UNICODE
#define _UNICODE
#define WIN32_LEAN_AND_MEAN

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

std::uint16_t byteSwap16(std::uint16_t value);
std::uint32_t byteSwap32(std::uint32_t value);
std::uint64_t byteSwap64(std::uint64_t value);

#endif