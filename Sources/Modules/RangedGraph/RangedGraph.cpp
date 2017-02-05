#include "Helpers/Exceptions.h"
#include "Helpers/Resources.h"
#include "RangedGraph.h"

using namespace Magick;

RangedGraph::RangedGraph(std::string pixelSizeDesc, Range xR, Range yR)
{
    ValidateRange(xR);
    ValidateRange(yR);

    auto xSpan = std::get<RangeIdxNames::END>(xR) - std::get<RangeIdxNames::BEG>(xR);
    auto ySpan = std::get<RangeIdxNames::END>(yR) - std::get<RangeIdxNames::BEG>(yR);

    if(xSpan > ySpan) { yR = CenterRange(yR, xSpan - ySpan); }
    if(ySpan > xSpan) { xR = CenterRange(xR, ySpan - xSpan); }

    xRange = xR;
    yRange = yR;
    graph = MakeBlankGraph(pixelSizeDesc);
}

RangedGraph RangedGraph::ValidateRange(Range range)
{
    if(std::get<RangeIdxNames::BEG>(range) > std::get<RangeIdxNames::END>(range))
    { throw InvalidRangeException(Msg::InvalidArg::INVALID_RANGE_BEG_GREATER_THAN_END); }
    if(AreApproxEqual(std::get<RangeIdxNames::BEG>(range), std::get<RangeIdxNames::END>(range)))
            { throw InvalidRangeException(Msg::InvalidArg::INVALID_RANGE_NO_SPAN); }
    return *this;
}

Range RangedGraph::CenterRange(const std::tuple<double, double>& range, const double span) const
{
    return Range(std::get<RangeIdxNames::BEG>(range) - span / 2,
                 std::get<RangeIdxNames::END>(range) + span / 2);
}

RangedGraph RangedGraph::SetPoint(const double pointX, const double pointY, const Color& color)
{
    graph.pixelColor(pointX, pointY, color);
    return *this;
}

template<typename T>
bool RangedGraph::AreApproxEqual(T f1, T f2)
{
    return (std::fabs(f1 - f2) <= std::numeric_limits<T>::epsilon() * std::fmax(fabs(f1), fabs(f2)));
}

Image RangedGraph::MakeBlankGraph(const std::string& pixelSizeDesc) const
{
    auto image = Image(pixelSizeDesc.c_str(), "white");
    return image;
}

Image RangedGraph::GetImage() const
{
    return graph;
}

