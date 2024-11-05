#ifndef _file_write_ // Include guards protect from circular dependency injection
#define _file_write_

#include <string>
#include <stdio.h>
#include <iostream>

namespace fileio {
    void write(std::string path, std::string output);
}

#endif