#include <iostream>
#include <Helpers/Filesystem.h>
#include <vector>
#include <cmath>

#include "CppGrapher.h"
#include "RangedGraph.h"

using namespace Magick;
using namespace udacity;
using namespace ranged_graph;

Magick::Image CppGrapher::GraphDataPoints(const std::vector<KalmanFilterDataPoint>& dataPoints) const
{
    auto graph = RangedGraph(RangedGraph::DEFAULT_CANVAS_SIZE, MakeRange2D(-1, 1));
    for(const auto& dataPoint : dataPoints)
    {
        graph.SetPoint(PointCoord(dataPoint.x, dataPoint.y), "black");
    }
    return graph.GetImage();
}

int CppGrapher::Main(const std::vector<utf8_string>& args)
{
    ValidateArgs(args);
	auto dataPoints = DeserializeDataPoints(args[ArgsIndexNames::INPUT_FILENAME].cpp_str());
    auto graph = GraphDataPoints(dataPoints);
    //Save, output graph at base64 to stdout
	return EXIT_SUCCESS;
}
