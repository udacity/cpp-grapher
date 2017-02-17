#include <iostream>
#include <vector>
#include <cmath>
#include "Helpers/Filesystem.h"

#include "CppGrapher.h"

using namespace Magick;
using namespace udacity;
using namespace ranged_graph;

int CppGrapher::Main(const std::vector<utf8_string>& args)
{
    ValidateArgs(args);
	auto dataPoints = DeserializeDataPoints(args[ArgsIndexNames::INPUT_FILENAME]);
    auto graph = GraphDataPoints(dataPoints);

    //Write file to disk and stream base64 version to stdout
    graph.write(EnsureFilenameEndsWithPng(args[ArgsIndexNames::OUTPUT_FILENAME]).cpp_str());

    Blob blob;
    graph.magick("PNG");
    graph.write(&blob);
    std::cout << blob.base64() << std::flush;

  	return EXIT_SUCCESS;
}

utf8_string CppGrapher::EnsureFilenameEndsWithPng(utf8_string filename)
{
    const auto PNG_SUFFIX = utf8_string(u8".png");
    auto suffix = filename.substr(filename.length() - PNG_SUFFIX.length(), PNG_SUFFIX.length());
    if(suffix != PNG_SUFFIX)
    {
        filename += PNG_SUFFIX;
    }

    return filename;
}
