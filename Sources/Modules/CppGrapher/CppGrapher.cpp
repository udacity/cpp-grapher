#include <iostream>
#include <Helpers/Filesystem.h>
#include <limits>
#include <vector>

#include "Helpers/Resources.h"
#include "Helpers/Exceptions.h"
#include "CppGrapher.h"

constexpr auto filenameArgIdx = 1;

int CppGrapher::Main( const std::vector<utf8_string> args )
{
	ValidateArgs(args);
    auto userData = ReadData(args[filenameArgIdx]);
	return EXIT_SUCCESS;
}

void CppGrapher::ValidateArgs( const std::vector<utf8_string> args ) const
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

std::vector<KalmanFilterDataPoint> CppGrapher::ReadData( const utf8_string filename ) const
{
    auto ifs = std::ifstream();
    ifs.exceptions( ifs.exceptions() | std::ios::failbit );
    ifs.open( filename.cpp_str() );
    return std::vector<KalmanFilterDataPoint> {};
}
