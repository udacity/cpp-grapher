#include <iostream>
#include "Helpers/Exceptions.h"
#include "Helpers/Resources.h"
#include "RangedGraph.h"

using namespace Magick;

namespace udacity {
namespace ranged_graph
{
    const std::string RangedGraph::DEFAULT_CANVAS_SIZE = "1280x720";
    const size_t RangedGraph::CANVAS_MARGIN_PIXELS = 64;
    const Color RangedGraph::DEFAULT_CANVAS_COLOR = Color(0xff, 0xff, 0xff);
    const Color RangedGraph::DEFAULT_AXIS_COLOR = Color(0x20, 0x20, 0x20);

    template<typename T>
    bool AreApproxEqual(T f1, T f2)
    {
        return (std::fabs(f1 - f2) <= std::numeric_limits<T>::epsilon() * std::fmax(fabs(f1), fabs(f2)));
    }

    RangedGraph::RangedGraph(const std::string graphCanvasSize, const Range2D& range2D)
    {
        //Margin determined empirically

        ValidateGraphRange(range2D);
        auto span2D = CalculateGraphSpan(range2D);
        canvas_ = MakeGraphCanvas(graphCanvasSize, DEFAULT_CANVAS_COLOR);
        pointsPerPixel_ = CalculatePointsPerPixel(span2D, canvas_);
        range2D_ = MakeCenteredGraphRange(range2D, span2D, pointsPerPixel_, canvas_);
        RenderAxes(canvas_, DEFAULT_AXIS_COLOR, range2D_);
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
        return Span2D(static_cast<f64>(static_cast<f80>(range2D.first.second) - range2D.first.first),
                      static_cast<f64>(static_cast<f80>(range2D.second.second) - range2D.second.first));
    }

    Image RangedGraph::MakeGraphCanvas(const std::string& pixelSizeDesc, const Color& canvasColor) const
    {
        auto image = Image(pixelSizeDesc.c_str(), canvasColor);
        ValidateGraph(image);
        return image;
    }

    RangedGraph RangedGraph::ValidateGraph(const Image& canvas) const
    {
        if(CANVAS_MARGIN_PIXELSres * 2 >= canvas.rows() || CANVAS_MARGIN_PIXELS * 2 >= canvas.columns())
        {
            auto pixelCount = utf8_string(std::to_string(static_cast<size_t>(ceil(CANVAS_MARGIN_PIXELS * 2) + 1)));
            throw InvalidGraphSizeException(utf8_string(Msg::InvalidArg::GRAPH_MUST_BE_AT_LEAST_PREFIX) +
                                                pixelCount +
                                                utf8_string("x") +
                                                pixelCount +
                                                utf8_string(Msg::InvalidArg::GRAPH_MUST_BE_AT_LEAST_SUFFIX));
        }
        return *this;
    }

    double RangedGraph::CalculatePointsPerPixel(const Span2D& span2D, const Image& canvas) const
    {
        auto doubleMargin  = CANVAS_MARGIN_PIXELS * 2;
        ValidateGraph(canvas);
        return static_cast<f64>(std::max(static_cast<f80>(span2D.first) /
                                             (canvas.columns() - static_cast<size_t>(ceil(doubleMargin))),
                                         static_cast<f80>(span2D.second) /
                                             (canvas.rows() - static_cast<size_t>(ceil(doubleMargin)))));
    }

    Range2D RangedGraph::MakeCenteredGraphRange(const Range2D& range2D, const Span2D& span2D, const double pointsPerPixel,
                                                    const Image& image) const
    {
        auto xSpanHalfDelta = (pointsPerPixel * (image.columns() - CANVAS_MARGIN_PIXELS * 2) - span2D.first) / 2;
        auto ySpanHalfDelta = (pointsPerPixel * (image.rows() - CANVAS_MARGIN_PIXELS * 2) - span2D.second) / 2;

        return xSpanHalfDelta < 0 || ySpanHalfDelta < 0
               ? range2D
               : MakeRange2D(static_cast<f64>(range2D.first.first - xSpanHalfDelta),
                             static_cast<f64>(range2D.first.second + xSpanHalfDelta),
                             static_cast<f64>(range2D.second.first - ySpanHalfDelta),
                             static_cast<f64>(range2D.second.second + ySpanHalfDelta));
    }

    RangedGraph RangedGraph::SetPoint(const PointCoord& point, const Color& color)
    {
        ValidatePointInGraph(point);
        auto pixelCoord = ConvertPointToPixelCoord(point);
        canvas_.pixelColor(pixelCoord.first, pixelCoord.second, color);

        return *this;
    }

