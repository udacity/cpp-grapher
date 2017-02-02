#include <regex>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Exceptions.h"
#include "Helpers/Filesystem.h"

SCENARIO("Parsing command line arguments")
{
    GIVEN( "an app instance" )
    {
        auto app = CppGrapher();

        WHEN( "two arguments are supplied" )
        {
            auto args = std::vector<utf8_string> { "sample-arg1", "sample-arg2" };

            THEN( "it should not throw an InvalidArgumentException" )
            {
                try
                {
                    app.Main( args );
                }
                catch ( std::exception& e )
                {
                    REQUIRE_THROWS_AS( throw, std::ios_base::failure );
                }
            }
        }

        WHEN( "no arguments are supplied" )
        {
            auto args = std::vector<utf8_string> {};

            THEN( "it should throw an InvalidArgumentException" )
            {
                REQUIRE_THROWS_AS( app.Main( args ), InvalidArgumentException );
            }
        }

        AND_WHEN( "one argument is supplied" )
        {
            auto args = std::vector<utf8_string> { "sample-arg1" };

            THEN( "it should throw an InvalidArgumentsException" )
            {
                REQUIRE_THROWS_AS( app.Main( args ), InvalidArgumentException );
            }
        }

        AND_WHEN( "three arguments are supplied" )
        {
            auto args = std::vector<utf8_string> { "sample-arg1", "sample-arg2", "sample-arg3" };

            THEN( "it should throw an InvalidArgumentsException" )
            {
                REQUIRE_THROWS_AS( app.Main( args ), InvalidArgumentException );
            }
        }
    }
}
SCENARIO("validating the data file")
{
	GIVEN("an app instance")
	{
		auto app = CppGrapher();

        WHEN("the app is given a non-existent data file to read")
        {
            auto filename = utf8_string( "cpp-grapher-test.should-not-exist" );
            std::remove( filename.c_str() );

            auto args = std::vector<utf8_string> { "cpp-grapher", filename };

            THEN("the app should throw a NonExistentFileException")
            {
                REQUIRE_THROWS_AS( app.Main( args ), std::ios_base::failure );
            }
        }
    }
}
