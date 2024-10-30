#include "filereader/readfile.h"
#include "filereader/writefile.h"
#include "json/parameter.h"
#include <iostream>
#include <string>

int main() {
    try {
        std::string tasks = fileio::read("resourses/tasks.json");
        json::Object tasksObj = json::Object();
        int start = 0;
        json::createObject(tasksObj, tasks, start);
        std::cout << tasksObj.toString(0);
        std::cout << "Step 1 finished successfully!\n";
        std::string stringifyed = tasksObj.stringify();
        std::cout << "Stringified: " << stringifyed << "\n";
        fileio::write("tasks.json", stringifyed);
        std::cout << "Step 2 finished successfully!\n";

        std::string tasksTemp = fileio::read("tasks.json");
        json::Object tasksObjTemp = json::Object();
        start = 0;
        json::createObject(tasksObjTemp, tasksTemp, start);
        std::cout << tasksObjTemp.toString(0);
        std::cout << "Programm finished successfully!\n";
    } catch (const std::exception &e) {
        std::cout << "\n" << e.what();
    }
    system("PAUSE");
    return 0;
}