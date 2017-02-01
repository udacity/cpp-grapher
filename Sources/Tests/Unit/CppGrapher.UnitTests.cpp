#include <regex>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Exceptions.h"

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

		WHEN("no arguments are supplied")
		{
			auto args = std::vector<std::string> {};

			THEN("it should throw an InvalidArgumentException")
			{
				REQUIRE_THROWS(app.Main(args));
			}
		}
	}
}
