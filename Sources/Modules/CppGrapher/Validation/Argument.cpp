#include <iostream>
#include <vector>
#include <Helpers/Exceptions.h>
#include <Helpers/Filesystem.h>

#include "CppGrapher.h"

constexpr auto filenameArgIdx = 1;

void CppGrapher::ValidateArgs(const std::vector<utf8_string>& args) const
{
    //Ensure exactly one argument was provided (note: app name is always automatically provided by system)
    //args[0] is guarded because Main can be called with 0 args (eg. by driver or test)
    if (args.size() != 2)
    {
        throw InvalidArgumentException((args.size() > 0 ? FilenameFromPath(args[0]) + " " : "") +
                                       Msg::ERROR_PREAMBLE +
                                       (args.size() < 2
                                        ? Msg::InvalidArg::EXPECTED_ONE_FOUND_NONE
                                        : Msg::InvalidArg::EXPECTED_ONE_FOUND_MULTIPLE));
    }
}
