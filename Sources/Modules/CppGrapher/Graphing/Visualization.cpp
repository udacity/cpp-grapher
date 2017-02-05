#include "RangedGraph/RangedGraph.h"
#include "CppGrapher.h"

using namespace Magick;

Magick::Image
CppGrapher::GraphDataPoints(const std::vector<KalmanFilterDataPoint>& dataPoints) const
{
    auto graph = RangedGraph(DEFAULT_GRAPH_SIZE);
    for(const auto& dataPoint : dataPoints)
    {
        graph.SetPoint(dataPoint.x, dataPoint.y, "black");
    }
    return graph.GetImage();
}
