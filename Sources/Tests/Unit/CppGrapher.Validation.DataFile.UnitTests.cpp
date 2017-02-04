#include <regex>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Exceptions.h"
#include "Helpers/Filesystem.h"

SCENARIO("Validating the data file")
{
    GIVEN("an app instance")
    {
        auto app = CppGrapher();

        WHEN("the app is given a non-existent data file to read")
        {
            auto filename = utf8_string(u8"cpp-grapher-test.should-not-exist");
            std::remove(filename.c_str());

            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner", filename};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), FileNotFoundException);
            }
        }

        AND_WHEN("the app is given an existing but empty data file to read")
        {
            auto filename = utf8_string(u8"cpp-grapher-test.should-exist");
            auto fs = TemporaryFileStream(filename);

            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner", filename};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), NoDataFoundException);
            }
        }

        AND_WHEN("a file with valid data is provided")
        {
            auto filename = utf8_string(u8"cpp-grapher-test.valid-data");
            auto fileContents = u8"test_name 1.0 2.0";
            auto fs = TemporaryFileStream(filename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner", filename};

            THEN("the app should return successfully")
            {
                REQUIRE(app.Main(args) == EXIT_SUCCESS);
            }
        }

        AND_WHEN("a valid multi-line file with valid data is provided")
        {
            auto filename = utf8_string(u8"cpp-grapher-test.valid-data");
            auto fileContents = u8"test_line_1 1.0 2.0\ntest_line_2 3.0 4\ntest_line_3 5.1 6.2";
            auto fs = TemporaryFileStream(filename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner", filename};

            THEN("the app should return successfully")
            {
                REQUIRE(app.Main(args) == EXIT_SUCCESS);
            }
        }

        AND_WHEN("a valid file with 'esoteric' whitespace is provided")
        {
            auto filename = utf8_string(u8"cpp-grapher-test.valid-data");
            auto fileContents = u8"test_line_1\t1.0\r2.0\ntest_line_2\v3.0\u205f4\ntest_line_3 5.1 6.2";
            auto fs = TemporaryFileStream(filename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner", filename};

            THEN("the app should return successfully")
            {
                REQUIRE(app.Main(args) == EXIT_SUCCESS);
            }
        }

        AND_WHEN("an invalid file with bad delimiters is provided")
        {
            auto filename = utf8_string(u8"cpp-grapher-test.valid-data");
            auto fileContents = u8"test_name,1.0;2.0";
            auto fs = TemporaryFileStream(filename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner", filename};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), TokenNotFoundException);
            }
        }

        AND_WHEN("a dataset with missing tokens is provided")
        {
            auto filename = utf8_string(u8"cpp-grapher-test.invalid-data");
            auto fileContents = u8"test_name";
            auto fs = TemporaryFileStream(filename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner", filename};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), TokenNotFoundException);
            }
        }

        AND_WHEN("a dataset with invalid numeric tokens is provided")
        {
            auto filename = utf8_string(u8"cpp-grapher-test.invalid-data");
            auto fileContents = u8"test_name not_a_number1 not_a_number2";
            auto fs = TemporaryFileStream(filename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner", filename};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), BadDataException);
            }
        }
    }
}
