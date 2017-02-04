#include <iostream>
#include <Helpers/Filesystem.h>
#include <vector>

#include "CppGrapher.h"

constexpr auto filenameArgIdx = 1;

int CppGrapher::Main(const std::vector<utf8_string>& args)
{
	ValidateArgs(args);
	auto userData = ParseKalmanFilterDataFile(args[filenameArgIdx]);
	return EXIT_SUCCESS;
}
