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
        static constexpr auto EXPECTED_TWO_FOUND_NONE = u8"Expected two arguments, but none were provided.";
        static constexpr auto EXPECTED_TWO_FOUND_MORE = u8"Expected two arguments, but more were provided.";
        static constexpr auto FILENAME_CANNOT_BE_NULL = u8"Filename parameter cannot be null.";
        static constexpr auto FILENAME_ALREADY_EXISTS = u8"Filename already exists.";

    private:
        InvalidArg();
    };
private:
    Msg();
};

#endif //RESOURCES_H
