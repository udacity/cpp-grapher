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

        WHEN("one (system) + two (user) arguments are supplied")
        {
            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  u8"cpp-grapher-test_input",
                                                  u8"cpp-grapher-test_output"};

            THEN("it should not throw an invalid argument exception")
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

        WHEN("only one (system) argument is supplied")
        {
            auto args = std::vector<utf8_string> {u8"cpp-grapher-test"};

            THEN("it should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), InvalidArgumentException);
            }
        }

        WHEN("only one (system) + one (user) arguments are supplied")
        {
            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  u8"cpp-grapher-test_input"};

            THEN("it should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), InvalidArgumentException);
            }
        }

        AND_WHEN("one (system) + three (user) arguments are supplied")
        {
            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  u8"cpp-grapher-test_input",
                                                  u8"cpp-grapher-test_output",
                                                  u8"cpp-grapher-test_one-too-many-args"};

            THEN("it should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), InvalidArgumentException);
            }
        }
    }
}
