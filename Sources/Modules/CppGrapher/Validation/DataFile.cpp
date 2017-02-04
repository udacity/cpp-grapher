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

std::vector<KalmanFilterDataPoint> CppGrapher::ParseKalmanFilterDataFile( const utf8_string& filename ) const
{
    auto ifs = std::ifstream();
    ifs.exceptions( ifs.exceptions() | std::ios::failbit );
    try
    {
        ifs.open( filename.cpp_str());

        auto points = std::vector<KalmanFilterDataPoint> {};
        std::string line;
        while ( std::getline( ifs, line ) )
        {
            points.push_back( ParseKalmanFilterDataLine( utf8_string( line + "\n" )));
        }
        if( points.size() == 0 ) { throw NoDataFoundException(); }

        return points;
    }
    catch(std::ios_base::failure& e)
    {
        throw FileNotFoundException("File '" + filename.cpp_str() +"' not found.");
    }
}

KalmanFilterDataPoint CppGrapher::ParseKalmanFilterDataLine( const utf8_string& line ) const
{
    auto dataPoint = KalmanFilterDataPoint();
    auto idx = utf8_string::size_type( 0 );
    dataPoint.name = ParseKalmanFilterName( line, idx );
    dataPoint.x = ParseKalmanFilterPoint( line, idx );
    dataPoint.y = ParseKalmanFilterPoint( line, idx );

    return dataPoint;
}

utf8_string CppGrapher::ParseKalmanFilterName( const utf8_string& line, utf8_string::size_type& pos ) const
{
    auto tokenRange = FindNextToken( line, pos );
    return line.substr(line.get(std::get<0>(tokenRange)), line.get(std::get<1>(tokenRange)));
}

double CppGrapher::ParseKalmanFilterPoint( const utf8_string& line, utf8_string::size_type& pos ) const
{
    //If user provides a non-double value, provide a friendlier error message
    try
    {
        return std::stod( ParseKalmanFilterName( line, pos ).cpp_str());
    }
    catch ( std::invalid_argument& e )
    {
        throw BadDataException(
            u8"Non-numeric data found for Kalman Filter point.  Ensure x and y are numeric values." );
    }
}

std::tuple<utf8_string::size_type, utf8_string::size_type> CppGrapher::FindNextToken(
                                                                const utf8_string& line,
                                                                utf8_string::size_type& pos ) const
{
    auto beg = line.find_first_not_of( UnicodeLiterals::WHITESPACE, pos );
    if ( beg == utf8_string::npos ) { throw TokenNotFoundException(); }

    auto end = line.find_first_of( UnicodeLiterals::WHITESPACE, beg );
    if ( end == utf8_string::npos ) { throw TokenNotFoundException(); }

    pos = end;
    return std::make_tuple( beg, end );
}
