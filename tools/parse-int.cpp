#include "parse-int.h" // Look at this header for some explanation

int str::parseInt(std::string source) {
    try {
        int ret = std::stoi(source);
        return ret;
    } catch (...) {
        return -1;
    }
}