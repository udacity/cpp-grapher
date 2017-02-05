#include <regex>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Filesystem.h"
#include "Helpers/UserDefinedLiterals.h"

using namespace Magick;

class TestApp : public CppGrapher
{
public:
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
};

SCENARIO("Graphics tests")
{
    GIVEN("a graphics-enabled app instance")
    {
        auto app = TestApp();

        WHEN("fed a data file rendering a single pixel at the origin (0, 0)")
        {
            auto inputFilename = utf8_string(u8"cpp-grapher_test_input.one_pixel");
            auto outputFilename = utf8_string(u8"cpp-grapher_test_output.png");
            auto fileContents = utf8_string(u8"pixel_one, 0 0");
            auto fs = TemporaryFileStream(inputFilename, fileContents);

            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner",
                                                  inputFilename.cpp_str(),
                                                  outputFilename.cpp_str()};

            THEN("a bitmap should be rendered with exactly one pixel set at (0, 0)")
            {
                auto referenceImage = app.MakeBlankGraph();
                auto editedImage = app.GraphDataPoints(app.DeserializeDataPoints(inputFilename));
                auto diffImage = Image(referenceImage);
                diffImage.composite(editedImage, 0, 0, DifferenceCompositeOp);

                auto deltas = std::vector<std::tuple<size_t, size_t>>();
                for(auto y = 0_usz; y < diffImage.rows(); ++y)
                {
                    for(auto x= 0_usz; x < diffImage.columns(); ++x)
                    {
                        if(diffImage.pixelColor(x, y) != Color(0,0,0))
                        {
                            deltas.push_back(std::make_tuple(x, y));
                        }
                    }
                }

                REQUIRE(deltas.size() == 1);
                REQUIRE(deltas[0] == std::make_tuple(0_usz, 0_usz));

                //DEBUG
                referenceImage.write("cpp-grapher_reference.png");
                editedImage.write("cpp-grapher_edited.png");
                diffImage.write("cpp-grapher_diff.png");
            }
        }
    }
}

