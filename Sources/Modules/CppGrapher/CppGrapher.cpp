#include <iostream>
#include <Helpers/Filesystem.h>
#include <limits>
#include <vector>
#include <fstream>
#include <string>
#include <Helpers/Unicode.h>

#include "Helpers/Resources.h"
#include "Helpers/Exceptions.h"
#include "Helpers/UserDefinedLiterals.h"
#include "CppGrapher.h"

constexpr auto filenameArgIdx = 1;

int CppGrapher::Main( const std::vector<utf8_string>& args )
{
	ValidateArgs(args);
    auto userData = ParseKalmanFilterDataFile(args[filenameArgIdx]);
	return EXIT_SUCCESS;
}

void CppGrapher::ValidateArgs( const std::vector<utf8_string>& args ) const
{
	//Ensure exactly one argument was provided (note: app name is always automatically provided by system)
    //args[0] is guarded because Main can be called with 0 args (eg. by driver or test)
	if( args.size() != 2 )
    {
        throw InvalidArgumentException(( args.size() > 0 ? FilenameFromPath( args[ 0 ] ) + " " : "" ) +
                                       Msg::ERROR_PREAMBLE +
                                       ( args.size() < 2
                                         ? Msg::InvalidArg::EXPECTED_ONE_FOUND_NONE
                                         : Msg::InvalidArg::EXPECTED_ONE_FOUND_MULTIPLE ));
    }
}

std::vector<KalmanFilterDataPoint> CppGrapher::ParseKalmanFilterDataFile( const utf8_string& filename ) const
{
    auto ifs = std::ifstream();
    ifs.exceptions( ifs.exceptions() | std::ios::failbit );
    ifs.open( filename.cpp_str());
    return ParseKalmanFilterDataLine( ifs );
}

std::vector<KalmanFilterDataPoint> CppGrapher::ParseKalmanFilterDataLine( std::ifstream& ifs ) const
{
    auto points = std::vector<KalmanFilterDataPoint> {};
    std::string line;

    while ( std::getline( ifs, line ) )
    {
        points.push_back( ParseKalmanFilterDataTokens( utf8_string( line + "\n" )));
    }
    if( points.size() == 0 ) { throw NoDataFoundException(); }

    return points;
}

KalmanFilterDataPoint CppGrapher::ParseKalmanFilterDataTokens( const utf8_string& line ) const
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
