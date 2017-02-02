//
// Created by bRad on 2/1/17.
//

#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

class Msg
{
public:
    static constexpr auto ERROR_PREAMBLE = "Error: ";
    class InvalidArg
    {
    public:
        static constexpr auto EXPECTED_ONE_FOUND_NONE = "Expected one argument, but none were provided.";
        static constexpr auto EXPECTED_ONE_FOUND_MULTIPLE = "Expected one argument, but multiple were provided.";
    private:
        InvalidArg();
    };

private:
    Msg();
};

#endif //RESOURCES_H
