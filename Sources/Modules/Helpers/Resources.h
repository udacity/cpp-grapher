//
// Created by bRad on 2/1/17.
//

#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

class Msg
{
public:
    //FIXME - These resources should be utf8_string, but utf8_string's constructor is not constexpr compatible
    static constexpr auto ERROR_PREAMBLE = u8"Error: ";
    class InvalidArg
    {
    public:
        static constexpr auto EXPECTED_TWO_FOUND_NONE = u8"Expected two arguments, but none were provided.";
        static constexpr auto EXPECTED_TWO_FOUND_MORE = u8"Expected two arguments, but more were provided.";
        static constexpr auto FILENAME_CANNOT_BE_NULL = u8"Filename parameter cannot be null.";
        static constexpr auto FILENAME_ALREADY_EXISTS = u8"Filename already exists.";
        static constexpr auto INVALID_RANGE_BEG_GREATER_THAN_END =
                u8"Invalid range specified.  The range begin value must not be greater than range end value";
        static constexpr auto INVALID_RANGE_NO_SPAN   =
            u8"Invalid range specified.  There must be a difference between the range's begin and end values.";

    private:
        InvalidArg();
    };
private:
    Msg();
};

#endif //RESOURCES_H
