#include "writefile.h"
#include <fstream>
#include <iostream>
#include <filesystem>

void fileio::write(std::string path, std::string output) {
    try {
        if (std::filesystem::remove(path)) {
            std::cout << "[INFO] File \"" << path << "\" was removed for rewriting.\n";
        } else {
            std::cout << "[INFO] File \"" << path << "\" not found.\n";
        }
    } catch (const std::filesystem::filesystem_error &err) {
        std::cerr << "[ERROR] Filesystem error:\n\t" << err.what() << "\n";
    }
    std::ofstream file(path);
    if (file.is_open()) {
        file << output;
        file.close();
        std::cout << "[INFO] Successfully saved data to \"" << path << "\".\n";
    } else {
        std::cerr << "[ERROR] Could not write to file: \"" << path << "\".\n";
    }
}