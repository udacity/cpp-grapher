#include "CppGrapher.h"

using namespace Magick;

Image CppGrapher::MakeBlankGraph(const std::string& pixelSizeDesc) const
{
    auto image = Image(pixelSizeDesc.c_str(), "white");
    return image;
}

Magick::Image
CppGrapher::GraphDataPoints(const std::vector<KalmanFilterDataPoint>& dataPoints) const
{
    auto graph = MakeBlankGraph();
    for(const auto& dataPoint : dataPoints)
    {
        graph.pixelColor(dataPoint.x, dataPoint.y, "black");
    }
    return graph;
}
