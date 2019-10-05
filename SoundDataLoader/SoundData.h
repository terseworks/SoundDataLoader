//********************************************************************************
// SoundData.h
//
// (C) 2019 TerseWorks. All rights reserved.
// TerseWorks Public Code License (https://www.terseworks.com/licensing).
//
// Written by: John Meschke
// Description: Container for sound data used by one or more sound voices.
//              Supports WAVE and XWMA formats.
//********************************************************************************

#ifndef INCLUDE_SOUNDDATA
#define INCLUDE_SOUNDDATA

#include "Common.h"

//********************************************************************************
// SoundData
//********************************************************************************

class SoundData
{
	public:
		SoundData(const std::string &fileName);
		SoundData(const SoundData &soundData) = delete;
		SoundData(SoundData &&soundData) = delete;
		~SoundData();
		SoundData &operator=(const SoundData &rhs) = delete;
		SoundData &operator=(SoundData &&rhs) = delete;
		const void *getFormatData() const;
		std::uint32_t getFormatDataSize() const;
		const std::uint8_t *getData() const;
		std::uint32_t getDataSize() const;
		const std::uint32_t *getPacketData() const;
		std::uint32_t getPacketCount() const;
		std::uint32_t getSamplesPerSecond() const;
		std::uint32_t getAverageBytesPerSecond() const;
		std::uint16_t getChannelCount() const;
		std::uint16_t getBlockAlignment() const;
		std::uint16_t getBitsPerSample() const;

	private:
		std::unique_ptr<std::uint8_t[]> formatData, data;
		std::unique_ptr<std::uint32_t[]> packetData;
		std::uint32_t formatDataSize, dataSize, packetCount, samplesPerSecond, averageBytesPerSecond;
		std::uint16_t channelCount, blockAlignment, bitsPerSample;
};

#endif