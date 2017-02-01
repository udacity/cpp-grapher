#include "Lib.h"

#include <limits>

std::string Hello::Greet() const
{
	return "Hello " + std::to_string(std::numeric_limits<size_t>::digits) + "-bit World!\n";
}
