#include <vector>
#include <string>
#include <cstdlib>

#include "App.h"

int main(const int argc, const char* const* argv)
{
    try
    {
        return App().main( std::vector<std::string>( argv, argv + argc ));
    }
    catch(...)
    {
        return EXIT_FAILURE;
    }
}
