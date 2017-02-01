#ifndef HELLO_H
#define HELLO_H

#include <string>

/// Sample Class
/// Example class to make build system (trivially) functional.
class Hello
{
public:
	/// Returns a "Hello, world"-style greeting to the caller
	std::string Greet() const;
};

/// \example ../Tests/Unit/Untitled\ Project/Hello.cpp
/// This is an example of how to use the Hello class.

#endif //HELLO_H