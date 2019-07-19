//********************************************************************************
// RiffParser.h
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
	utype32 dataSize;
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