#include "datetime.h"

std::string str::getDateTime() { // A basic function to get a timestamp. Not sure yet, how it works
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    const std::time_t *tempPtr = &t_c;
    std::string temp = std::ctime(tempPtr);
    return temp.replace(temp.length() - 1, 1, "");
}