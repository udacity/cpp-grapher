#include <regex>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Filesystem.h"
#include "Magick++.h"

SCENARIO("Graphics tests")
{
    GIVEN("an app instance")
    {
        auto app = CppGrapher();

        WHEN("fed a data file rendering a single pixel at the origin (0, 0)")
        {
            auto filename = utf8_string( u8"cpp-grapher-test.one_pixel" );
            auto fileContents = u8"pixel_one, 0 0";
            auto fs = TemporaryFileStream( filename, fileContents );
            auto args = std::vector<utf8_string> { u8"cpp-grapher_via-test-runner", filename };

            //TODO suppress stdout output
            app.Main( args );

            THEN("a bitmap should be rendered with one pixel set at (0, 0)")
            {
                //TODO read image file
                //generate 0-pixel image file
                //diff images
                //assert (count non-black pixels == 1)
            }
        }
    }
}

