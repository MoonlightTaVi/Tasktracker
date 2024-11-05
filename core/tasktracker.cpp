#include "tasktracker.h"
#include "../tools/datetime.h"

tasks::Tasktracker::Tasktracker() { // Constructor
    std::string readfile = fileio::read("tasks.json"); // Read JSON
    this->tasks = json::Object(); // Create an empty JS object
    if (readfile != "") { // If file exists and not empty
        int start = 0; // This line is needed for nested objects (see json::createObject)
        json::createObject(this->tasks, readfile, start); // Parse text to the object
    }
    if (!this->tasks.has("counter")) { // The file must have a "counter" property with the overall number of tasks
        if (readfile != "") { // If the file wasn't empty, but there's no such a property
            std::cerr << "[ERROR] \"tasks.json\" seems to be corrupted (no task counter). Unexpected behaviour may happen.\n";
        }
        json::Parameter counter = json::Parameter(0); // We add this property with a default value
        json::Parameter *counterPtr = &counter;
        this->tasks.add("counter", counterPtr);
    }
    this->counter = this->tasks.get("counter")->getIntValue(); // Update the variable, corresponding to the counter

    // Show tips
    std::cout << "Possible commands:\n\tnew {description of the task to add}";
    std::cout << "\n\tupdate {task ID} {the new description of the task}";
    std::cout << "\n\tdelete {the ID of the task you want to delete}";
    std::cout << "\n\tstart {the ID of the task you want to set as \"in-progress\"}";
    std::cout << "\n\tdone {the ID of the task you want to set as \"done\"}";
    std::cout << "\n\tlist (show all tasks)";
    std::cout << "\n\tlist {filter} (show filtered tasks, where filter can be one of the following: \"to-do\", \"in-progress\", \"done\")";
    std::cout << "\nYou can also use shortcuts for the commands and the filters, for example \"l i\" is the same as \"list in-progress\"" << std::endl << std::endl;
}

void tasks::Tasktracker::execute(std::string line) { // Process input
    std::vector<std::string> commands = {"new", "update", "delete", "start", "done", "list"}; // All commands
    std::vector<std::string> split = {}; // Split the input into words
    str::split(split, line, " ");
    if (split.size() == 0) { // Empty input
        std::cerr << "[ERROR] No command given.\n";
        return;
    }
    std::string command = str::findLeftMatch(commands, split[0]); // You can also type only the first characters of a command
    if (command == "") { // No matches
        std::cerr << "[ERROR] Unknown command.\n";
        return;
    }
    // The commands below need the task ID to be executed
    if (command == "update" || command == "delete" || command == "start"|| command == "done") {
        if (split.size() < 2) { // No ID
            std::cerr << "[ERROR] Task id was not specified in the input.\n";
            return;
        }
        if (str::parseInt(split[1]) < 0) { // ID is not an integer
            printf("[ERROR] Could not convert the second argument (%s) to the positive integer.\n", split[1].c_str());
            return;
        }
        if (!this->tasks.has(split[1])) { // No such ID
            printf("[ERROR] Could not find the task with the id of %s.\n", split[1].c_str());
            return;
        }
    }
    if (command == "update") { // Update description
        if (split.size() < 3) { // No description
            std::cerr << "[ERROR] Empty description given, failed to update (specify new description after the ID).\n";
            return;
        }
        std::string newDescription = ""; // Join the words from split from the third one and to the last one
        for (int i = 2; i < split.size(); i++) {
            newDescription += split[i];
            if (i < split.size() - 1) {
                newDescription += " ";
            }
        }
        this->updateTask(split[1], newDescription); // Pass new arguments further
        return; // Stop the method
    }
    if (command == "delete") { // Delete the task
        if (split[0].length() == 1) { // Only one letter was given as a command, which may refer to both "delete" and "done"
            std::cout << "Do you want to delete the task? (in the future, type \"do\" to mark done and \"de\" to delete)\ny / n >>> ";
            std::string answer = "";
            std::cin >> answer;
            if (answer != "y") { // Process further only if user types "y"
                std::cout << "Operation abort.\n";
                return;
            }
        }
        this->deleteTask(split[1]);
        return;
    }
    if (command == "start") { // Mark "in-progress"
        this->markTask(split[1], "in-progress");
        return;
    }
    if (command == "done") { // Mark "done"
        this->markTask(split[1], "done");
        return;
    }
    if (command == "new") { // Create a new task
        if (split.size() < 2) { // No description given
            std::cerr << "[ERROR] Empty description given, failed to add (specify description).\n";
            return;
        }
        std::string description = ""; // Join the words from split
        for (int i = 1; i < split.size(); i++) {
            description += split[i];
            if (i < split.size() - 1) {
                description += " ";
            }
        }
        this->addTask(description);
        return;
    }
    if (command == "list") { // Show the list of tasks
        std::string filter = "";
        if (split.size() >= 2) { // The third word (optional) represents the filter (by status)
            filter = split[1];
        }
        if (filter != "") { // You can also type the first letters of the filter
            std::vector<std::string> statuses = {"to-do", "in-progress", "done"};
            filter = str::findLeftMatch(statuses, filter);
        }
        this->listTasks(filter);
    }
}

