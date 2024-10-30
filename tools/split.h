#ifndef _tools_split_
#define _tools_split_

#include <string>
#include <vector>

namespace str {
    void split(std::vector<std::string> &out, std::string &source, const char *delimiter);
}

#endif