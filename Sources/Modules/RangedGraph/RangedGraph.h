#ifndef RANGED_GRAPH_H
#define RANGED_GRAPH_H

#include <cmath>
#include <Magick++/Color.h>
#include <Magick++/Image.h>
#include "Helpers/UserDefinedLiterals.h"

using Range = std::tuple<double, double>;
enum RangeIdxNames: size_t { BEG = 0, END = 1 };

template<typename T>
bool AreApproxEqual(T f1, T f2);

class RangedGraph
{
public:
    RangedGraph(std::string pixelSizeDesc, Range xRange = std::make_tuple(-1_f64, 1_f64),
                                           Range yRange = std::make_tuple(-1_f64, 1_f64));
    RangedGraph SetPoint(const double pointX, const double pointY, const Magick::Color& color);
    std::tuple<double, double, Magick::Color> GetPixel(double x, double y);

    Magick::Image GetImage() const;

private:
//Conditionally grant test framework access to privates
#ifdef CPP_GRAPHER_COMPILE_TESTS
    friend class TestHelpers;
#endif

    Range xRange;
    Range yRange;
    Magick::Image graph;

    RangedGraph ValidateRange(Range tuple);

    Range CenterRange(const std::tuple<double, double>& range, const double span) const;

    Magick::Image MakeBlankGraph(const std::string& pixelSizeDesc) const;
};

#endif //RANGED_GRAPH_H
