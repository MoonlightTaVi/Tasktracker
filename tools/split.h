#ifndef _tools_split_ // Include guards protect from circular dependency injection
#define _tools_split_

#include <string>
#include <vector>

namespace str { // Splits the string to a vector by a char delimiter
    void split(std::vector<std::string> &out, std::string &source, const char *delimiter);
}

#endif