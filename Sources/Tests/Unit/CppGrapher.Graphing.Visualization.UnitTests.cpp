#include <regex>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Filesystem.h"
#include "Helpers/UserDefinedLiterals.h"

using namespace Magick;

// TestSpyApp is conditionally defined as a friend class of CppGrapher to permit access to CppGrapher's privates.
// CPP_GRAPHER_COMPILE_TESTS preprocessor flag must be defined for the `Tests` target.
// One way to accomplish this (in Tests/CMakeLists.txt):
//      target_compile_definitions(Tests PRIVATE CPP_GRAPHER_COMPILE_TESTS)
class TestSpyApp : public CppGrapher
{
public:
    using PointDelta = std::tuple<double, double, Color>; //(x, y, color)

    Image MakeBlankGraph(const std::string& sizeDesc = CppGrapher::DEFAULT_GRAPH_SIZE) const
    {
        return CppGrapher::MakeBlankGraph(sizeDesc);
    }

    std::vector<KalmanFilterDataPoint> DeserializeDataPoints(const utf8_string& filename) const
    {
        return CppGrapher::DeserializeDataPoints(filename);
    }

    Image GraphDataPoints(const std::vector<KalmanFilterDataPoint>& dataPoints) const
    {
        return CppGrapher::GraphDataPoints(dataPoints);
    }

    std::vector<PointDelta> FindAllPixelDeltas(Image diffImage, Image compareImage)
    {
        diffImage.composite(compareImage, 0, 0, DifferenceCompositeOp);
        auto deltas = std::vector<PointDelta>();
        for (auto y = 0_usz; y < diffImage.rows(); ++y)
        {
            for (auto x = 0_usz; x < diffImage.columns(); ++x)
            {
                auto color = diffImage.pixelColor(x, y);
                if (color != Color(0, 0, 0))
                {
                    deltas.push_back(std::make_tuple(x, y, color));
                }
            }
        }

        //DEBUG TODO: Remove
        diffImage.write("cpp-grapher_diff.png");

        return deltas;
    }
};

SCENARIO("Graphics tests")
{
    GIVEN("a graphics-enabled app instance")
    {
        auto app = TestSpyApp();

        WHEN("fed a data file rendering a single black pixel at the origin (0, 0)")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher_test_input.one_pixel");
            auto outputFilename = utf8_string(u8"cpp-grapher_test_output.png");
            auto fileContents = utf8_string(u8"pixel_one, 0 0");
            auto fs = TemporaryFileStream(inputFilename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner",
                                                  inputFilename.cpp_str(),
                                                  outputFilename.cpp_str()};

            THEN("a the resulting graph should differ from the original by exactly one white pixel set at (0, 0)")
            {
                auto referenceImage = app.MakeBlankGraph();
                auto editedImage = app.GraphDataPoints(app.DeserializeDataPoints(inputFilename));

                auto deltas = app.FindAllPixelDeltas(referenceImage, editedImage);
                REQUIRE(deltas.size() == 1);
                REQUIRE(deltas[0] == std::make_tuple(0, 0, Color(0xff, 0xff, 0xff)));

                //DEBUG TODO: Remove
                referenceImage.write("cpp-grapher_reference.png");
                editedImage.write("cpp-grapher_edited.png");
            }
        }
    }
}

