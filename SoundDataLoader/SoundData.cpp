//********************************************************************************
// SoundData.cpp
//
// Written by: John Meschke
// Description: Container for sound data used by one or more sound voices.
//              Supports WAVE and XWMA formats.
//********************************************************************************

#include "SoundData.h"
#include "Files.h"
#include "RiffParser.h"
#include <XAudio2.h>

//********************************************************************************
// SoundData
//********************************************************************************

/*
SoundData constructor.
*/
SoundData::SoundData(const std::string &fileName) : formatDataSize(0), dataSize(0), packetCount(0), samplesPerSecond(0), averageBytesPerSecond(0), channelCount(0), blockAlignment(0), bitsPerSample(0)
{
	// File data information.
	bool foundRiff = false;
	bool foundFmt = false;
	bool foundData = false;
	bool foundDpds = false;
	std::uint32_t fileType = 0;

	ReadableFile soundFile(fileName);
	RiffParser riffParser(soundFile);

	for (std::size_t i = 0; i < riffParser.getChunkCount(); i++)
	{
		RiffChunk chunk = riffParser.getChunk(i);

		if (std::strncmp(chunk.name, "RIFF", 4) == 0 && !foundRiff)
		{
			// RIFF (all types).
			foundRiff = true;
			if (std::strncmp(chunk.type, "WAVE", 4) == 0)
			{
				// WAVE.
				fileType = 'WAVE';
			}
			else if (std::strncmp(chunk.type, "XWMA", 4) == 0)
			{
				// XWMA.
				fileType = 'XWMA';
			}
		}
		else if (std::strncmp(chunk.name, "fmt ", 4) == 0 && !foundFmt)
		{
			// fmt (all types).
			foundFmt = true;
			if (!chunk.dataSize) throw InvalidDataException("Chunk format has 0 size.");

			switch (chunk.dataSize)
			{
				case sizeof(ADPCMWAVEFORMAT):
				case sizeof(PCMWAVEFORMAT):
				case sizeof(WAVEFORMATEX):
				case sizeof(WAVEFORMATEXTENSIBLE):
					formatData.reset(new std::uint8_t[chunk.dataSize]);
					formatDataSize = chunk.dataSize;
					soundFile.setOffset(chunk.dataOffset);
					soundFile.read(formatData.get(), chunk.dataSize);
					break;
			}

			ADPCMWAVEFORMAT *adpcmWaveFormat;
			PCMWAVEFORMAT *pcmWaveFormat;
			WAVEFORMATEX *waveFormatEx;
			WAVEFORMATEXTENSIBLE *waveFormatExtensible;
			switch (chunk.dataSize)
			{
				case sizeof(ADPCMWAVEFORMAT):
					adpcmWaveFormat = reinterpret_cast<ADPCMWAVEFORMAT *>(formatData.get());
					if (IS_BIG_ENDIAN)
					{
						adpcmWaveFormat->wfx.wFormatTag = byteSwap16(adpcmWaveFormat->wfx.wFormatTag);
						adpcmWaveFormat->wfx.nChannels = byteSwap16(adpcmWaveFormat->wfx.nChannels);
						adpcmWaveFormat->wfx.nSamplesPerSec = byteSwap32(adpcmWaveFormat->wfx.nSamplesPerSec);
						adpcmWaveFormat->wfx.nAvgBytesPerSec = byteSwap32(adpcmWaveFormat->wfx.nAvgBytesPerSec);
						adpcmWaveFormat->wfx.nBlockAlign = byteSwap16(adpcmWaveFormat->wfx.nBlockAlign);
						adpcmWaveFormat->wfx.wBitsPerSample = byteSwap16(adpcmWaveFormat->wfx.wBitsPerSample);
						adpcmWaveFormat->wfx.cbSize = byteSwap16(adpcmWaveFormat->wfx.cbSize);
						adpcmWaveFormat->wNumCoef = byteSwap16(adpcmWaveFormat->wNumCoef);
						adpcmWaveFormat->wSamplesPerBlock = byteSwap16(adpcmWaveFormat->wSamplesPerBlock);
						adpcmWaveFormat->aCoef->iCoef1 = byteSwap16(adpcmWaveFormat->aCoef->iCoef1);
						adpcmWaveFormat->aCoef->iCoef2 = byteSwap16(adpcmWaveFormat->aCoef->iCoef2);
					}
					samplesPerSecond = adpcmWaveFormat->wfx.nSamplesPerSec;
					averageBytesPerSecond = adpcmWaveFormat->wfx.nAvgBytesPerSec;
					channelCount = adpcmWaveFormat->wfx.nChannels;
					blockAlignment = adpcmWaveFormat->wfx.nBlockAlign;
					bitsPerSample = adpcmWaveFormat->wfx.wBitsPerSample;
					break;

				case sizeof(PCMWAVEFORMAT):
					pcmWaveFormat = reinterpret_cast<PCMWAVEFORMAT *>(formatData.get());
					if (IS_BIG_ENDIAN)
					{
						pcmWaveFormat->wf.wFormatTag = byteSwap16(pcmWaveFormat->wf.wFormatTag);
						pcmWaveFormat->wf.nChannels = byteSwap16(pcmWaveFormat->wf.nChannels);
						pcmWaveFormat->wf.nSamplesPerSec = byteSwap32(pcmWaveFormat->wf.nSamplesPerSec);
						pcmWaveFormat->wf.nAvgBytesPerSec = byteSwap32(pcmWaveFormat->wf.nAvgBytesPerSec);
						pcmWaveFormat->wf.nBlockAlign = byteSwap16(pcmWaveFormat->wf.nBlockAlign);
						pcmWaveFormat->wBitsPerSample = byteSwap16(pcmWaveFormat->wBitsPerSample);
					}
					samplesPerSecond = pcmWaveFormat->wf.nSamplesPerSec;
					averageBytesPerSecond = pcmWaveFormat->wf.nAvgBytesPerSec;
					channelCount = pcmWaveFormat->wf.nChannels;
					blockAlignment = pcmWaveFormat->wf.nBlockAlign;
					bitsPerSample = pcmWaveFormat->wBitsPerSample;
					break;

				case sizeof(WAVEFORMATEX):
					waveFormatEx = reinterpret_cast<WAVEFORMATEX *>(formatData.get());
					if (IS_BIG_ENDIAN)
					{
						waveFormatEx->wFormatTag = byteSwap16(waveFormatEx->wFormatTag);
						waveFormatEx->nChannels = byteSwap16(waveFormatEx->nChannels);
						waveFormatEx->nSamplesPerSec = byteSwap32(waveFormatEx->nSamplesPerSec);
						waveFormatEx->nAvgBytesPerSec = byteSwap32(waveFormatEx->nAvgBytesPerSec);
						waveFormatEx->nBlockAlign = byteSwap16(waveFormatEx->nBlockAlign);
						waveFormatEx->wBitsPerSample = byteSwap16(waveFormatEx->wBitsPerSample);
						waveFormatEx->cbSize = byteSwap16(waveFormatEx->cbSize);
					}
					samplesPerSecond = waveFormatEx->nSamplesPerSec;
					averageBytesPerSecond = waveFormatEx->nAvgBytesPerSec;
					channelCount = waveFormatEx->nChannels;
					blockAlignment = waveFormatEx->nBlockAlign;
					bitsPerSample = waveFormatEx->wBitsPerSample;
					break;

				case sizeof(WAVEFORMATEXTENSIBLE):
					waveFormatExtensible = reinterpret_cast<WAVEFORMATEXTENSIBLE *>(formatData.get());
					if (IS_BIG_ENDIAN)
					{
						waveFormatExtensible->Format.wFormatTag = byteSwap16(waveFormatExtensible->Format.wFormatTag);
						waveFormatExtensible->Format.nChannels = byteSwap16(waveFormatExtensible->Format.nChannels);
						waveFormatExtensible->Format.nSamplesPerSec = byteSwap32(waveFormatExtensible->Format.nSamplesPerSec);
						waveFormatExtensible->Format.nAvgBytesPerSec = byteSwap32(waveFormatExtensible->Format.nAvgBytesPerSec);
						waveFormatExtensible->Format.nBlockAlign = byteSwap16(waveFormatExtensible->Format.nBlockAlign);
						waveFormatExtensible->Format.wBitsPerSample = byteSwap16(waveFormatExtensible->Format.wBitsPerSample);
						waveFormatExtensible->Format.cbSize = byteSwap16(waveFormatExtensible->Format.cbSize);
						waveFormatExtensible->dwChannelMask = byteSwap32(waveFormatExtensible->dwChannelMask);
						waveFormatExtensible->Samples.wReserved = byteSwap16(waveFormatExtensible->Samples.wReserved);
						waveFormatExtensible->SubFormat.Data1 = byteSwap32(waveFormatExtensible->SubFormat.Data1);
						waveFormatExtensible->SubFormat.Data2 = byteSwap16(waveFormatExtensible->SubFormat.Data2);
						waveFormatExtensible->SubFormat.Data3 = byteSwap16(waveFormatExtensible->SubFormat.Data3);
					}
					samplesPerSecond = waveFormatExtensible->Format.nSamplesPerSec;
					averageBytesPerSecond = waveFormatExtensible->Format.nAvgBytesPerSec;
					channelCount = waveFormatExtensible->Format.nChannels;
					blockAlignment = waveFormatExtensible->Format.nBlockAlign;
					bitsPerSample = waveFormatExtensible->Format.wBitsPerSample;
					break;
			}
		}
		else if (std::strncmp(chunk.name, "data", 4) == 0 && !foundData)
		{
			// data (all types).
			foundData = true;
			if (!chunk.dataSize) throw InvalidDataException("Chunk data has 0 size.");

			data.reset(new std::uint8_t[chunk.dataSize]);
			dataSize = chunk.dataSize;
			soundFile.setOffset(chunk.dataOffset);
			soundFile.read(data.get(), chunk.dataSize);
		}
		else if (std::strncmp(chunk.name, "dpds", 4) == 0 && !foundDpds)
		{
			// dpds (xWMA only).
			foundDpds = true;
			packetCount = chunk.dataSize / 4;
			if (!packetCount) throw InvalidDataException("Chunk packet count is 0.");

			packetData.reset(new std::uint32_t[packetCount]);
			soundFile.setOffset(chunk.dataOffset);
			soundFile.read(packetData.get(), chunk.dataSize);
			if (IS_BIG_ENDIAN)
			{
				for (std::uint32_t i = 0; i < packetCount; i++)
				{
					std::uint32_t packet = packetData[i];
					packetData[i] = byteSwap32(packet);
				}
			}
		}
	}

	// Validate necessary data was found.
	if (!fileType || !formatData.get() || !data.get() || (fileType == 'XWMA' && !packetData.get()) || !samplesPerSecond || !averageBytesPerSecond || !channelCount || !blockAlignment)
	{
		throw InvalidDataException("Missing information in sound data.");
	}

	// Validate data is correct.
	if (dataSize % blockAlignment || (fileType == 'XWMA' && packetCount != dataSize / blockAlignment) || channelCount < 1 || channelCount > 2)
	{
		throw InvalidDataException("Malformed information in sound data.");
	}
}

