#include "filereader/readfile.h"
#include "json/parameter.h"
#include "json/object.h"
#include <iostream>
#include <string>

int main() {
    try {
        std::string tasks = read("resourses/tasks.json");
        json::Object tasksObj = json::Object();
        int start = 0;
        json::createObject(tasksObj, tasks, start);
        std::cout << tasksObj.toString(0);
        std::cout << "Finished successfully!\n";
    } catch (const std::exception &e) {
        std::cout << "\n" << e.what();
    }
    system("PAUSE");
    return 0;
}