    RangedGraph RangedGraph::ValidatePointInGraph(const PointCoord& pointCoord) const
    {
        auto pixelCoord = ConvertPointToPixelCoord(pointCoord);
        if (pixelCoord.first > canvas_.columns() || pixelCoord.second > canvas_.rows())
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
        return PixelCoord(
            static_cast<size_t>(CANVAS_MARGIN_PIXELS +
                    std::fabs(static_cast<f80>(pointCoord.first) - range2D_.first.first) / pointsPerPixel_),
            static_cast<size_t>(CANVAS_MARGIN_PIXELS +
                    std::fabs(static_cast<f80>(pointCoord.second) - range2D_.second.first) / pointsPerPixel_));
    }

    Image RangedGraph::GetImage() const
    {
        return canvas_;
    }

    void RangedGraph::RenderAxes(Magick::Image& canvas, const Magick::Color& axisColor, const Range2D& range2D) const
    {
        auto canvasThinStrokeWidth = 1;
        auto canvasBoldStrokeWidth = 3;

        canvas.strokeColor(axisColor);
        canvas.strokeWidth(canvasBoldStrokeWidth);
        canvas.strokeAntiAlias(false);

        canvas.draw(DrawableLine(CANVAS_MARGIN_PIXELS, canvas.rows() - CANVAS_MARGIN_PIXELS,
                                 canvas.columns() - CANVAS_MARGIN_PIXELS, canvas.rows() - CANVAS_MARGIN_PIXELS));
        canvas.draw(DrawableLine(CANVAS_MARGIN_PIXELS, CANVAS_MARGIN_PIXELS,
                                 CANVAS_MARGIN_PIXELS, canvas.rows() - CANVAS_MARGIN_PIXELS));

        canvas.strokeWidth(canvasThinStrokeWidth);
        canvas.strokeAntiAlias(true);
        auto axisSegments = 10;
        auto axisValue = std::pair<double, double>(range2D_.first.first, range2D_.second.first);
        auto axisValueSpan2D = Span2D(range2D_.first.second - axisValue.first, range2D_.second.second - axisValue.second);
        auto axisValueInterval = std::pair<f80, f80>(static_cast<f80>(axisValueSpan2D.first) / axisSegments,
                                                     static_cast<f80>(axisValueSpan2D.second) / axisSegments);
        auto axisPos = std::pair<size_t, size_t>(CANVAS_MARGIN_PIXELS, canvas.rows() - CANVAS_MARGIN_PIXELS);
        auto axisPosSpan = std::pair<size_t, size_t>(
                canvas.columns() - static_cast<size_t>(CANVAS_MARGIN_PIXELS) - axisPos.first,
                axisPos.second - CANVAS_MARGIN_PIXELS);
        auto axisPosInterval = std::pair<f80, f80>(static_cast<f80>(axisPosSpan.first) / axisSegments,
                                                   static_cast<f80>(axisPosSpan.second) / axisSegments);
        auto origin = PixelCoord(CANVAS_MARGIN_PIXELS, canvas.rows() - CANVAS_MARGIN_PIXELS);
        auto textOffset = std::pair<PixelSpan2D, PixelSpan2D>(PixelSpan2D(-3, 14),
                                                              PixelSpan2D(-CANVAS_MARGIN_PIXELS + 3, + 3)); //Offsets determined empirically

        for(auto i = 0; i <= axisSegments; ++i)
        {
            //x-axis labels
            canvas.strokeWidth(canvasBoldStrokeWidth);
            canvas.strokeAntiAlias(false);
            canvas.draw(DrawableLine(axisPos.first, origin.second, axisPos.first, origin.second + 3));
            canvas.strokeWidth(canvasThinStrokeWidth);
            canvas.strokeAntiAlias(true);
            canvas.draw(DrawableText(axisPos.first + textOffset.first.first, origin.second + textOffset.first.second,
                                     std::to_string(axisValue.first), "UTF-8"));
            axisValue.first += axisValueInterval.first;
            axisPos.first += static_cast<size_t>(axisPosInterval.first);

            //y-axis labels
            canvas.strokeWidth(canvasBoldStrokeWidth);
            canvas.strokeAntiAlias(false);
            canvas.draw(DrawableLine(origin.first - 3, axisPos.second, origin.first, axisPos.second));
            canvas.strokeWidth(canvasThinStrokeWidth);
            canvas.strokeAntiAlias(true);
            canvas.draw(DrawableText(origin.first + textOffset.second.first, axisPos.second + textOffset.second.second,
                                     std::to_string(axisValue.second), "UTF-8"));
            axisValue.second += axisValueInterval.second;
            axisPos.second -= static_cast<size_t>(axisPosInterval.second);
        }
    }
}}
