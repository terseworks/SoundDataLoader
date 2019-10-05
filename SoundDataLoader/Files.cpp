//********************************************************************************
// Files.cpp
//
// (C) 2019 TerseWorks. All rights reserved.
// TerseWorks Public Code License (https://www.terseworks.com/licensing).
//
// Written by: John Meschke
// Description: Utilities to read and write the contents of a file on the system.
//********************************************************************************

#include "Files.h"
#include <climits>
#include <Windows.h>

//********************************************************************************
// ReadableFile
//********************************************************************************

/*
ReadableFile constructor.
*/
ReadableFile::ReadableFile(const std::string &fileName) : ReadableFile(fileName, false, true, false)
{
}

/*
ReadableFile constructor.
*/
ReadableFile::ReadableFile(const std::string &fileName, bool writeAccess, bool readShare, bool alwaysOpen)
{
	// Convert Unicode string from UTF-8 to UTF-16.
	std::wstring fileNameWide;
	int sizeChars = MultiByteToWideChar(CP_UTF8, 0, fileName.c_str(), -1, nullptr, 0);
	if (sizeChars > 0)
	{
		std::unique_ptr<wchar_t[]> buffer(new wchar_t[sizeChars]);
		MultiByteToWideChar(CP_UTF8, 0, fileName.c_str(), -1, buffer.get(), sizeChars);
		fileNameWide = buffer.get();
	}
	else
	{
		fileNameWide = L"";
	}

	// Set the file option flags.
	DWORD accessFlags = (writeAccess) ? GENERIC_READ | GENERIC_WRITE : GENERIC_READ;
	DWORD shareFlags = (readShare) ? FILE_SHARE_READ : 0;
	DWORD creationFlags = (alwaysOpen) ? OPEN_ALWAYS : OPEN_EXISTING;

	// Create the file handle with desired read permissions.
	fileHandle = CreateFile(fileNameWide.c_str(), accessFlags, shareFlags, nullptr, creationFlags, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (fileHandle == INVALID_HANDLE_VALUE) throw ResourceFailureException("Could not create the file handle.");
}

/*
ReadableFile destructor.
[virtual]
*/
ReadableFile::~ReadableFile()
{
	CloseHandle(fileHandle);
}

/*
Read from the file to fill an existing buffer.
The current file offset is moved by the number of bytes read.
Returns the number of bytes read from file.
*/
std::size_t ReadableFile::read(void *buffer, std::size_t bufferSize) const
{
	if (!buffer) throw NullPointerException("Null buffer.");
	if (bufferSize > ULONG_MAX) throw RequestFailureException("Read size is too large. Use multiple reads instead.");

	DWORD bytesRead = 0;
	BOOL result = ReadFile(fileHandle, buffer, static_cast<DWORD>(bufferSize), &bytesRead, nullptr);
	if (!result) throw RequestFailureException("Could not read the file.");

	return static_cast<std::size_t>(bytesRead);
}

/*
Set the current file offset in bytes.
The offset may be moved beyond the end of the file.
*/
void ReadableFile::setOffset(std::size_t offset) const
{
	LARGE_INTEGER distance;
	distance.QuadPart = static_cast<LONGLONG>(offset);
	BOOL result = SetFilePointerEx(fileHandle, distance, nullptr, FILE_BEGIN);
	if (!result) throw RequestFailureException("Could not set the file offset.");
}

/*
Get the current file offset in bytes.
*/
std::size_t ReadableFile::getOffset() const
{
	LARGE_INTEGER distance, newDistance;
	distance.QuadPart = 0;
	BOOL result = SetFilePointerEx(fileHandle, distance, &newDistance, FILE_CURRENT);
	if (!result) throw RequestFailureException("Could not set the file offset.");

	return static_cast<std::size_t>(newDistance.QuadPart);
}

/*
Get the size of the file in bytes.
*/
std::size_t ReadableFile::getSize() const
{
	LARGE_INTEGER fileSize;
	BOOL result = GetFileSizeEx(fileHandle, &fileSize);
	if (!result) fileSize.QuadPart = 0;

	return static_cast<std::size_t>(fileSize.QuadPart);
}

//********************************************************************************
// WritableFile
//********************************************************************************

/*
WritableFile constructor.
*/
WritableFile::WritableFile(const std::string &fileName) : ReadableFile(fileName, true, false, true)
{
}

/*
WritableFile destructor.
[virtual]
*/
WritableFile::~WritableFile()
{
}

/*
Write to the file from an existing buffer.
The current file offset is moved by the number of bytes written.
Returns the number of bytes written to file.
*/
std::size_t WritableFile::write(const void *buffer, std::size_t bufferSize) const
{
	if (!buffer) throw NullPointerException("Null buffer.");
	if (bufferSize > ULONG_MAX) throw RequestFailureException("Write size is too large. Use multiple writes instead.");

	DWORD bytesWritten = 0;
	BOOL result = WriteFile(fileHandle, buffer, static_cast<DWORD>(bufferSize), &bytesWritten, nullptr);
	if (!result) throw RequestFailureException("Could not write to the file.");

	return static_cast<std::size_t>(bytesWritten);
}

/*
Set the ending of the file at the current file offset.
*/
void WritableFile::setEnding() const
{
	BOOL result = SetEndOfFile(fileHandle);
	if (!result) throw RequestFailureException("Could not set the end of the file.");
}