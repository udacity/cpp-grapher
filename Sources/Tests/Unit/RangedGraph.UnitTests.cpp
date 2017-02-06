#include <regex>
#include <RangedGraph/RangedGraph.h>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Filesystem.h"
#include "Helpers/UserDefinedLiterals.h"

using namespace Magick;

using PointDelta = std::tuple<double, double, Color>;
enum PointDeltaIdxNames : size_t {X = 0, Y = 1, COLOR = 2};

// TestHelpers is conditionally defined as a friend class of CppGrapher to permit access to CppGrapher's privates.
// CPP_GRAPHER_COMPILE_TESTS preprocessor flag must be defined for the `Tests` target.
// One way to accomplish this (in Tests/CMakeLists.txt):
//      target_compile_definitions(Tests PRIVATE CPP_GRAPHER_COMPILE_TESTS)
class TestHelpers : public CppGrapher
{
public:

    std::vector<PointDelta> FindAllPixelDeltas(Image image1, Image image2)
    {
        image1.composite(image2, 0, 0, DifferenceCompositeOp);
        auto deltas = std::vector<PointDelta>();
        for (auto y = 0_usz; y < image1.rows(); ++y)
        {
            for (auto x = 0_usz; x < image1.columns(); ++x)
            {
                auto color = image1.pixelColor(x, y);
                if (color != Color(0, 0, 0))
                {
                    deltas.push_back(std::make_tuple(x, y, color));
                }
            }
        }

        //DEBUG TODO: Remove
        image1.write("cpp-grapher_diff.png");

        return deltas;
    }
};

SCENARIO("Basic functionality")
{
    GIVEN("a RangedGraph instance set to render a 3x3 (9-pixel) canvas ranging from -1 to 1 (x and y axes)")
    {
        auto helpers = TestHelpers();
        auto graph = RangedGraph("3x3", Range(-1, 1), Range(-1, 1));
        auto referenceImage = graph.GetImage();

        WHEN("rendering a black pixel at (0,0)")
        {
            graph.SetPoint(0, 0, Color(0, 0, 0));
            auto graphImage = graph.GetImage();
            auto deltas = helpers.FindAllPixelDeltas(referenceImage, graphImage);

            THEN("the resulting graph should differ from the reference by exactly one pixel")
            {
                REQUIRE(deltas.size() == 1);
            }

            AND_THEN("the delta pixel should be white")
            {
                auto diffColor = std::get<PointDeltaIdxNames::COLOR>(deltas[0]);
                REQUIRE(diffColor == Color(0xff, 0xff, 0xff));
            }

            AND_THEN("the point coordinate of the differing pixel should be (x,y) = (0,0)")
            {
                auto x = std::get<PointDeltaIdxNames::X>(deltas[0]);
                auto y = std::get<PointDeltaIdxNames::Y>(deltas[0]);
                REQUIRE(AreApproxEqual(x, 0_f64));
                REQUIRE(AreApproxEqual(y, 0_f64));
            }

            AND_THEN("the differing pixel should be at pixel coordinate (1,1)--the center pixel of a 3x3 bitmap")
            {
                REQUIRE(graphImage.rows() == 3);
                REQUIRE(graphImage.columns() == 3);
                REQUIRE(graphImage.pixelColor(1, 1) == Color(0xff, 0xff, 0xff));
            }
        }
    }
}
