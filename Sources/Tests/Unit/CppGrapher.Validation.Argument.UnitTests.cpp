#include <regex>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Exceptions.h"
#include "Helpers/Filesystem.h"

SCENARIO("Parsing command line arguments")
{
    GIVEN("an app instance")
    {
        auto app = CppGrapher();

        WHEN("two arguments are supplied")
        {
            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner",
                                                  u8"cpp-grapher-test.should-not-exist"};

            THEN("it should not throw an invalid arguments exception")
            {
                try
                {
                    app.Main(args);
                }
                catch (std::exception& e)
                {
                    REQUIRE_THROWS_AS(throw, FileNotFoundException);
                }
            }
        }

        WHEN("no arguments are supplied")
        {
            auto args = std::vector<utf8_string> {};

            THEN("it should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), InvalidArgumentException);
            }
        }

        AND_WHEN("one argument is supplied")
        {
            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner"};

            THEN("it should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), InvalidArgumentException);
            }
        }

        AND_WHEN("three arguments are supplied")
        {
            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner", u8"sample-arg2", u8"sample-arg3"};

            THEN("it should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), InvalidArgumentException);
            }
        }
    }
}
