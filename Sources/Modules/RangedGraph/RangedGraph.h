#ifndef RANGED_GRAPH_H
#define RANGED_GRAPH_H

#include <cmath>
#include <iostream>
#include <Magick++.h>
#include "Helpers/Exceptions.h"
#include "Helpers/Resources.h"
#include "Helpers/UserDefinedLiterals.h"

static_assert(sizeof(long double) > sizeof(double), "RangedGraph requires support for extended-precision floating \
    point to operate correctly.  Extended-precision is not supported by your compiler and/or hardware platform.");

//Forward declaration required to conditionally grant test framework access to privates
#ifdef TEST_HELPER_ACCESS_PRIVATES
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
    using PixelSpan2D = std::pair<size_t, size_t>;

     /// Ensures a double is a value; throws if it is a not-a-number or infinity.
     /// @param n[in]                       The value to be validated.
     ///@throws InvalidArgumentException    If the value is outside the range of valid values (ie. a NaN or infinity).
    inline void ValidateDouble(const double n)
    {
        if(!(n >= std::numeric_limits<double>::lowest() && n <= std::numeric_limits<double>::max())) //NaN, +/-infinity
        {
            throw InvalidArgumentException(Msg::InvalidArg::INVALID_DOUBLE_RECEIVED);
        }
    }

    /// Convenience function to generate a 2D range of values; suitable for use with RangedGraph's constructor.
    /// @param xMin                 Minmum x-coordinate value in the set to be graphed.
    /// @param xMax                 Maximum x-coordinate value in the set to be graphed.
    /// @param yMin                 Minimum y-coordinate value in the set to be graphed.
    /// @param yMax                 Maximum y-coordinate value in the set to be graphed.
    /// @returns                    A 2D Range representing the span of x and y coordinate values to be graphed.
    inline Range2D MakeRange2D(const double xMin, const double xMax, const double yMin, const double yMax)
    {
        ValidateDouble(xMin);
        ValidateDouble(xMax);
        ValidateDouble(yMin);
        ValidateDouble(yMax);

        return Range2D(Range(xMin, xMax), Range(yMin, yMax));
    }

    /// Convenience function to generate a 2D graph from a pair of values; suitable for use with RangedGraph's
    /// constructor.
    /// @param min                  Minimum x- and y-coordinate values in the set to be graphed.
    /// @param max                  Maximum x- and y-coordinate values in the set to be graphed.
    /// @returns                    A 2D Range representing the span of x and y coordinate values to be graphed.
    inline Range2D MakeRange2D(const double min, const double max)
    {
        return MakeRange2D(min, max, min, max);
    }

    /// Floating point numbers (single, double or extended-precision) cannot be reliably compared for equality.  This is
    /// because the least significant digits are subject to variance from implementation issues and rounding error.
    /// To reliably compare floating point numbers a little 'wiggle room' should be given.  Values within this
    /// specified tolerance (epsilon) are considered equal.
    template<typename T>
    bool AreApproxEqual(T f1, T f2);

    /// A pixel canvas behind a continuous-to-discrete mapping (CDM) layer. It will map points at any scale
    /// representable by IEEE-754 double precision floating point value to the requested sized canvas.
    class RangedGraph
    {
    public:
        /// Default graph size convenience constant (in pixels).  Defined in RangedGraph.cpp.  To be consumed directly by
        /// ImageMagick.
        static const std::string DEFAULT_CANVAS_SIZE;
        static const Magick::Color DEFAULT_CANVAS_COLOR;
        static const Magick::Color DEFAULT_AXIS_COLOR;
        static const size_t CANVAS_MARGIN_PIXELS;

        /// Constructor.
        /// @param graphCanvasSize  Accepting a std::string of the form "wxh" where w is the width of of the graph and
        ///                         h is the height of the graph in pixels (eg. "1280x720").
        /// @param graphRange       A Range2D which represents the min and max x and y values to be represented by the
        ///                         graph.  MakeRange2D() is a convenience function provided to construct Range2D's.
        /// @throws                 May throw any std::exception listed by any method in the RangedGraph class.
        RangedGraph(const std::string graphCanvasSize, const Range2D& graphRange);

        /// Writes a pixel to the graph in the specified color, mapping the point coordinate to a pixel coordinate
        /// according to the graph's set x and y scale as set by graphRange specified in the class' constructor.
        /// @param point            A continuous-domain x and y coordinate to be rendered.
        /// @param color            The color to draw the pixel corresponding to the specified point.
        /// @returns                The current instance of the class to enable a fluent API.
        RangedGraph SetPoint(const PointCoord& point, const Magick::Color& color);

        /// Returns a copy of the class' image buffer to the caller.
        /// @returns                A copy of the RangedGraph's internal image buffer.
        Magick::Image GetImage() const;

    private:
//Conditionally grant test framework access to privates
#ifdef TEST_HELPER_ACCESS_PRIVATES
        friend class ::TestHelper;
#endif
        long double pointsPerPixel_;
        Range2D range2D_;
        Magick::Image canvas_;

        //Ensure a given Range2D contains no null ranges
        RangedGraph ValidateGraphRange(const Range2D& GraphPointRange) const;

        //Ensure a given Range is not null
        RangedGraph ValidateRange(const Range& pointRange) const;

        //Given an aspect ratio of the graph image buffer and Range2D may differ, the mapping will ensure no clipping
        //by using the axis requiring the smallest scale as the scale for the entire range against the bitmap.  This
        //may leave freedom on the other axis, which, if true, will be modified so as to be centered for aesthetics.
        Range2D MakeCenteredGraphRange(const Range2D& range2D, const Span2D& span2D, const double pointsPerPixel,
                                       const Magick::Image& image) const;

        //Creates the ImageMagick canvas
        Magick::Image MakeGraphCanvas(const std::string& graphCanvasSize, const Magick::Color& canvasColor) const;

        //Ensures the canvas has positive dimensions on both axes.
        RangedGraph ValidateGraph(const Magick::Image& canvas) const;

        //Ensures the requested point translated by the scale indicated by Range2D set in the constructor actually maps
        //to a pixel within the canvas boundaries.
        RangedGraph ValidatePointInGraph(const PointCoord& pointCoord) const;

        //Central location where the computation to translate between continuous points and discrete pixels at a scale
        //controlled by Range2D is performed.
        PixelCoord ConvertPointToPixelCoord(const PointCoord& pointCoord) const;

        //Central location to calculate the span (absolute distance) between min and max values on x and y axes
        Span2D CalculateGraphSpan(const Range2D& pair) const;

        //Central location indicating the scale (in points per pixels) required to map the given Span2D to the given
        //image canvas
        double CalculatePointsPerPixel(const Span2D& span2D, const Magick::Image& canvas) const;

        //Render x and y axes onto the graph canvas
        void RenderAxes(Magick::Image& canvas, const Magick::Color& axisColor, const Range2D& range2D) const;
    };
}}

#endif //RANGED_GRAPH_H
