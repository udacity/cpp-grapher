#include <iostream>
#include <vector>
#include <cmath>

#include "Helpers/Filesystem.h"
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

//TODO Write GetUniqueColor() declaratively
Color CppGrapher::GetUniqueColor()
{
    if(this->hueAngles.size() == 0)
    {
        hueAngles.push_back(0);   //Sets initial limit of primary hue angle
    }

    if(hueAngleOffsetIdx >= hueAngleOffsets.size())
    {
        hueAngleOffsetIdx = 0;
        ++hueAngleIdx;
    }

    if(hueAngleIdx >= hueAngles.size())
    {
        hueAngleIdx = 0;
        hueAngles.clear();
        auto hueStep = (AreApproxEqual(hueAngles[0], 0_f64) ? hueAngleOffsets[1] : hueAngles[0]) / 2_f80;
        auto stepCount = static_cast<size_t>(std::ceil(hueAngleOffsets[1] / hueStep) / 2);
        hueAngles.reserve(stepCount);
        for(auto i = 1_f64; i <= stepCount; ++i)
        {
            hueAngles.push_back(static_cast<f64>((2 * i - 1) * hueStep));
        }
    }

    return Magick::ColorHSL(hueAngles[hueAngleIdx] + hueAngleOffsets[hueAngleOffsetIdx++], 1, 0.5);
}
