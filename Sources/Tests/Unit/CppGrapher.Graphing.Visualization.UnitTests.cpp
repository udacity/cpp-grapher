#include <regex>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Filesystem.h"
#include "Helpers/UserDefinedLiterals.h"

using namespace Magick;

class TestApp : public CppGrapher
{
public:
    Image MakeDefaultGraph()
    {
        return CppGrapher::MakeDefaultGraph();
    }
};

SCENARIO("Graphics tests")
{
    GIVEN("a graphics-enabled app instance")
    {
        auto app = TestApp();
        auto resultFilename = utf8_string(u8"cpp-grapher-output.png");

        WHEN("fed a data file rendering a single pixel at the origin (0, 0)")
        {
            auto filename = utf8_string(u8"cpp-grapher-test.one_pixel");
            auto fileContents = utf8_string(u8"pixel_one, 0 0");
            auto fs = TemporaryFileStream(filename, fileContents);
            auto args = std::vector<utf8_string> {u8"cpp-grapher_via-test-runner", filename};
            //TODO suppress stdout output?
            app.Main(args);

            THEN("a bitmap should be rendered with one pixel set at (0, 0)")
            {
                auto referenceImage = app.MakeDefaultGraph();
                auto resultImage = Image();
                resultImage.read(resultFilename.cpp_str());
                auto distortion = 0.0_f64;
                auto diffImage = referenceImage.compare(resultImage,
                                                        MetricType::AbsoluteErrorMetric,
                                                        &distortion);
                diffImage.write("cpp-grapher-diff.png");
                //assert (count non-black pixels == 1)
            }
        }
    }
}

