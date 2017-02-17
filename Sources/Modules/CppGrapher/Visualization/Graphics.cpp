#include <vector>
#include <cmath>
#include <Helpers/Unicode.h>

#include "Helpers/Filesystem.h"
#include "CppGrapher.h"

using namespace Magick;
using namespace udacity;
using namespace ranged_graph;

Magick::Image CppGrapher::GraphDataPoints(std::vector<KalmanFilterDataPoint> dataPoints)
{
    auto coords = std::vector<PointCoord>();
    coords.reserve(dataPoints.size());
    std::transform(std::begin(dataPoints),
                   std::end(dataPoints),
                   std::back_inserter(coords),
                   [](auto dataPoint) { return dataPoint.coord; });
    auto graph = RangedGraph(RangedGraph::DEFAULT_CANVAS_SIZE, MakeRange2D(coords));

    std::sort(std::begin(dataPoints), std::end(dataPoints), [](auto a, auto b){ return a.name < b.name; });

    auto color = GetUniqueColor();
    auto name = dataPoints.front().name;
    AddNonWhitespaceLabelToLegend(name, color, graph);
    for(const auto& dataPoint : dataPoints)
    {
        if(dataPoint.name != name)
        {
            color = GetUniqueColor();
            name = dataPoint.name;
            AddNonWhitespaceLabelToLegend(name, color, graph);
        }
        graph.SetPoint(PointCoord(dataPoint.coord.first, dataPoint.coord.second), color);
    }
    return graph.GetCanvas();
}

Color CppGrapher::GetUniqueColor()
{
    const double SATURATION_FULL = 1_f64;
    const double LEVEL_30_PERCENT = 0.3_f64;

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

    return Magick::ColorHSL(hueAngles[hueAngleIdx] + hueAngleOffsets[hueAngleOffsetIdx++],
                            SATURATION_FULL,
                            LEVEL_30_PERCENT);
}

CppGrapher CppGrapher::AddNonWhitespaceLabelToLegend(const utf8_string& label,
                                                     const Color& color,
                                                     RangedGraph& graph)
{
    //if(label.find_first_not_of(UnicodeLiterals::WHITESPACE, 0) != utf8_string::npos)
    {
        graph.AddLegendItem(label, color);
    }
    return *this;
}
