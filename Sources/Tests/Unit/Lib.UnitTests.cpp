#include <regex>
#include "catch.hpp"
#include "Lib.h"

SCENARIO("Ensure project can say hello")
{
	GIVEN("an instance of the Lib class")
	{
		auto hello = Hello();

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
