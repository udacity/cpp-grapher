#include <iostream>
#include "Helpers/Exceptions.h"
#include "Helpers/Resources.h"
#include "RangedGraph.h"

using namespace Magick;

namespace udacity {
namespace ranged_graph
{
    const std::string RangedGraph::DEFAULT_GRAPH_CANVAS_SIZE = "1280x720";

    template<typename T>
    bool AreApproxEqual(T f1, T f2)
    {
        return (std::fabs(f1 - f2) <= std::numeric_limits<T>::epsilon() * std::fmax(fabs(f1), fabs(f2)));
    }

    RangedGraph::RangedGraph(const std::string graphCanvasSize, const Range2D& range2D)
    {
        ValidateGraphRange(range2D);
        auto span2D = CalculateGraphSpan(range2D);
        image_ = MakeGraphCanvas(graphCanvasSize);
        pointsPerPixel_ = CalculatePointsPerPixel(span2D, image_);
        range2D_ = MakeCenteredGraphRange(range2D, span2D, pointsPerPixel_, image_);
    }

    RangedGraph RangedGraph::ValidateGraphRange(const Range2D& range2D) const
    {
        ValidateRange(range2D.first);
        ValidateRange(range2D.second);

        return *this;
    }

    RangedGraph RangedGraph::ValidateRange(const Range& range) const
    {
        if (range.first > range.second)
        {
            throw InvalidRangeException(Msg::InvalidArg::INVALID_RANGE_MIN_GREATER_THAN_MAX);
        }

        if (AreApproxEqual(range.first, range.second))
        {
            throw InvalidRangeException(Msg::InvalidArg::INVALID_RANGE_NO_SPAN);
        }
        return *this;
    }

    Span2D RangedGraph::CalculateGraphSpan(const Range2D& range2D) const
    {
        return Span2D(range2D.first.second - range2D.first.first,
                         range2D.second.second - range2D.second.first);
    }

    Image RangedGraph::MakeGraphCanvas(const std::string& pixelSizeDesc) const
    {
        auto image = Image(pixelSizeDesc.c_str(), "white");
        ValidateGraph(image);
        return image;
    }

    RangedGraph RangedGraph::ValidateGraph(const Image& image) const
    {
        if(image.rows() < 1 || image.columns() < 1)
        {
            throw InvalidGraphSizeException(Msg::InvalidArg::GRAPH_MUST_BE_AT_LEAST_1_X_1);
        }
        return *this;
    }

    double RangedGraph::CalculatePointsPerPixel(const Span2D& span2D, const Image& image) const
    {
        ValidateGraph(image);
        return std::max(span2D.first / image.columns(),
                        span2D.second / image.rows());
    }

    Range2D RangedGraph::MakeCenteredGraphRange(const Range2D& range2D,
                                                const Span2D& span2D,
                                                const double pointsPerPixel,
                                                const Image& image) const
    {
        auto xSpanHalfDelta = (pointsPerPixel * image.columns() - span2D.first) / 2;
        auto ySpanHalfDelta = (pointsPerPixel * image.rows() - span2D.second) / 2;

        return xSpanHalfDelta < 0 || ySpanHalfDelta < 0
               ? range2D
               : MakeRange2D(range2D.first.first - xSpanHalfDelta,
                             range2D.first.second + xSpanHalfDelta,
                             range2D.second.first - ySpanHalfDelta,
                             range2D.second.second + ySpanHalfDelta);
    }

    RangedGraph RangedGraph::SetPoint(const PointCoord& point, const Color& color)
    {
        ValidatePointInGraph(point);
        //TODO: Remove
        std::cout << "*** Image(x(0, " << image_.columns() - 1 << "), y(0, " << image_.rows() - 1 << ")), Range2D(Range("
                  << range2D_.first.first << ", " << range2D_.first.second << "), ("
                  << range2D_.second.first << ", " << range2D_.second.second << ")) @ " << pointsPerPixel_ << "_=> PixelRange(("
                  << image_.columns() / 2 - pointsPerPixel_ * (std::fabs(range2D_.first.second - range2D_.first.first) / 2)
                  << ", "
                  << image_.columns() / 2 + pointsPerPixel_ * (std::fabs(range2D_.first.second - range2D_.first.first) / 2)
                  << "), "
                  << image_.rows() / 2 - pointsPerPixel_ * (std::fabs(range2D_.second.second - range2D_.second.first) / 2)
                  << ", "
                  << image_.rows() / 2 + pointsPerPixel_ * (std::fabs(range2D_.second.second - range2D_.second.first) / 2)
                  << ")) ***" << std::endl;
        auto pixelCoord = ConvertPointToPixelCoord(point);
        //TODO: Remove
        std::cout << "*** PixelCoord(" << pixelCoord.first << "," << pixelCoord.second << ") ***" << std::endl;
        image_.pixelColor(pixelCoord.first, pixelCoord.second, color);

        return *this;
    }

    RangedGraph RangedGraph::ValidatePointInGraph(const PointCoord& pointCoord) const
    {
        auto pixelCoord = ConvertPointToPixelCoord(pointCoord);
        if (pixelCoord.first > image_.columns() || pixelCoord.second > image_.rows())
        {
            throw PointOutOfRangeException(utf8_string(Msg::InvalidArg::POINT_OUT_OF_RANGE) +
                                           utf8_string(Msg::EXPECTED_RANGE) +
                                           utf8_string("x: " + std::to_string(range2D_.first.first) + " - " +
                                                       std::to_string(range2D_.first.second)) +
                                           utf8_string(Msg::EXPECTED_RANGE_SEPARATOR) +
                                           utf8_string("y: " + std::to_string(range2D_.second.first) + " - " +
                                                       std::to_string(range2D_.second.second)) +
                                           utf8_string(Msg::RECEIVED_OUT_OF_RANGE_VALUE) +
                                           utf8_string(std::to_string(pointCoord.first) + ", " +
                                                       std::to_string(pointCoord.second)) +
                                           utf8_string(Msg::EXPECTED_RANGE_TERMINATOR));
        }

        return *this;
    }

    PixelCoord RangedGraph::ConvertPointToPixelCoord(const PointCoord& pointCoord) const
    {
        return PixelCoord(static_cast<size_t>(std::fabs(pointCoord.first - range2D_.first.first) / pointsPerPixel_),
                     static_cast<size_t>(std::fabs(pointCoord.second - range2D_.second.first) / pointsPerPixel_));
    }

    Image RangedGraph::GetImage() const
    {
        return image_;
    }
}}
