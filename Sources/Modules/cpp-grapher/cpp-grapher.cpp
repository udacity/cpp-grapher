#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

#include "CppGrapher.h"

int main(const int argc, const char* const* argv)
{
    try
    {
        return CppGrapher().Main( std::vector<std::string>( argv, argv + argc ));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
