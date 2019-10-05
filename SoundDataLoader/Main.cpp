//********************************************************************************
// Main.cpp
//
// (C) 2019 TerseWorks. All rights reserved.
// TerseWorks Public Code License (https://www.terseworks.com/licensing).
//
// Written by: John Meschke
// Description: Main program entry point.
// Dependencies: Windows, xaudio2.lib
//********************************************************************************

#include "Common.h"
#include "SoundData.h"
#include <iostream>

//********************************************************************************
// Main
//********************************************************************************

/*
Main entry function.
*/
int main()
{
	try
	{
		SoundData sound("bgm.wav");

		std::cout << "Format data size:   " << sound.getFormatDataSize() << std::endl;
		std::cout << "Data size:          " << sound.getDataSize() << std::endl;
		std::cout << "Packet count:       " << sound.getPacketCount() << std::endl;
		std::cout << "Samples per second: " << sound.getSamplesPerSecond() << std::endl;
		std::cout << "Bytes per second:   " << sound.getAverageBytesPerSecond() << std::endl;
		std::cout << "Channel count:      " << sound.getChannelCount() << std::endl;
		std::cout << "Block alignment:    " << sound.getBlockAlignment() << std::endl;
		std::cout << "Bits per sample:    " << sound.getBitsPerSample() << std::endl;
		std::cout << std::endl;
	}
	catch (const Exception &exception)
	{
		std::cout << exception.what() << std::endl;
		std::cout << std::endl;
	}

	std::cout << "Press <enter> to quit.";
	std::cin.get();

	return 0;
}