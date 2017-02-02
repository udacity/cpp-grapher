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
    InvalidArgumentException(utf8_string msg = u8"Invalid argument exception") : runtime_error(msg.cpp_str()) {}
};

class NonExistentFileException : public std::runtime_error
{
public:
    NonExistentFileException(utf8_string msg = u8"Non-existent file exception") : runtime_error(msg.cpp_str()) {}
};

#endif // EXCEPTIONS_H
