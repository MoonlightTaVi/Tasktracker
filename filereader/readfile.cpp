#include "readfile.h"
#include <fstream>
#include <iostream>

std::string fileio::read(std::string path) {
    std::string ret = "";
    std::ifstream file(path);
    if (file.is_open()) {
        while (file) {
            ret += file.get();
        }
        std::cout << "[INFO] Successfully read data from \"" << path << "\".\n";
    } else {
        std::cerr << "[ERROR] Could not open the file: \"" << path << "\".\n";
    }
    return ret;
}