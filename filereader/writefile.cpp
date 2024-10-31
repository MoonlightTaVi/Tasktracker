#include "writefile.h"
#include <fstream>
#include <filesystem>

void fileio::write(std::string path, std::string output) {
    try {
        if (std::filesystem::remove(path)) {
            printf("[INFO] File \"%s\" was removed for rewriting.\n", path.c_str());
        } else {
            printf("[INFO] File \"%s\" not found.\n", path.c_str());
        }
    } catch (const std::filesystem::filesystem_error &err) {
        std::cerr << "[ERROR] Filesystem error:\n\t" << err.what() << "\n";
    }
    std::ofstream file(path);
    if (file.is_open()) {
        file << output;
        file.close();
        printf("[INFO] Successfully saved data to \"%s\".\n", path.c_str());
    } else {
        printf("[ERROR] Could not write to file: \"%s\".\n", path.c_str());
    }
}