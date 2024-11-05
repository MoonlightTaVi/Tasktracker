#ifndef _file_read_ // Include guards protect from circular dependency injection
#define _file_read_

#include <string>
#include <stdio.h>

namespace fileio {
    std::string read(std::string path);
}

#endif