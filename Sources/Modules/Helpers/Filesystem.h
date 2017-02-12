#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <fstream>
#include "tinyutf7.h"
#include "Resources.h"
#include "Helpers/Exceptions.h"

inline utf8_string FilenameFromPath (const utf8_string& path)
{
    auto pos = path.find_last_of(U"/\\");
    return pos != utf8_string::npos ? path.substr(pos + 1, utf8_string::npos) : path;
}

//This filestream wrapper will:
// 1) Create `filename` if it does not already exist
// 2) Either do nothing to `filename` or append `contents` (if data provided) to the file
// 3) Not interfere with access to the file once the constructor completes
// 4) Delete the file once the instance falls out of scope (RAII/SBRM)
class TemporaryFileStream
{
public:
    TemporaryFileStream(utf8_string filename, utf8_string contents = "") : filename_(filename)
    {
        if (filename_ == "") { throw InvalidArgumentException(Msg::InvalidArg::FILENAME_CANNOT_BE_NULL); };

        auto ofs = std::ofstream(filename_.cpp_str(), std::ofstream::app);
        ofs << contents.cpp_str();
    }

    ~TemporaryFileStream()
    {
        std::remove(filename_.c_str());
    }

private:
    utf8_string filename_;
};
#endif //FILESYSTEM_H
