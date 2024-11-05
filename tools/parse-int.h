#ifndef _tools_parse_int_ // Include guards protect from circular dependency injection
#define _tools_parse_int_

#include <string>

namespace str {
    int parseInt(std::string source); // Returns -1 if could not parse a string to an int
}

#endif