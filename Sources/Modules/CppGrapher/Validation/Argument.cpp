#include <iostream>
#include <vector>
#include <Helpers/Exceptions.h>
#include <Helpers/Filesystem.h>

#include "CppGrapher.h"

void CppGrapher::ValidateArgs(const std::vector<utf8_string>& args) const
{
    //Ensure exactly one argument was provided (note: app name is always automatically provided by system)
    //args[0] is guarded because Main can be called with 0 args (eg. by driver or test)
    if (args.size() != ArgsIndexNames::REQUIRED_ARGUMENT_COUNT)
    {
        throw InvalidArgumentException((args.size() > 0
                                            ? FilenameFromPath(args[ArgsIndexNames::APPLICATION_FILENAME]) + " "
                                            : "") +
                                       Msg::ERROR_PREAMBLE +
                                       (args.size() < ArgsIndexNames::REQUIRED_ARGUMENT_COUNT
                                            ? Msg::InvalidArg::EXPECTED_TWO_FOUND_NONE
                                            : Msg::InvalidArg::EXPECTED_TWO_FOUND_MORE));
    }
}
