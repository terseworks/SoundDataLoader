//********************************************************************************
// RiffParser.cpp
//
// (C) 2019 TerseWorks. All rights reserved.
// TerseWorks Public Code License | https://www.terseworks.com/licensing
//
// Written by: John Meschke
// Description: Parses a RIFF file into managable parts.
//********************************************************************************

#include "RiffParser.h"
#include "Files.h"

//********************************************************************************
// RiffParser
//********************************************************************************

/*
RiffParser constructor.
*/
RiffParser::RiffParser(const ReadableFile &riffFile)
{
	std::size_t originalOffset = riffFile.getOffset();

	try
	{
		riffFile.setOffset(0);

		std::size_t fileSize = riffFile.getSize();
		while (riffFile.getOffset() < fileSize)
		{
			RiffChunk chunk;

			// Chunk name (4 bytes).
			riffFile.read(&chunk.name, 4);

			// Validate the first chunk is RIFF.
			if (!chunks.size())
			{
				if (std::strncmp(chunk.name, "RIFF", 4) != 0)
				{
					throw InvalidDataException("RIFF header not found in file.");
				}
			}

			// Chunk size (32-bit big-endian).
			riffFile.read(&chunk.dataSize, 4);
			chunk.dataSize = (IS_LITTLE_ENDIAN) ? chunk.dataSize : byteSwap32(chunk.dataSize);

			if (std::strncmp(chunk.name, "RIFF", 4) == 0 || std::strncmp(chunk.name, "LIST", 4) == 0)
			{
				// Chunk type (4 bytes).
				riffFile.read(&chunk.type, 4);

				// Chunk offset.
				chunk.dataOffset = riffFile.getOffset();
			}
			else
			{
				// Chunk offset.
				chunk.dataOffset = riffFile.getOffset();

				// Advance to next chunk and account for padding byte.
				std::size_t offset = chunk.dataOffset;
				offset += chunk.dataSize;
				if (chunk.dataSize % 2) offset++;
				riffFile.setOffset(offset);
			}

			chunks.push_back(chunk);
		}
	}
	catch (const Exception &)
	{
		riffFile.setOffset(originalOffset);
		throw;
	}

	riffFile.setOffset(originalOffset);
}

/*
RiffParser destructor.
*/
RiffParser::~RiffParser()
{
}

/*
Get the chunk at the given index.
*/
RiffChunk RiffParser::getChunk(std::size_t index) const
{
	if (index >= chunks.size()) throw OutOfBoundsException("Invalid index for chunk.");

	return chunks[index];
}

/*
Get the number of chunks in the parser.
*/
std::size_t RiffParser::getChunkCount() const
{
	return chunks.size();
}