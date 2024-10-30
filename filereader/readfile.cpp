#include "readfile.h"
#include <fstream>
#include <string>
#include <iostream>

std::string fileio::read(std::string path) {
    std::string ret = "";
    std::ifstream file(path);
    if (file.is_open()) {
        while (file) {
            ret += file.get();
        }
        std::cout << "Successfully read data from \"" << path << "\".\n";
    } else {
        std::cerr << "Could not open the file: \"" << path << "\".\n";
    }
    return ret;
}