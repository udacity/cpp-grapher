#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include "tinyutf8.h"

utf8_string FilenameFromPath ( const utf8_string& path )
{
    auto pos = path.find_last_of(U"/\\");
    return pos != utf8_string::npos ? path.substr( pos + 1, utf8_string::npos ) : path;
}

#endif //FILESYSTEM_H
