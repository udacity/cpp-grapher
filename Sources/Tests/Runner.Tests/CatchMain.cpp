#include <cstdint>
#include <iostream>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(const int argc, const char* const argv[])
{
	auto returnCode = Catch::Session().run(argc, argv);

//	std::cout << "\nPress any key to exit..." << std::endl;
//	static_cast<void>(std::getchar());

	return returnCode;
}
