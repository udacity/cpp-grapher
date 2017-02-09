#ifndef CPP_GRAPHER_H
#define CPP_GRAPHER_H

#include <vector>
#include <fstream>
#include "Magick++.h"

//save compiler switches - external libs often can't handle ultra-strict compiler settings
#include "tinyutf8.h"

/// The application logic is written as a library to enable flexible packaging (static or dynamic linking) and
/// execution from a test runner, application driver (this class), or other driver.  Entry point for execution is
/// Main().
struct KalmanFilterDataPoint
{
    utf8_string name;
    double x, y;
};

class CppGrapher
{
public:
    /// Main() is the application entry (starting) point.
    ///
    /// The traditional C-style practice of using argv + argc is an example of a "buffer + length" anti-pattern.
    /// Because the two must be manually coupled, this pattern has not only been shown to be a source of bugs (eg.
    /// off-by-one errors or buffer-a + length-of-buffer-b-errors) but also a security vulnerability (whenever the two
    /// are misaligned, we risk enabling an exploit).  Using a buffer which manages its own length (ie. std::vector)
    /// ensures these kinds of issues cannot happen.
    ///
    /// All strings managed by this app are strongly-typed UTF-8 strings, which permit the use and proper operation
    /// of any Unicode code point.  All operations on strings are Unicode-compliant, except for equality, which will
    /// only perform a literal compare, not a Unicode-semantic compare (the latter is when a set of code points is
    /// considered equal to some other code point or set of code points).
    ///
    /// No C or C++ string operators are UTF-8-aware, and ignoring this can lead to both surprising and incorrect
    /// behavior with the added bonus of the problem being completely silent (until it manifests in some way).
    /// To deal with this, this application uses a strongly-typed UTF-8 string class to prevent accidental use of
    /// non-UTF-8-aware string manipulation functionality.
    ///
    /// Note: this kind of issue is known as semantic types and can lead to real issues when ignored or not properly
    /// handled (eg. http://www.cnn.com/TECH/space/9909/30/mars.metric.02)
    ///
    /// @param args[in]         A vector of UTF-8 strings representing the arguments given to the program.
    ///                         Note: the system always provides the application's name as args[0].
    /// @returns                Execution status code (typically EXIT_SUCCESS, as App will throw if it encounters an
    ///                         error).
    /// @throws                 May throw any std::exception listed by any method in the CppGrapher class (see below).
    int Main(const std::vector<utf8_string>& args);

private:
//Conditionally grant test framework access to privates
#ifdef CPP_GRAPHER_COMPILE_TESTS
    friend class TestHelper;
#endif

    /// Enum mapping argument position to argument meaning, plus argument count sentinel.
    enum ArgsIndexNames : size_t
    {
        APPLICATION_FILENAME = 0,
        INPUT_FILENAME = 1,
        OUTPUT_FILENAME = 2,
        REQUIRED_ARGUMENT_COUNT = 3
    };

    /// Ensure expected/required arguments have been received.
    ///
    /// @param args[in]         A vector of UTF-8 strings representing the arguments given to the program.
    /// @returns                A 3-element tuple containing UTF-8 strings representing:
    ///                             1) this application's filename,
    ///                             2) the requested input filename expected to Kalman Filter data points and
    ///                             3) the output file representing a graph of those points, respectively.
    /// @throws                 Typically, InvalidArgumentException.
    void ValidateArgs(const std::vector<utf8_string>& args) const;

    /// Deserialize a data file--expected to be a series of whitespace-delimited elements of type
    /// string double double, one set of elements per line.
    ///
    /// Note: This method will (attempt to) deserialize the entire data file into a memory-resident structure before
    /// processing begins.
    ///
    /// @param filename[in]     A UTF-8 string representing the name of the file to be deserialized.
    /// @returns                A vector of KalmanFilterDataPoints representing the deserialized file.
    /// @throws                 Typically, FileNotFoundException, NoDataFoundException, plus any exceptions thrown by
    ///                         CppGrapher::ParseKalmanFilterPoint() and CppGrapher::FindNextToken().
    std::vector<KalmanFilterDataPoint> DeserializeDataPoints(const utf8_string& filename) const;

