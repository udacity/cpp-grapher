#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class NotImplementedException : public std::runtime_error
{
public:
    NotImplementedException() : runtime_error("Method not implemented") {}
};

class InvalidArgumentException : public std::runtime_error
{
public:
    InvalidArgumentException(std::string msg = "Invalid argument exception") : runtime_error(msg) {}
};

#endif // EXCEPTIONS_H
