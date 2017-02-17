#include <regex>
#include <RangedGraph/RangedGraph.h>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Filesystem.h"
#include "Helpers/UserDefinedLiterals.h"

using namespace Magick;
using namespace udacity;
using namespace ranged_graph;

// TestHelper is conditionally defined as a friend class of CppGrapher to permit access to RangedGraph's privates.
// RANGED_GRAPH_ACCESS_PRIVATES preprocessor flag must be defined for the `Tests` target.
// (target_compile_definitions(Tests PRIVATE RANGED_GRAPH_ACCESS_PRIVATES))
class TestHelper
{
public:
    Image MakeDiffImage(Image beforeImage, const Image& afterImage) const
    {
        beforeImage.composite(afterImage, 0, 0, DifferenceCompositeOp);
        return beforeImage;
    }

    std::vector<PixelCoord> EnumerateAllImageDifferences(const Image& diffImage) const
    {
        auto deltas = std::vector<PixelCoord>();
        for (auto y = 0_usz; y < diffImage.rows(); ++y)
        {
            for (auto x = 0_usz; x < diffImage.columns(); ++x)
            {
                auto color = diffImage.pixelColor(x, y);
                if (color != Color(0, 0, 0))
                {
                    deltas.push_back(PixelCoord(x, y));
                }
            }
        }
        return deltas;
    }
};

SCENARIO("Continuous-to-Discrete mapping (CDM) functionality")
{
    GIVEN("a RangedGraph instance")
    {
        auto graph = RangedGraph(RangedGraph::DEFAULT_CANVAS_SIZE, MakeRange2D(-1, 1));
        WHEN("a data point outside of a given graph's range is provided")
        {
            THEN("RangedGraph should throw an exception")
            {
                REQUIRE_THROWS_AS(graph.SetPoint(PointCoord(1, 2), Color(0, 0, 0)), PointOutOfRangeException);
            }
        }
    }

    GIVEN("a RangedGraph instance set to render a net 3x3 (9-pixel) canvas ranging from -1 to 1 on both x and y axes")
    {
        auto helper = TestHelper();
        auto rangedGraph = RangedGraph(std::to_string(RangedGraph::CANVAS_MARGIN_PIXELS * 2 + 3) +
                                           "x" +
                                           std::to_string(RangedGraph::CANVAS_MARGIN_PIXELS * 2 + 3),
                                       MakeRange2D(-1, 1));
        auto beforeImage = rangedGraph.GetCanvas();

        WHEN("rendering a black pixel at point (0,0)")
        {
            rangedGraph.SetPoint(PointCoord(0, 0), Color(0, 0, 0));
            auto afterImage = rangedGraph.GetCanvas();
            auto diffImage = helper.MakeDiffImage(beforeImage, afterImage);
            auto deltas = helper.EnumerateAllImageDifferences(diffImage);

            THEN("the resulting graph should differ from the reference by exactly one pixel")
            {
                REQUIRE(deltas.size() == 1);
            }

            AND_THEN("the differing pixel should be at pixel (1,1)--the center pixel of a 3x3 bitmap")
            {
                auto doubleMargin = RangedGraph::CANVAS_MARGIN_PIXELS * 2;
                REQUIRE(afterImage.rows() - doubleMargin == 3);
                REQUIRE(afterImage.columns() - doubleMargin == 3);
                REQUIRE(diffImage.pixelColor(RangedGraph::CANVAS_MARGIN_PIXELS + 1,
                                             RangedGraph::CANVAS_MARGIN_PIXELS + 1) != Color(0, 0, 0));
            }
        }
    }

    GIVEN("a net 3x3 RangedGraph with 4:3 points per pixel")
    {
        auto helper = TestHelper();
        auto graph = RangedGraph(std::to_string(RangedGraph::CANVAS_MARGIN_PIXELS * 2 + 3) +
                                     "x" +
                                     std::to_string(RangedGraph::CANVAS_MARGIN_PIXELS * 2 + 3),
                                 MakeRange2D(-4, 4));
        auto beforeImage = graph.GetCanvas();

        WHEN("rendering a black pixel at point (-2.5, 1)")
        {
            graph.SetPoint(PointCoord(-2.5, 1), Color(0, 0, 0));
            auto afterImage = graph.GetCanvas();
            auto diffImage = helper.MakeDiffImage(beforeImage, afterImage);
            auto deltas = helper.EnumerateAllImageDifferences(diffImage);

            THEN("the resulting graph should differ from the reference by exactly one pixel")
            {
                REQUIRE(deltas.size() == 1);
            }

            AND_THEN("the differing pixel should be at pixel (0,1) of a 3x3 bitmap")
            {
                auto doubleMargin = RangedGraph::CANVAS_MARGIN_PIXELS * 2;
                REQUIRE(afterImage.rows() - doubleMargin == 3);
                REQUIRE(afterImage.columns() - doubleMargin == 3);
                REQUIRE(diffImage.pixelColor(RangedGraph::CANVAS_MARGIN_PIXELS + 0,
                                             RangedGraph::CANVAS_MARGIN_PIXELS + 1) != Color(0, 0, 0));
            }
        }
    }
}

