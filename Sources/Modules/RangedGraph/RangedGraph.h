#ifndef RANGED_GRAPH_H
#define RANGED_GRAPH_H

#include <cmath>
#include <Magick++/Color.h>
#include <Magick++/Image.h>
#include <iostream>
#include <Helpers/Exceptions.h>
#include <Helpers/Resources.h>
#include "Helpers/UserDefinedLiterals.h"

static_assert(sizeof(long double) > sizeof(double), "RangedGraph requires support for extended-precision floating point to operate correctly.  Extended-precision is not supported by your compiler and/or hardware platform.");

//Forward declaration required to conditionally grant test framework access to privates
#ifdef RANGED_GRAPH_ACCESS_PRIVATES
class TestHelper;
#endif

namespace udacity {
namespace ranged_graph
{
    using Range = std::pair<double, double>;
    using Range2D = std::pair<Range, Range>;
    using PointCoord = std::pair<double, double>;
    using PixelCoord = std::pair<size_t, size_t>;
    using Span2D = std::pair<double, double>;

    inline void ValidateDouble(const double n)
    {
        if(!(n >= std::numeric_limits<double>::lowest() && n <= std::numeric_limits<double>::max())) //NaN, +/-infinity
        {
            throw InvalidArgumentException(Msg::InvalidArg::INVALID_DOUBLE_RECEIVED);
        }
    }

    inline Range2D MakeRange2D(const double xMin, const double xMax, const double yMin, const double yMax)
    {
        ValidateDouble(xMin);
        ValidateDouble(xMax);
        ValidateDouble(yMin);
        ValidateDouble(yMax);

        return Range2D(Range(xMin, xMax), Range(yMin, yMax));
    }

    inline Range2D MakeRange2D(const double min, const double max)
    {
        return MakeRange2D(min, max, min, max);
    }

    template<typename T>
    bool AreApproxEqual(T f1, T f2);

    class RangedGraph
    {
    public:
        /// Default graph size convenience constant (in pixels).  Defined in RangedGraph.cpp.  To be consumed directly by
        /// ImageMagick.
        static const std::string DEFAULT_GRAPH_CANVAS_SIZE;

        RangedGraph(const std::string graphCanvasSize, const Range2D& graphRange);

        RangedGraph SetPoint(const PointCoord& point, const Magick::Color& color);

        Magick::Image GetImage() const;

    private:
//Conditionally grant test framework access to privates
#ifdef RANGED_GRAPH_ACCESS_PRIVATES
        friend class ::TestHelper;
#endif

        long double pointsPerPixel_;
        Range2D range2D_;
        Magick::Image image_;

        RangedGraph ValidateGraphRange(const Range2D& GraphPointRange) const;

        RangedGraph ValidateRange(const Range& pointRange) const;

        Range2D MakeCenteredGraphRange(const Range2D& range2D,
                                       const Span2D& span2D,
                                       const double pointsPerPixel,
                                       const Magick::Image& image) const;

        Magick::Image MakeGraphCanvas(const std::string& graphCanvasSize) const;

        RangedGraph ValidateGraph(const Magick::Image& image) const;

        RangedGraph ValidatePointInGraph(const PointCoord& pointCoord) const;

        PixelCoord ConvertPointToPixelCoord(const PointCoord& pointCoord) const;

        Span2D CalculateGraphSpan(const Range2D& pair) const;

        double CalculatePointsPerPixel(const Span2D& span2D, const Magick::Image& image) const;

    };
}}

#endif //RANGED_GRAPH_H
