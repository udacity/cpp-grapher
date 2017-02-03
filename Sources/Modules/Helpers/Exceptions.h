#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "tinyutf8.h"

class NotImplementedException : public std::runtime_error
{
public:
    NotImplementedException() : runtime_error("Method not implemented") {}
};

class InvalidArgumentException : public std::runtime_error
{
public:
    InvalidArgumentException(utf8_string msg = u8"Invalid argument received") : runtime_error(msg.cpp_str()) {}
};

class TokenNotFoundException : public std::runtime_error
{
public:
    TokenNotFoundException(utf8_string msg = u8"Expected token not found") : runtime_error(msg.cpp_str()) {}
};

class NoDataFoundException : public std::runtime_error
{
public:
    NoDataFoundException(utf8_string msg = u8"No data found") : runtime_error(msg.cpp_str()) {}
};

#endif // EXCEPTIONS_H
