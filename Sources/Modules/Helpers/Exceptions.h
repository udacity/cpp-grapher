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

class BadDataException : public std::runtime_error
{
public:
    BadDataException(utf8_string msg = u8"Bad data found") : runtime_error(msg.cpp_str()) {}
};

class FileNotFoundException : public std::runtime_error
{
public:
    FileNotFoundException(utf8_string msg = u8"File not found") : runtime_error(msg.cpp_str()) {}
};

class InvalidRangeException : public std::runtime_error
{
public:
    InvalidRangeException(utf8_string msg = u8"Invalid range specified") : runtime_error(msg.cpp_str()) {}
};

class InvalidGraphSizeException : public std::runtime_error
{
public:
    InvalidGraphSizeException(utf8_string msg = u8"Invalid graph size requested") : runtime_error(msg.cpp_str()) {}
};

class PointOutOfRangeException : public std::runtime_error
{
public:
    PointOutOfRangeException(utf8_string msg = u8"Point requested outside the range of the graph") :
                                                                                    runtime_error(msg.cpp_str()) {}
};

#endif // EXCEPTIONS_H
