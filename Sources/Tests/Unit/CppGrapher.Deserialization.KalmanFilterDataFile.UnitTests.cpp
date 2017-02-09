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

        WHEN("a file with valid data is provided")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher-test_input.valid-data");
            auto fileContents = utf8_string(u8"test_name -0.1 0.5");
            auto outputFilename = utf8_string(u8"cpp-grapher-test_output");

            auto ifs = TemporaryFileStream(inputFilename, fileContents);
            auto ofs = TemporaryFileStream(outputFilename);

            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  inputFilename,
                                                  outputFilename};

            THEN("the app should return successfully")
            {
                REQUIRE(app.Main(args) == EXIT_SUCCESS);
            }
        }

        AND_WHEN("the app is given a non-existent data file to read")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher-test_input.should-not-exist");
            std::remove(inputFilename.c_str());

            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  inputFilename,
                                                  u8"cpp-grapher-test_output"};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), FileNotFoundException);
            }
        }

        AND_WHEN("the app is given an existing but empty data file to read")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher-test_input.should-exist");
            auto ifs = TemporaryFileStream(inputFilename);

            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  inputFilename,
                                                  u8"cpp-grapher-test_output"};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), NoDataFoundException);
            }
        }

        AND_WHEN("a valid multi-line file with valid data is provided")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher-test_input.valid-data");
            auto fileContents = utf8_string(u8"test_line_1 -0.1 0.5\ntest_line_2 -0.2 0.4\ntest_line_3 -0.7 1.0");
            auto ifs = TemporaryFileStream(inputFilename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  inputFilename,
                                                  u8"cpp-grapher-test_output"};

            THEN("the app should return successfully")
            {
                REQUIRE(app.Main(args) == EXIT_SUCCESS);
            }
        }

        AND_WHEN("a valid file with 'esoteric' whitespace is provided")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher-test_input.valid-data");
            auto fileContents = utf8_string(u8"test_line_1 -0.1 0.5\ntest_line_2 -0.2 0.4\ntest_line_3 -0.7 1");
            auto ifs = TemporaryFileStream(inputFilename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  inputFilename,
                                                  u8"cpp-grapher-test_output"};

            THEN("the app should return successfully")
            {
                REQUIRE(app.Main(args) == EXIT_SUCCESS);
            }
        }

        AND_WHEN("an invalid file with bad delimiters is provided")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher-test_input.valid-data");
            auto fileContents = utf8_string(u8"test_name,-0.1;0.5");
            auto ifs = TemporaryFileStream(inputFilename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  inputFilename,
                                                  u8"cpp-grapher-test_output"};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), TokenNotFoundException);
            }
        }

        AND_WHEN("a dataset with missing tokens is provided")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher-test_input.invalid-data");
            auto fileContents = utf8_string(u8"test_name");
            auto ifs = TemporaryFileStream(inputFilename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  inputFilename,
                                                  u8"cpp-grapher-test_output"};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), TokenNotFoundException);
            }
        }

        AND_WHEN("a dataset with invalid numeric tokens is provided")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher-test_input.invalid-data");
            auto fileContents = u8"test_name not_a_number1 not_a_number2";
            auto ifs = TemporaryFileStream(inputFilename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  inputFilename,
                                                  u8"cpp-grapher-test_output"};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), BadDataException);
            }
        }
    }
}
