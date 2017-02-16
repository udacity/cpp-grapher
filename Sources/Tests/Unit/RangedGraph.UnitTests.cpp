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
    GIVEN("an app instance")
    {
        auto app = CppGrapher();
        WHEN("a data point outside of a given graph's range is provided")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher-test_input.valid-data");
            auto fileContents = utf8_string(u8"test_name 1.0 2.0");
            auto outputFilename = utf8_string(u8"cpp-grapher-test_output");

            auto ifs = TemporaryFileStream(inputFilename, fileContents);
            auto ofs = TemporaryFileStream(outputFilename);

            auto args = std::vector<utf8_string> {u8"cpp-grapher-test",
                                                  inputFilename,
                                                  outputFilename};

            THEN("the app should throw an exception")
            {
                REQUIRE_THROWS_AS(app.Main(args), PointOutOfRangeException);
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
        auto beforeImage = rangedGraph.GetImage();

        WHEN("rendering a black pixel at point (0,0)")
        {
            rangedGraph.SetPoint(PointCoord(0, 0), Color(0, 0, 0));
            auto afterImage = rangedGraph.GetImage();
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
        auto beforeImage = graph.GetImage();

        WHEN("rendering a black pixel at point (-2.5, 1)")
        {
            graph.SetPoint(PointCoord(-2.5, 1), Color(0, 0, 0));
            auto afterImage = graph.GetImage();
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

    GIVEN("a valid list of points to be ranged")
    {
        auto helper = TestHelper();
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
        auto helper = TestHelper();
        auto graph = RangedGraph(RangedGraph::DEFAULT_CANVAS_SIZE, MakeRange2D(-1, 1));

        WHEN("the canvas is examined")
        {
            auto image = graph.GetImage();

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
}
