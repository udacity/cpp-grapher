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
    static constexpr auto EXPECTED_RANGE = u8"The expected range was (";
    static constexpr auto EXPECTED_RANGE_SEPARATOR = u8", ";
    static constexpr auto RECEIVED_OUT_OF_RANGE_VALUE = u8").  The received value was ";
    static constexpr auto EXPECTED_RANGE_TERMINATOR = u8".";
    class InvalidArg
    {
    public:
        static constexpr auto EXPECTED_TWO_FOUND_NONE = u8"Expected two arguments, but none were provided.";
        static constexpr auto EXPECTED_TWO_FOUND_MORE = u8"Expected two arguments, but more were provided.";
        static constexpr auto FILENAME_CANNOT_BE_NULL = u8"Filename parameter cannot be null.";
        static constexpr auto FILENAME_ALREADY_EXISTS = u8"Filename already exists.";
        static constexpr auto INVALID_RANGE_MIN_GREATER_THAN_MAX =
                u8"Invalid range specified.  The range minimum value must not be greater than range maximum value";
        static constexpr auto INVALID_RANGE_NO_SPAN   =
            u8"Invalid range specified.  There must be a difference between the range's begin and end values.";
        static constexpr auto GRAPH_MUST_BE_AT_LEAST_1_X_1 =
            u8"Invalid graph size specified.  The requested graph size must be 1x1 pixels or larger";
        static constexpr auto POINT_OUT_OF_RANGE = u8"Point specified outside the range of the graph.";
        static constexpr auto INVALID_DOUBLE_RECEIVED = u8"Invalid double-precision floating point number received.";
    private:
        InvalidArg();
    };
private:
    Msg();
};

#endif //RESOURCES_H
