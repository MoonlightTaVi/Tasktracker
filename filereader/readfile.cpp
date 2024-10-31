#include "readfile.h"
#include <fstream>

std::string fileio::read(std::string path) {
    std::string ret = "";
    std::ifstream file(path);
    if (file.is_open()) {
        while (file) {
            ret += file.get();
        }
        printf("[INFO] Successfully read data from \"%s\".\n", path.c_str());
    } else {
        printf("[INFO] Could not open the file: \"%s\" (probably does not exist).\n", path.c_str());
    }
    return ret;
}