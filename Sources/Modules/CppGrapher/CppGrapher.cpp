#include <iostream>
#include <Helpers/Filesystem.h>
#include <vector>

#include "CppGrapher.h"

const std::string CppGrapher::DEFAULT_GRAPH_SIZE = "1280x720";

int CppGrapher::Main(const std::vector<utf8_string>& args)
{
    ValidateArgs(args);
	auto dataPoints = DeserializeDataPoints(args[ArgsIndexNames::INPUT_FILENAME].cpp_str());
    auto graph = GraphDataPoints(dataPoints);
	return EXIT_SUCCESS;
}
