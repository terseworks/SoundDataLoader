//********************************************************************************
// Files.h
//
// Written by: John Meschke
// Description: Utilities to read and write the contents of a file on the system.
//********************************************************************************

#ifndef INCLUDE_FILES
#define INCLUDE_FILES

#include "Common.h"

//********************************************************************************
// ReadableFile
//********************************************************************************

class ReadableFile
{
	public:
		ReadableFile(const std::string &fileName);
		ReadableFile(const ReadableFile &readableFile) = delete;
		ReadableFile(ReadableFile &&readableFile) = delete;
		virtual ~ReadableFile();
		ReadableFile &operator=(const ReadableFile &rhs) = delete;
		ReadableFile &operator=(ReadableFile &&rhs) = delete;
		std::size_t read(void *buffer, std::size_t bufferSize) const;
		void setOffset(std::size_t offset) const;
		std::size_t getOffset() const;
		std::size_t getSize() const;

	protected:
		void *fileHandle;

		ReadableFile(const std::string &fileName, bool writeAccess, bool readShare, bool alwaysOpen);
};

//********************************************************************************
// WritableFile
//********************************************************************************

class WritableFile : public ReadableFile
{
	public:
		WritableFile(const std::string &fileName);
		WritableFile(const WritableFile &writableFile) = delete;
		WritableFile(WritableFile &&writableFile) = delete;
		~WritableFile() override;
		WritableFile &operator=(const WritableFile &rhs) = delete;
		WritableFile &operator=(WritableFile &&rhs) = delete;
		std::size_t write(const void *buffer, std::size_t bufferSize) const;
		void setEnding() const;
};

#endif