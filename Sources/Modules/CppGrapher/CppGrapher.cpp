#include <iostream>
#include <Helpers/Filesystem.h>
#include <limits>
#include <vector>

#include "Helpers/Resources.h"
#include "Helpers/Exceptions.h"
#include "CppGrapher.h"

std::string CppGrapher::Greet() const
{
	return "Hello " + std::to_string(std::numeric_limits<size_t>::digits) + "-bit World!\n";
}

int CppGrapher::Main( const std::vector<std::string> args )
{
	ValidateArgs(args);

	auto hello = CppGrapher();
	return EXIT_SUCCESS;
}

void CppGrapher::ValidateArgs( const std::vector<std::string> args )
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
