#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <Helpers/Filesystem.h>

#include "CppGrapher.h"

int main(const int argc, const char* const* argv)
{
    auto args = std::vector<utf8_string> {};
    args.reserve(argc);

    //Convert args to UTF-8 & place in a safe container (see docs for CppGrapher::Main() in CppGrapher.h for more info)
    std::transform(argv,
                   argv + argc,
                   std::back_inserter(args),
                   [](std::string arg)
                   { return utf8_string(arg); });

    //Run app, reporting top-level exceptions (if any) to stderr
    try
    {
        return CppGrapher().Main(args);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
