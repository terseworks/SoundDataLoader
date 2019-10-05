//********************************************************************************
// Exceptions.h
//
// (C) 2019 TerseWorks. All rights reserved.
// TerseWorks Public Code License (https://www.terseworks.com/licensing).
//
// Written by: John Meschke
// Description: Exception classes.
//********************************************************************************

#ifndef INCLUDE_EXCEPTIONS
#define INCLUDE_EXCEPTIONS

#include <stdexcept>
#include <string>

//********************************************************************************
// Exception
//********************************************************************************

class Exception : public std::runtime_error
{
	public:
		Exception();
		Exception(const std::string &what);
		virtual ~Exception();
		virtual const char *name() const noexcept;
};

//********************************************************************************
// InvalidArgumentException
//********************************************************************************

class InvalidArgumentException : public Exception
{
	public:
		InvalidArgumentException();
		InvalidArgumentException(const std::string &what);
		~InvalidArgumentException() override;
		const char *name() const noexcept override;
};

//********************************************************************************
// InvalidCallException
//********************************************************************************

class InvalidCallException : public Exception
{
	public:
		InvalidCallException();
		InvalidCallException(const std::string &what);
		~InvalidCallException() override;
		const char *name() const noexcept override;
};

//********************************************************************************
// NullPointerException
//********************************************************************************

class NullPointerException : public Exception
{
	public:
		NullPointerException();
		NullPointerException(const std::string &what);
		~NullPointerException() override;
		const char *name() const noexcept override;
};

//********************************************************************************
// OutOfBoundsException
//********************************************************************************

class OutOfBoundsException : public Exception
{
	public:
		OutOfBoundsException();
		OutOfBoundsException(const std::string &what);
		~OutOfBoundsException() override;
		const char *name() const noexcept override;
};

//********************************************************************************
// InvalidDataException
//********************************************************************************

class InvalidDataException : public Exception
{
	public:
		InvalidDataException();
		InvalidDataException(const std::string &what);
		~InvalidDataException() override;
		const char *name() const noexcept override;
};

//********************************************************************************
// RequestFailureException
//********************************************************************************

class RequestFailureException : public Exception
{
	public:
		RequestFailureException();
		RequestFailureException(const std::string &what);
		~RequestFailureException() override;
		const char *name() const noexcept override;
};

//********************************************************************************
// ResourceFailureException
//********************************************************************************

class ResourceFailureException : public Exception
{
	public:
		ResourceFailureException();
		ResourceFailureException(const std::string &what);
		~ResourceFailureException() override;
		const char *name() const noexcept override;
};

//********************************************************************************
// UnsupportedException
//********************************************************************************

class UnsupportedException : public Exception
{
	public:
		UnsupportedException();
		UnsupportedException(const std::string &what);
		~UnsupportedException() override;
		const char *name() const noexcept override;
};

#endif