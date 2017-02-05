#include "CppGrapher.h"

using namespace Magick;

Image CppGrapher::MakeBlankGraph(std::string size = DEFAULT_GRAPH_SIZE)
{
    auto image = Image(size.c_str(), "white");
    return image;
}

