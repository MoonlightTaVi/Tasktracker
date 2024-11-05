#ifndef _core_ // Include guards protect from circular dependency injection
#define _core_

// All the includes
#include "../json/parameter.h"
#include "../filereader/readfile.h"
#include "../filereader/writefile.h"
#include "../tools/split.h"
#include "../tools/starts-with.h"
#include "../tools/parse-int.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>

namespace tasks {
    class Tasktracker {
        private:
            int counter = 0; // Overall number of tasks (including deleted, needed for the new task ID calculation)
            json::Object tasks = json::Object();
        public:
            Tasktracker(); // Look at tasktracker.cpp for realization
            void execute(std::string line);
            void addTask(std::string description);
            void updateTask(std::string id, std::string description);
            void deleteTask(std::string id);
            void markTask(std::string id, std::string status);
            void listTasks(std::string filter);
            void save();
    };
}

#endif