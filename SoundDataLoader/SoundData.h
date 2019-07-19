//********************************************************************************
// SoundData.h
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
		utype32 getFormatDataSize() const;
		const utype8 *getData() const;
		utype32 getDataSize() const;
		const utype32 *getPacketData() const;
		utype32 getPacketCount() const;
		utype32 getSamplesPerSecond() const;
		utype32 getAverageBytesPerSecond() const;
		utype16 getChannelCount() const;
		utype16 getBlockAlignment() const;
		utype16 getBitsPerSample() const;

	private:
		std::unique_ptr<utype8[]> formatData, data;
		std::unique_ptr<utype32[]> packetData;
		utype32 formatDataSize, dataSize, packetCount, samplesPerSecond, averageBytesPerSecond;
		utype16 channelCount, blockAlignment, bitsPerSample;
};

#endif