#include <iostream>
#include <Helpers/Filesystem.h>
#include <vector>
#include <cmath>

#include "CppGrapher.h"
#include "RangedGraph.h"

using namespace Magick;
using namespace udacity;
using namespace ranged_graph;

int CppGrapher::Main(const std::vector<utf8_string>& args)
{
    ValidateArgs(args);
	auto dataPoints = DeserializeDataPoints(args[ArgsIndexNames::INPUT_FILENAME].cpp_str());
    auto graph = GraphDataPoints(dataPoints);
    //Save, output graph at base64 to stdout
	return EXIT_SUCCESS;
}
