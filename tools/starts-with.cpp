#include "starts-with.h" // Look at this header for some explanation

bool str::startsWith(std::string text, std::string left) {
    const int textLength = text.length();
    const int leftLength = left.length();
    if (textLength < leftLength) {
        return false;
    }
    for (int i = 0; i < leftLength; i++) {
        if (text[i] != left[i]) {
            return false;
        }
    }
    return true;
}

std::string str::findLeftMatch(std::vector<std::string> &source, std::string left) {
    for (std::string item : source) {
        if (str::startsWith(item, left)) {
            return item;
        }
    }
    return "";
}