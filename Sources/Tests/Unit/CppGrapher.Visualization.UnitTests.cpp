#include <regex>
#include "catch.hpp"
#include "CppGrapher.h"
#include "Helpers/Exceptions.h"
#include "Helpers/Filesystem.h"

using namespace udacity;
using namespace ranged_graph;

class TestHelper : CppGrapher
{
public:
    Magick::Color GetUniqueColor()
    {
        return CppGrapher::GetUniqueColor();
    }

    void ValidateArgs(std::vector<utf8_string> args)
    {
        CppGrapher::ValidateArgs(args);
    }

    std::vector<KalmanFilterDataPoint> DeserializeDataPoints(utf8_string filename)
    {
        return CppGrapher::DeserializeDataPoints(filename);
    }

    Magick::Image GraphDataPoints(std::vector<KalmanFilterDataPoint> dataPoints)
    {
        return CppGrapher::GraphDataPoints(dataPoints);
    }
};

SCENARIO("Generating colors")
{
    GIVEN("an app instance")
    {
        auto app = TestHelper();

        WHEN("one color is requested")
        {
            auto color = app.GetUniqueColor();

            THEN("it should provide a color, not black or white or any shade of gray (neutrals reserved for graph itself)")
            {
                REQUIRE(!(color.quantumRed() == color.quantumGreen() &&
                          color.quantumGreen() == color.quantumBlue()));
            }
        }

        WHEN("a number of colors are requested")
        {
            auto requestColorCount = 1000;
            auto requestedColors = std::vector<Magick::Color>();

            THEN("every color returned should be unique")
            {
                for(auto i = 0_usz; i < requestColorCount; ++i)
                {
                    auto color = app.GetUniqueColor();
                    REQUIRE(std::find(std::begin(requestedColors), std::end(requestedColors), color) == std::end(requestedColors));
                    requestedColors.push_back(Magick::Color(color));
                }
            }
        }
    }
}
