#include "parse-int.h"

int str::parseInt(std::string source) {
    try {
        int ret = std::stoi(source);
        return ret;
    } catch (...) {
        return -1;
    }
}