SCENARIO("Range maker")
{
    GIVEN("an empty list of points to be ranged")
    {
        auto coords = std::vector<PointCoord>();

        WHEN("a range is computed from that list")
        {
            THEN("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(MakeRange2D(coords), InvalidArgumentException);
            }
        }
    }

    GIVEN("a list of one point to be ranged")
    {
        auto coords = std::vector<PointCoord> {PointCoord(1, 2)};
        WHEN("a range is computed from that list")
        {
            auto limits = MakeRange2D(coords);
            THEN("the range should have no span")
            {
                REQUIRE(AreApproxEqual(limits.first.second - limits.first.first, 0_f64));
                REQUIRE(AreApproxEqual(limits.second.second - limits.second.first, 0_f64));
            }

            AND_THEN("attempting to make a graph using a spanless range should throw an exception")
            {
                REQUIRE_THROWS_AS(RangedGraph(RangedGraph::DEFAULT_CANVAS_SIZE, limits), InvalidRangeException);
            }
        }
    }

    GIVEN("a valid list of points to be ranged")
    {
        auto coords = std::vector<PointCoord> {PointCoord(-5, 3),
                                               PointCoord(5, -2),
                                               PointCoord(2.5, -4),
                                               PointCoord(0, 4)};

        WHEN("a range is computed from that list")
        {
            auto limits = MakeRange2D(coords);

            THEN("the mins and maxes of x and y have been correctly determined")
            {
                REQUIRE(AreApproxEqual(limits.first.first, -5_f64)); //x-min
                REQUIRE(AreApproxEqual(limits.first.second, 5_f64)); //x-max
                REQUIRE(AreApproxEqual(limits.second.first, -4_f64)); //y-min
                REQUIRE(AreApproxEqual(limits.second.second, 4_f64)); //y-max
            }
        }
    }
}

SCENARIO("Axes and labels")
{
    GIVEN("a valid RangedGraph with no points rendered")
    {
        auto graph = RangedGraph(RangedGraph::DEFAULT_CANVAS_SIZE, MakeRange2D(-1, 1));

        WHEN("the canvas is examined")
        {
            auto image = graph.GetCanvas();

            THEN("there should be axis lines visible at the graph origin, and at the limit of x and y axes")
            {
                REQUIRE(image.pixelColor(RangedGraph::CANVAS_MARGIN_PIXELS,
                                         image.rows() - RangedGraph::CANVAS_MARGIN_PIXELS) != Color(0xff, 0xff, 0xff));
                REQUIRE(image.pixelColor(image.columns() - RangedGraph::CANVAS_MARGIN_PIXELS,
                                         image.rows() - RangedGraph::CANVAS_MARGIN_PIXELS) != Color(0xff, 0xff, 0xff));
                REQUIRE(image.pixelColor(RangedGraph::CANVAS_MARGIN_PIXELS,
                                         RangedGraph::CANVAS_MARGIN_PIXELS) != Color(0xff, 0xff, 0xff));
            }
        }
    }

    GIVEN("an unlabeled graph with rendered data points")
    {
        auto graph = RangedGraph(RangedGraph::DEFAULT_CANVAS_SIZE, MakeRange2D(-1000000, 1000000));
        graph.SetPoint(PointCoord(-0.5, -0.5), Magick::Color(0xff, 0, 0));
        graph.SetPoint(PointCoord(0.5, 0.5), Magick::Color(0, 0xff, 0));
        auto unlabeledCanvas = graph.GetCanvas();

        WHEN("a legend is rendered")
        {
            graph.AddLegendItem("sample item1", Magick::Color(0, 0, 0xff));
            graph.AddLegendItem("sample item2", Magick::Color(0xff, 0, 0));

            THEN("the legend is visible on the graph")
            {
                auto diffImage = graph.GetCanvas();
                auto changedPixelCount = 0_u64;
                for(auto y = 0_usz; y < diffImage.rows(); ++y)
                {
                    for(auto x = 0_usz; x < diffImage.columns(); ++x)
                    {
                        if(diffImage.pixelColor(x, y) != Magick::Color(0, 0, 0))
                        {
                            ++changedPixelCount;
                        }
                    }
                }
                REQUIRE(changedPixelCount > 0);
            }
        }
    }
}
