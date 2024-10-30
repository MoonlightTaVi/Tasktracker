#include "tasktracker.h"

taskscore::Taskmanager::Taskmanager() {
    std::string readfile = fileio::read("tasks.json");
    this->tasks = json::Object();
    if (readfile != "") {
        int start = 0;
        json::createObject(this->tasks, readfile, start);
    }
    if (!this->tasks.has("counter")) {
        if (readfile != "") {
            std::cerr << "\"tasks.json\" seems to be corrupted (no task counter). Unexpected behaviour may happen.\n";
        }
        json::Parameter counter = json::Parameter(0);
        json::Parameter *counterPtr = &counter;
        this->tasks.add("counter", counterPtr);
    }
    this->counter = this->tasks.get("counter")->getIntValue();
}

void taskscore::Taskmanager::execute(std::string line) {
    std::vector<std::string> commands = {"new", "update", "delete", "start", "done", "list"};
    std::vector<std::string> split = {};
    str::split(split, line, " ");
    if (split.size() == 0) {
        std::cerr << "No command given.\n";
        return;
    }
    std::string command = str::findLeftMatch(commands, split[0]);
    if (command == "") {
        std::cerr << "Unknown command.\n";
        return;
    }
    if (command == "update" || command == "delete" || command == "start"|| command == "done") {
        if (split.size() < 2) {
            std::cerr << "Task id was not specified in the input.\n";
            return;
        }
        if (str::parseInt(split[1]) < 0) {
            std::cerr << "Could not convert the second argument (" << split[1] <<") to the positive integer.\n";
            return;
        }
        if (!this->tasks.has(split[1])) {
            std::cerr << "Could not find the task with the id of " << split[1] <<".\n";
            return;
        }
    }
    if (command == "update") {
        if (split.size() < 3) {
            std::cerr << "Empty description given, failed to update (specify new description after the ID).\n";
            return;
        }
        std::string newDescription = "";
        for (int i = 2; i < split.size(); i++) {
            newDescription += split[i];
        }
        this->updateTask(split[1], newDescription);
        return;
    }
    if (command == "delete") {
        this->deleteTask(split[1]);
        return;
    }
    if (command == "start") {
        this->markTask(split[1], "in-progress");
        return;
    }
    if (command == "done") {
        this->markTask(split[1], "done");
        return;
    }
    if (command == "new") {
        if (split.size() < 2) {
            std::cerr << "Empty description given, failed to add (specify description).\n";
            return;
        }
        std::string description = "";
        for (int i = 1; i < split.size(); i++) {
            description += split[i];
        }
        this->addTask(description);
        return;
    }
    if (command == "list") {
        std::string filter = "";
        if (split.size() >= 3) {
            filter = split[2];
        }
        this->listTasks(filter);
    }
}

void taskscore::Taskmanager::addTask(std::string description) {
    this->counter += 1;
    std::string newId = std::to_string(this->counter);
    json::Object *newTask = new json::Object();
    json::Parameter *newDescription = new json::Parameter(description);
    newTask->add("description", newDescription);
    json::Parameter *newStatus = new json::Parameter("to-do");
    newTask->add("status", newStatus);
    json::Parameter *newTaskParameter = new json::Parameter(newTask);
    this->tasks.add(newId, newTaskParameter);
    json::Parameter *newCounter = new json::Parameter(this->counter);
    this->tasks.update("counter", newCounter);
    std::cout << "Successfully added a new task with the ID of " << newId << " and the following description: \"" << description << "\".\n";
    this->save();
}

void taskscore::Taskmanager::updateTask(std::string id, std::string newDescription) {
    json::Parameter *newParameter = new json::Parameter(newDescription);
    this->tasks.get(id)->getObjectValue()->update("description", newParameter);
    std::cout << "Updated task {" << id << "}'s description to: \"" << newDescription << "\".\n";
    this->save();
}

void taskscore::Taskmanager::deleteTask(std::string id) {
    this->tasks.remove(id);
    std::cout << "Task {" << id << "} was successfully deleted.\n";
    this->save();
}

void taskscore::Taskmanager::markTask(std::string id, std::string status) {
    json::Parameter *newParameter = new json::Parameter(status);
    this->tasks.get(id)->getObjectValue()->update("description", newParameter);
    std::cout << "Updated task {" << id << "}'s status to: \"" << status << "\".\n";
    this->save();
}

void taskscore::Taskmanager::listTasks(std::string filter) {
    std::cout << "List of tasks filtered as \"" << filter << "\":\n";
    std::map<std::string, json::Parameter> map = this->tasks.getBody();
    std::map<std::string, json::Parameter>::iterator it;
    int count = 0;
    for (it = map.begin(); it != map.end(); it++) {
        if (it->first != "counter") {
            std::string description = it->second.getObjectValue()->get("description")->getStringValue();
            std::string status = it->second.getObjectValue()->get("status")->getStringValue();
            if (str::startsWith(status, filter)) {
                std::cout << "Task #" << it->first << ":\n";
                std::cout << "\tDescription: \"" << description << "\";\n";
                std::cout << "\tStatus: " << status << ".\n";
                count++;
            }
        }
    }
    std::cout << "Found tasks after filtering: " << count << ".\n";
    std::cout << "Overall tasks: " << this->counter << ".\n";
}

void taskscore::Taskmanager::save() {
    std::string stringified = this->tasks.stringify();
    fileio::write("tasks.json", stringified);
}