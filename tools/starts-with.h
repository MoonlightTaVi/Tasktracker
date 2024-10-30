#ifndef _tools_starts_with_
#define _tools_starts_with_

#include <string>
#include <vector>

namespace str {
    bool startsWith(std::string text, std::string left);
    std::string findLeftMatch(std::vector<std::string> &source, std::string left);
}

#endif