    /// Deserialize one line of the data file--expected to be a string, a double and another double delimited by
    /// whitespace.  All three data elements are expected to be on the same line.  Additional data elements on the
    /// same line will be ignored.
    ///
    /// @param line[in]         A UTF-8 string containing the line of the file to be processed.
    /// @returns                A KalmanFilterDataPoint
    /// @throws                 Typically, any exceptions thrown by CppGrapher::FindNextToken().
    KalmanFilterDataPoint DeserializeDataLine(const utf8_string& line) const;

    /// Deserialize the first non-whitespace data element found starting at pos and return it as a string
    ///
    /// @param line[in]         A UTF-8 string containing the line of the file to be processed.
    /// @param pos[in,out]      Read as the starting codepoint index into line to begin token search.  Written as
    ///                         the codepoint index (one-past-the-end, as per all C++ end iterators) of the found
    ///                         token.
    /// @returns                The found token, returned as a string.
    /// @throws                 Typically, any exceptions thrown by CppGrapher::FindNextToken().
    utf8_string DeserializeDataName(const utf8_string& line, utf8_string::size_type& pos) const;

    /// Deserialize the first non-whitespace data element found starting at pos and return it as a
    /// double (IEEE-754 double-precision floating point value).
    ///
    /// @param line[in]         A UTF-8 string containing the line of the file to be processed.
    /// @param pos[in,out]      Read as the starting codepoint index into line to begin token search.  Written as
    ///                         the codepoint index (one-past-the-end, as per all C++ end iterators) of the found
    ///                         token.
    /// @returns                The found token, returned as a double.
    /// @throws                 Typically, BadDataException plus any exceptions thrown by CppGrapher::FindNextToken().
    double DeserializeDataPoint(const utf8_string& line, utf8_string::size_type& pos) const;

    /// Find the bounds of the next contiguous block on non-whitespace data starting at codepoint index pos and return
    /// it as a half-open range in a 2-element tuple (start-index, one-past-end-index).
    ///
    /// @param line[in]         A UTF-8 string containing the line of the file to be processed.
    /// @param pos[in,out]      Read as the starting codepoint index into line to begin the token search.  Written as
    ///                         the codepoint index (one-past-the-end, as per all C++ end iterators) of the found
    ///                         token.
    /// @returns                The codepoint (not byte!) range of the found token, returned as a half-open range--from
    ///                         start-index (inclusive) to end-index (exclusive).
    /// @throws                 Typically, TokenNotFoundException.
    std::tuple<utf8_string::size_type, utf8_string::size_type> LocateNextToken(const utf8_string& line,
                                                                               utf8_string::size_type& pos) const;

    /// Create an empty ranged graph with indexed axes.  A ranged graph is a Magick::Image with an associated
    /// position and scale.  (This means all points within the graph's x and y range boundaries will map to a pixel in
    /// the bitmap.)
    ///
    /// @param pixelSizeDesc    A "width x height" (or "widthxheight") string accepted by ImageMagick to determine
    ///                         the pixel dimensions of the ranged graph bitmap.
    /// @returns                A ranged bitmap
    //Magick::Image MakeGraphCanvas(const std::string& pixelSizeDesc = DEFAULT_GRAPH_CANVAS_SIZE) const;

    /// Iterates through the provided collection of data points and places a colored pixel on the provided ranged graph
    /// for each data point in the list.  This method automatically uses a unique color for each different
    /// KalmanFilterDataPoint.name and renders a translucent legend to decode the name/color mappings.
    ///
    /// @param dataPoints[in]   Collection of data points to be rendered.
    /// @param inGraph[in]      Ranged graph (ie. bitmap canvas) serving as the template graph for rendering data
    ///                         points to.
    /// @returns                Ranged graph with data points and legend rendered.
    Magick::Image GraphDataPoints(const std::vector<KalmanFilterDataPoint>& dataPoints) const;
};

/// @example ../Tests/Unit/Lib.UnitTests.cpp
/// This is an example of how to use the CppGrapher class.

#endif //CPP_GRAPHER_H
