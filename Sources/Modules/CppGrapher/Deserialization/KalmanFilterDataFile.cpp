#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <string>

#include "Helpers/Unicode.h"
#include "Helpers/Filesystem.h"
#include "Helpers/Resources.h"
#include "Helpers/Exceptions.h"
#include "Helpers/UserDefinedLiterals.h"
#include "CppGrapher.h"

std::vector<KalmanFilterDataPoint> CppGrapher::DeserializeDataPoints(const utf8_string& filename) const
{
    auto ifs = std::ifstream();
    ifs.exceptions(ifs.exceptions() | std::ios::failbit);
    try
    {
        ifs.open(filename.cpp_str());

        auto points = std::vector<KalmanFilterDataPoint> {};
        std::string line;
        while (std::getline(ifs, line))
        {
            points.push_back(DeserializeDataLine(utf8_string(line + "\n")));
        }
        if (points.size() == 0) { throw NoDataFoundException(); }

        return points;
    }
    catch (std::ios_base::failure& e)
    {
        throw FileNotFoundException("File '" + filename.cpp_str() + "' not found.");
    }
}

KalmanFilterDataPoint CppGrapher::DeserializeDataLine(const utf8_string& line) const
{
    auto dataPoint = KalmanFilterDataPoint();
    auto idx = utf8_string::size_type(0);
    dataPoint.name = DeserializeDataName(line, idx);
    dataPoint.coord.first = DeserializeDataPoint(line, idx);
    dataPoint.coord.second = DeserializeDataPoint(line, idx);

    return dataPoint;
}

utf8_string CppGrapher::DeserializeDataName(const utf8_string& line, utf8_string::size_type& pos) const
{
    enum Range : size_t { BEG = 0, END = 1 };

    auto tokenRange = LocateNextToken(line, pos);
    return line.substr(line.get(std::get<Range::BEG>(tokenRange)), line.get(std::get<Range::END>(tokenRange)));
}

double CppGrapher::DeserializeDataPoint(const utf8_string& line, utf8_string::size_type& pos) const
{
    //If user provides a non-double value, provide a friendlier error message than the C++ SL provides
    try
    {
        return std::stod(DeserializeDataName(line, pos).cpp_str());
    }
    catch (std::invalid_argument& e)
    {
        throw BadDataException(
            u8"Non-numeric data found for Kalman Filter point.  Ensure x and y are numeric values.");
    }
}

std::tuple<utf8_string::size_type, utf8_string::size_type> CppGrapher::LocateNextToken(
    const utf8_string& line,
    utf8_string::size_type& pos) const
{
    auto beg = line.find_first_not_of(UnicodeLiterals::WHITESPACE, pos);
    if (beg == utf8_string::npos) { throw TokenNotFoundException(); }

    auto end = line.find_first_of(UnicodeLiterals::WHITESPACE, beg);
    if (end == utf8_string::npos) { throw TokenNotFoundException(); }

    pos = end;
    return std::make_tuple(beg, end);
}
