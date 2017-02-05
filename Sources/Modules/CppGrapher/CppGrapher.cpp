#include <iostream>
#include <Helpers/Filesystem.h>
#include <vector>

#include "CppGrapher.h"

const std::string CppGrapher::DEFAULT_GRAPH_SIZE = "1280x720";

int CppGrapher::Main(const std::vector<utf8_string>& args)
{
    ValidateArgs(args);
	auto userData = ParseKalmanFilterDataFile(args[NamedArgs::INPUT_FILENAME].cpp_str());
	return EXIT_SUCCESS;
}
