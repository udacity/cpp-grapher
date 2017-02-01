#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class NotImplementedException : public std::runtime_error
{
public:
    NotImplementedException() : runtime_error("Method not implemented") {}
};

#endif // EXCEPTIONS_H
