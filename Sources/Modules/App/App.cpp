#include <iostream>

#include "App.h"
#include "Lib.h"

//**********************************************************************************************************************
// Sample code illustration how to build an application's functionality into a library, which may be linked with any
// number of drivers (test harness and application driver examples provided).  For brevity, dynamic linking to the
// library is not shown in this sample code.
//
// While this concept is obviously overkill for a simple "Hello, world!" app, this template is designed to accommodate
// projects of various scope.  For larger projects, multiple highly-cohesive libraries would be created, instead of
// just one.
//
// Build the Test target to (statically) link against the library and execute tests against it.
// Build the App target to have the Hello library statically linked into an executable application suitable for
// release.  Remember to use the --release flag for an optimized binary image.
//**********************************************************************************************************************

int App::main( const std::vector<std::string> args )
{
    auto hello = Hello();
    std::cout << hello.Greet() << std::endl;
    return EXIT_SUCCESS;
}
