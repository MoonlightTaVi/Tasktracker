#include "tasktracker.h"
#include "../tools/datetime.h"

taskscore::Taskmanager::Taskmanager() {
    std::string readfile = fileio::read("tasks.json");
    this->tasks = json::Object();
    if (readfile != "") {
        int start = 0;
        json::createObject(this->tasks, readfile, start);
    }
    if (!this->tasks.has("counter")) {
        if (readfile != "") {
            std::cerr << "[ERROR] \"tasks.json\" seems to be corrupted (no task counter). Unexpected behaviour may happen.\n";
        }
        json::Parameter counter = json::Parameter(0);
        json::Parameter *counterPtr = &counter;
        this->tasks.add("counter", counterPtr);
    }
    this->counter = this->tasks.get("counter")->getIntValue();

    std::cout << "Possible commands:\n\tnew {description of the task to add}";
    std::cout << "\n\tupdate {task ID} {the new description of the task}";
    std::cout << "\n\tdelete {the ID of the task you want to delete}";
    std::cout << "\n\tstart {the ID of the task you want to set as \"in-progress\"}";
    std::cout << "\n\tcomplete {the ID of the task you want to set as \"done\"}";
    std::cout << "\n\tlist (show all tasks)";
    std::cout << "\n\tlist {filter} (show filtered tasks, where filter can be one of the following: \"to-do\", \"in-progress\", \"done\")";
    std::cout << "\nYou can also use shortcuts for the commands and the filters, for example \"l i\" is the same as \"list in-progress\"" << std::endl << std::endl;
}

void taskscore::Taskmanager::execute(std::string line) {
    std::vector<std::string> commands = {"new", "update", "delete", "start", "complete", "list"};
    std::vector<std::string> split = {};
    str::split(split, line, " ");
    if (split.size() == 0) {
        std::cerr << "[ERROR] No command given.\n";
        return;
    }
    std::string command = str::findLeftMatch(commands, split[0]);
    if (command == "") {
        std::cerr << "[ERROR] Unknown command.\n";
        return;
    }
    if (command == "update" || command == "delete" || command == "start"|| command == "done") {
        if (split.size() < 2) {
            std::cerr << "[ERROR] Task id was not specified in the input.\n";
            return;
        }
        if (str::parseInt(split[1]) < 0) {
            printf("[ERROR] Could not convert the second argument (%s) to the positive integer.\n", split[1].c_str());
            return;
        }
        if (!this->tasks.has(split[1])) {
            printf("[ERROR] Could not find the task with the id of %s.\n", split[1].c_str());
            return;
        }
    }
    if (command == "update") {
        if (split.size() < 3) {
            std::cerr << "[ERROR] Empty description given, failed to update (specify new description after the ID).\n";
            return;
        }
        std::string newDescription = "";
        for (int i = 2; i < split.size(); i++) {
            newDescription += split[i];
            if (i < split.size() - 1) {
                newDescription += " ";
            }
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
    if (command == "complete") {
        this->markTask(split[1], "done");
        return;
    }
    if (command == "new") {
        if (split.size() < 2) {
            std::cerr << "[ERROR] Empty description given, failed to add (specify description).\n";
            return;
        }
        std::string description = "";
        for (int i = 1; i < split.size(); i++) {
            description += split[i];
            if (i < split.size() - 1) {
                description += " ";
            }
        }
        this->addTask(description);
        return;
    }
    if (command == "list") {
        std::string filter = "";
        if (split.size() >= 2) {
            filter = split[1];
        }
        if (filter != "") {
            std::vector<std::string> statuses = {"to-do", "in-progress", "done"};
            filter = str::findLeftMatch(statuses, filter);
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
    json::Parameter *newCreated = new json::Parameter(str::getDateTime());
    newTask->add("created", newCreated);
    json::Parameter *newUpdated = new json::Parameter("never updated");
    newTask->add("updated", newUpdated);
    json::Parameter *newTaskParameter = new json::Parameter(newTask);
    this->tasks.add(newId, newTaskParameter);
    json::Parameter *newCounter = new json::Parameter(this->counter);
    this->tasks.update("counter", newCounter);
    printf("> Successfully added a new task with the ID of %s and the following description: \"%s\".\n", newId.c_str(), description.c_str());
    this->save();
}

void taskscore::Taskmanager::updateTask(std::string id, std::string newDescription) {
    json::Parameter *newParamDescription = new json::Parameter(newDescription);
    this->tasks.get(id)->getObjectValue()->update("description", newParamDescription);
    json::Parameter *newParamUpdated = new json::Parameter(str::getDateTime());
    this->tasks.get(id)->getObjectValue()->update("updated", newParamUpdated);
    printf("> Updated task {%s}'s description to: \"%s\".\n", id.c_str(), newDescription.c_str());
    this->save();
}

void taskscore::Taskmanager::deleteTask(std::string id) {
    this->tasks.remove(id);
    printf("> Task {%s} was successfully deleted.\n", id.c_str());
    this->save();
}

void taskscore::Taskmanager::markTask(std::string id, std::string status) {
    json::Parameter *newParameter = new json::Parameter(status);
    this->tasks.get(id)->getObjectValue()->update("status", newParameter);
    json::Parameter *newParamUpdated = new json::Parameter(str::getDateTime());
    this->tasks.get(id)->getObjectValue()->update("updated", newParamUpdated);
    printf("> Updated the status of the task with the ID of {%s} and the description of \"%s\"  to: \"%s\".\n", id.c_str(), this->tasks.get(id)->getObjectValue()->get("description")->getStringValue().c_str(), status.c_str());
    this->save();
}

void taskscore::Taskmanager::listTasks(std::string filter) {
    printf("> List of tasks filtered as \"%s\":\n", filter.c_str());
    std::map<std::string, json::Parameter> map = this->tasks.getBody();
    std::map<std::string, json::Parameter>::iterator it;
    int count = 0;
    for (it = map.begin(); it != map.end(); it++) {
        if (it->first != "counter") {
            std::string created = it->second.getObjectValue()->get("created")->getStringValue();
            std::string updated = it->second.getObjectValue()->get("updated")->getStringValue();
            std::string description = it->second.getObjectValue()->get("description")->getStringValue();
            std::string status = it->second.getObjectValue()->get("status")->getStringValue();
            if (str::startsWith(status, filter)) {
                printf("Task #%s:\n", it->first.c_str());
                printf("\tCreated at: %s;\n", created.c_str());
                printf("\tUpdated at: %s;\n", updated.c_str());
                printf("\tDescription: \"%s\";\n", description.c_str());
                printf("\tStatus: %s.\n", status.c_str());
                count++;
            }
        }
    }
    printf("> Found tasks after filtering: %d.\n", count);
    printf("> Overall tasks (including deleted): %d.\n", this->counter);
}

void taskscore::Taskmanager::save() {
    std::string stringified = this->tasks.stringify();
    fileio::write("tasks.json", stringified);
}