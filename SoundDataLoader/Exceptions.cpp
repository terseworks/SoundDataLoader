//********************************************************************************
// Exceptions.cpp
//
// (C) 2019 TerseWorks. All rights reserved.
// TerseWorks Public Code License (https://www.terseworks.com/licensing).
//
// Written by: John Meschke
// Description: Exception classes.
//********************************************************************************

#include "Exceptions.h"

//********************************************************************************
// Exception
//********************************************************************************

/*
Exception constructor.
*/
Exception::Exception() : std::runtime_error("")
{
}

/*
Exception constructor.
*/
Exception::Exception(const std::string &what) : std::runtime_error(what)
{
}

/*
Exception destructor.
[virtual]
*/
Exception::~Exception()
{
}

/*
Get the name of the exception as a string.
[virtual]
*/
const char *Exception::name() const noexcept
{
	return "Exception";
}

//********************************************************************************
// InvalidArgumentException
//********************************************************************************

/*
InvalidArgumentException constructor.
*/
InvalidArgumentException::InvalidArgumentException()
{
}

/*
InvalidArgumentException constructor.
*/
InvalidArgumentException::InvalidArgumentException(const std::string &what) : Exception(what)
{
}

/*
InvalidArgumentException destructor.
[virtual]
*/
InvalidArgumentException::~InvalidArgumentException()
{
}

/*
Get the name of the exception as a string.
[virtual]
*/
const char *InvalidArgumentException::name() const noexcept
{
	return "InvalidArgumentException";
}

//********************************************************************************
// InvalidCallException
//********************************************************************************

/*
InvalidCallException constructor.
*/
InvalidCallException::InvalidCallException()
{
}

/*
InvalidCallException constructor.
*/
InvalidCallException::InvalidCallException(const std::string &what) : Exception(what)
{
}

/*
InvalidCallException destructor.
[virtual]
*/
InvalidCallException::~InvalidCallException()
{
}

/*
Get the name of the exception as a string.
[virtual]
*/
const char *InvalidCallException::name() const noexcept
{
	return "InvalidCallException";
}

//********************************************************************************
// NullPointerException
//********************************************************************************

/*
NullPointerException constructor.
*/
NullPointerException::NullPointerException()
{
}

/*
NullPointerException constructor.
*/
NullPointerException::NullPointerException(const std::string &what) : Exception(what)
{
}

/*
NullPointerException destructor.
[virtual]
*/
NullPointerException::~NullPointerException()
{
}

/*
Get the name of the exception as a string.
[virtual]
*/
const char *NullPointerException::name() const noexcept
{
	return "NullPointerException";
}

//********************************************************************************
// OutOfBoundsException
//********************************************************************************

/*
OutOfBoundsException constructor.
*/
OutOfBoundsException::OutOfBoundsException()
{
}

/*
OutOfBoundsException constructor.
*/
OutOfBoundsException::OutOfBoundsException(const std::string &what) : Exception(what)
{
}

/*
OutOfBoundsException destructor.
[virtual]
*/
OutOfBoundsException::~OutOfBoundsException()
{
}

/*
Get the name of the exception as a string.
[virtual]
*/
const char *OutOfBoundsException::name() const noexcept
{
	return "OutOfBoundsException";
}

//********************************************************************************
// InvalidDataException
//********************************************************************************

/*
InvalidDataException constructor.
*/
InvalidDataException::InvalidDataException()
{
}

/*
InvalidDataException constructor.
*/
InvalidDataException::InvalidDataException(const std::string &what) : Exception(what)
{
}

/*
InvalidDataException destructor.
[virtual]
*/
InvalidDataException::~InvalidDataException()
{
}

/*
Get the name of the exception as a string.
[virtual]
*/
const char *InvalidDataException::name() const noexcept
{
	return "InvalidDataException";
}

//********************************************************************************
// RequestFailureException
//********************************************************************************

/*
RequestFailureException constructor.
*/
RequestFailureException::RequestFailureException()
{
}

/*
RequestFailureException constructor.
*/
RequestFailureException::RequestFailureException(const std::string &what) : Exception(what)
{
}

/*
InvalidDataException destructor.
[virtual]
*/
RequestFailureException::~RequestFailureException()
{
}

/*
Get the name of the exception as a string.
[virtual]
*/
const char *RequestFailureException::name() const noexcept
{
	return "RequestFailureException";
}

//********************************************************************************
// ResourceFailureException
//********************************************************************************

/*
ResourceFailureException constructor.
*/
ResourceFailureException::ResourceFailureException()
{
}

/*
ResourceFailureException constructor.
*/
ResourceFailureException::ResourceFailureException(const std::string &what) : Exception(what)
{
}

/*
ResourceFailureException destructor.
[virtual]
*/
ResourceFailureException::~ResourceFailureException()
{
}

/*
Get the name of the exception as a string.
[virtual]
*/
const char *ResourceFailureException::name() const noexcept
{
	return "ResourceFailureException";
}

//********************************************************************************
// UnsupportedException
//********************************************************************************

/*
UnsupportedException constructor.
*/
UnsupportedException::UnsupportedException()
{
}

/*
UnsupportedException constructor.
*/
UnsupportedException::UnsupportedException(const std::string &what) : Exception(what)
{
}

/*
UnsupportedException destructor.
[virtual]
*/
UnsupportedException::~UnsupportedException()
{
}

/*
Get the name of the exception as a string.
[virtual]
*/
const char *UnsupportedException::name() const noexcept
{
	return "UnsupportedException";
}