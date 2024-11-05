#ifndef _tools_starts_with_ // Include guards protect from circular dependency injection
#define _tools_starts_with_

#include <string>
#include <vector>

namespace str {
    bool startsWith(std::string text, std::string left); // Matches the left characters of the two given strings
    std::string findLeftMatch(std::vector<std::string> &source, std::string left); // Finds a left-match with a first string from a vector
}

#endif