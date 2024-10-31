#ifndef _core_
#define _core_

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

namespace taskscore {
    class Taskmanager {
        private:
            int counter = 0;
            json::Object tasks = json::Object();
        public:
            Taskmanager();
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