/*
SoundData destructor.
*/
SoundData::~SoundData()
{
}

/*
Get a constant pointer to the format data.
*/
const void *SoundData::getFormatData() const
{
	return formatData.get();
}

/*
Get the format data size in bytes.
*/
std::uint32_t SoundData::getFormatDataSize() const
{
	return formatDataSize;
}

/*
Get a constant pointer to the data.
*/
const std::uint8_t *SoundData::getData() const
{
	return data.get();
}

/*
Get the data size in bytes.
*/
std::uint32_t SoundData::getDataSize() const
{
	return dataSize;
}

/*
Get a constant pointer to the packet data.
May be null if not in XWMA format.
*/
const std::uint32_t *SoundData::getPacketData() const
{
	return packetData.get();
}

/*
Get the packet count.
May be 0 if not in XWMA format.
*/
std::uint32_t SoundData::getPacketCount() const
{
	return packetCount;
}

/*
Get the number of samples per second.
*/
std::uint32_t SoundData::getSamplesPerSecond() const
{
	return samplesPerSecond;
}

/*
Get the average bytes played per second.
*/
std::uint32_t SoundData::getAverageBytesPerSecond() const
{
	return averageBytesPerSecond;
}

/*
Get the number of channels.
1 channel for mono, 2 for stereo.
*/
std::uint16_t SoundData::getChannelCount() const
{
	return channelCount;
}

/*
Get the block alignment in bytes.
The data size is evenly divisible by this value.
*/
std::uint16_t SoundData::getBlockAlignment() const
{
	return blockAlignment;
}

/*
Get the number of bits per sample.
May be 0 for some compressed formats.
*/
std::uint16_t SoundData::getBitsPerSample() const
{
	return bitsPerSample;
}