//********************************************************************************
// RiffParser.h
//
// (C) 2019 TerseWorks. All rights reserved.
// TerseWorks Public Code License | https://www.terseworks.com/licensing
//
// Written by: John Meschke
// Description: Parses a RIFF file into managable parts.
//********************************************************************************

#ifndef INCLUDE_RIFFPARSER
#define INCLUDE_RIFFPARSER

#include "Common.h"
#include <vector>

class ReadableFile;

//********************************************************************************
// RiffChunk
//********************************************************************************

struct RiffChunk
{
	char name[4];
	char type[4];
	std::size_t dataOffset;
	std::uint32_t dataSize;
};

//********************************************************************************
// RiffParser
//********************************************************************************

class RiffParser
{
	public:
		RiffParser(const ReadableFile &riffFile);
		~RiffParser();
		RiffChunk getChunk(std::size_t index) const;
		std::size_t getChunkCount() const;

	private:
		std::vector<RiffChunk> chunks;
};

#endif