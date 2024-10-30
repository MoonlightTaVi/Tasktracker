#include "split.h"

void str::split(std::vector<std::string> &out, std::string &source, const char *delimiterPointer) {
    out.clear();
    std::string currentItem = "";
    const char delimiter = *delimiterPointer;
    for (const char c : source) {
        if (c == delimiter) {
            out.push_back(currentItem);
            currentItem = "";
        } else {
            currentItem += c;
        }
    }
    if (currentItem != "") {
        out.push_back(currentItem);
    }
}