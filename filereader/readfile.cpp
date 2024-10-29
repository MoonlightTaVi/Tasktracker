#include "readfile.h"
#include <fstream>
#include <string>
#include <iostream>

std::string read(std::string path) {
    std::string ret = "";
    std::ifstream file(path);
    if (file.is_open()) {
        while (file) {
            ret += file.get();
        }
    } else {
        std::cout << "Could not open the file: " << path;
    }
    return ret;
}