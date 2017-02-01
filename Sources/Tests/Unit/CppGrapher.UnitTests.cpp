#include <regex>
#include "catch.hpp"
#include "Helpers/Exceptions.h"
#include "CppGrapher.h"

SCENARIO("Ensure project can say hello")
{
	GIVEN("an instance of the CppGrapher class")
	{
		auto hello = CppGrapher();

		WHEN("the greeter is asked to say hello")
		{
			auto result = hello.Greet();

			THEN("the correct greeting was issued")
			{
				const auto expectedResult = std::regex("Hello \\d+-bit World!\n");
				REQUIRE(std::regex_match(result, expectedResult));
			}
		}
	}
}

SCENARIO("Parsing command line arguments")
{
	GIVEN("an app instance")
	{
		auto app = CppGrapher();

		WHEN("two arguments are supplied")
		{
			auto args = std::vector<utf8_string> {"sample-arg1", "sample-arg2"};

			THEN("it should not throw an InvalidArgumentException")
			{
				try
				{
					app.Main(args);
				}
				catch(std::exception& e)
				{
					REQUIRE_THROWS_AS(throw, InvalidArgumentException);
				}
			}
		}

		WHEN("no arguments are supplied")
		{
			auto args = std::vector<utf8_string> {};

			THEN("it should throw an InvalidArgumentException")
			{
				REQUIRE_THROWS_AS(app.Main(args), InvalidArgumentException);
			}
		}

		AND_WHEN("one argument is supplied")
		{
			auto args = std::vector<utf8_string> {"sample-arg1"};

			THEN("it should throw an InvalidArgumentsException")
			{
				REQUIRE_THROWS_AS(app.Main(args), InvalidArgumentException);
			}
		}

		AND_WHEN("three arguments are supplied")
		{
			auto args = std::vector<utf8_string> {"sample-arg1", "sample-arg2", "sample-arg3"};

			THEN("it should throw an InvalidArgumentsException")
			{
				REQUIRE_THROWS_AS(app.Main(args), InvalidArgumentException);
			}
		}
	}
}