void tasks::Tasktracker::addTask(std::string description) { // Add a new task
    this->counter += 1; // Increase task count
    std::string newId = std::to_string(this->counter); // Task ID is a string
    json::Object *newTask = new json::Object(); // New task's object
    json::Parameter *newDescription = new json::Parameter(description); // Its description
    newTask->add("description", newDescription);
    json::Parameter *newStatus = new json::Parameter("to-do"); // Default status
    newTask->add("status", newStatus);
    json::Parameter *newCreated = new json::Parameter(str::getDateTime()); // Creation date
    newTask->add("created", newCreated);
    json::Parameter *newUpdated = new json::Parameter("never updated"); // Default "updated at" info
    newTask->add("updated", newUpdated);
    json::Parameter *newTaskParameter = new json::Parameter(newTask);
    this->tasks.add(newId, newTaskParameter); // Add the task to the main JS object
    json::Parameter *newCounter = new json::Parameter(this->counter);
    this->tasks.update("counter", newCounter); // Update the counter of the main object
    printf("> Successfully added a new task with the ID of %s and the following description: \"%s\".\n", newId.c_str(), description.c_str());
    this->save(); // Save to file
}

void tasks::Tasktracker::updateTask(std::string id, std::string newDescription) { // Update the desription
    json::Parameter *newParamDescription = new json::Parameter(newDescription); // New description
    this->tasks.get(id)->getObjectValue()->update("description", newParamDescription);
    json::Parameter *newParamUpdated = new json::Parameter(str::getDateTime()); // New "updated at"
    this->tasks.get(id)->getObjectValue()->update("updated", newParamUpdated);
    printf("> Updated task {%s}'s description to: \"%s\".\n", id.c_str(), newDescription.c_str());
    this->save(); // Save to file
}

void tasks::Tasktracker::deleteTask(std::string id) {
    this->tasks.remove(id); // Simply remove the object of the task from the main object
    printf("> Task {%s} was successfully deleted.\n", id.c_str());
    this->save(); // Save to file
}

void tasks::Tasktracker::markTask(std::string id, std::string status) { // Update status
    json::Parameter *newParameter = new json::Parameter(status);
    this->tasks.get(id)->getObjectValue()->update("status", newParameter);
    json::Parameter *newParamUpdated = new json::Parameter(str::getDateTime());
    this->tasks.get(id)->getObjectValue()->update("updated", newParamUpdated);
    printf("> Updated the status of the task with the ID of {%s} and the description of \"%s\"  to: \"%s\".\n", id.c_str(), this->tasks.get(id)->getObjectValue()->get("description")->getStringValue().c_str(), status.c_str());
    this->save(); // Save to file
}

void tasks::Tasktracker::listTasks(std::string filter) { // Show the list of the tasks
    printf("> List of tasks filtered as \"%s\":\n", filter.c_str()); // string.c_str() is neccessary in printf
    std::map<std::string, json::Parameter> map = *this->tasks.getBody(); // Get the main object
    std::map<std::string, json::Parameter>::iterator it; // Iterator
    int count = 0; // We count the filtered list's items
    for (it = map.begin(); it != map.end(); it++) { // Iterate through map
        if (it->first == "counter") { // Skip the counter parameter
            continue;
        }
        // Get the info of the task
        std::string created = it->second.getObjectValue()->get("created")->getStringValue();
        std::string updated = it->second.getObjectValue()->get("updated")->getStringValue();
        std::string description = it->second.getObjectValue()->get("description")->getStringValue();
        std::string status = it->second.getObjectValue()->get("status")->getStringValue();
        if (str::startsWith(status, filter)) { // If it corresponds to the filter (or the filter is empty)
            printf("Task #%s:\n", it->first.c_str());
            printf("\tCreated at: %s;\n", created.c_str());
            printf("\tUpdated at: %s;\n", updated.c_str());
            printf("\tDescription: \"%s\";\n", description.c_str());
            printf("\tStatus: %s.\n", status.c_str());
            count++;
        }
    }
    printf("> Found tasks after filtering: %d.\n", count);
    printf("> Overall tasks (including deleted): %d.\n", this->counter);
}

void tasks::Tasktracker::save() { // Save to file
    std::string stringified = this->tasks.stringify();
    fileio::write("tasks.json", stringified);
}