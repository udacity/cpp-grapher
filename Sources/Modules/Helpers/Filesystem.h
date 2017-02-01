#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <string>

std::string FilenameFromPath ( const std::string& path )
{
    auto pos = path.find_last_of("/\\");
    return pos != std::string::npos ? path.substr( pos + 1 ) : path;
}

#endif //FILESYSTEM_H
