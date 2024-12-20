#include "core/tasktracker.h" // This has all the neccessary includes

int main() {
    try {
        tasks::Tasktracker tracker = tasks::Tasktracker(); // This is the main class
        std::string command = "";
        std::cout << "Type \"quit\" to quit the programm." << std::endl << std::endl;
        while (true) {
            try {
                std::cout << "task-cli >>> ";
                std::getline(std::cin, command); // getline allows multi-word input
                if (!str::startsWith(command, "quit")) {
                    tracker.execute(command); // The method to process the input
                    std::cout << std::endl;
                } else { // Break the loop on "quit"
                    break;
                }
            } catch (const std::exception &err) {
                std::cerr << "[ERROR] Encountered error when processing the command:\n\t" << err.what() << "\n";
            }
        }
    } catch (const std::exception &err) {
        std::cerr << "[ERROR] Encountered error during initialization:\n\t" << err.what() << "\n";
    }
    return 0;
}

void testJson() {
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
}

void testSplit() {
    std::vector<std::string> split = {};
    std::string toSplit = "abc cba xyz";
    str::split(split, toSplit, " ");
    for(std::string item : split) {
        std::cout << item << "\n";
    }
    system("PAUSE");
}

void testMatch() {
    std::vector<std::string> split = {};
    std::string toSplit = "first second secspam";
    str::split(split, toSplit, " ");
    std::cout << str::findLeftMatch(split, "sec") << "\n";
    system("PAUSE");
}