# Task tracker (C++)
## Made for [roadmap.sh](https://roadmap.sh/projects/task-tracker)
### Status: done (2024.11.05), work-in-progress (2024.10.29-2024.11.05)
## Requirements (taken from the site)
The application should run from the command line, accept user actions and inputs as arguments, and store the tasks in a JSON file. The user should be able to:

    Add, Update, and Delete tasks
    Mark a task as in progress or done
    List all tasks
    List all tasks that are done
    List all tasks that are not done
    List all tasks that are in progress

Here are some constraints to guide the implementation:

    You can use any programming language to build this project.
    Use positional arguments in command line to accept user inputs.
    Use a JSON file to store the tasks in the current directory.
    The JSON file should be created if it does not exist.
    Use the native file system module of your programming language to interact with the JSON file.
    Do not use any external libraries or frameworks to build this project.
    Ensure to handle errors and edge cases gracefully.
<br>

# How to use
### The application is used for tracking your tasks
### The tasks are stored in the "tasks.json" in the program directory
### Tasks have:
1. A short description (custom, neccessary)
1. A unique ID
1. Creation date
1. Updated date
1. Status (to-do, in-progress, done)
### Available commands
You can see the list of available commands on the start of the application, but here its brief copy:
1. new {description} - create a new task;
1. update {id} {description} - update the description of the task;
1. delete {id} - delete the task;
1. start {id} - mark the task as "in-progress";
1. done {id} - mark the task as "done";
1. list - show all tasks;
1. list {filter} - show the tasks with the status given in the filter;
1. quit - exit the application. <br> <br>
You can use shortcuts for the commands, for example "l i" is the same as "list in-progress". <br>
Since "delete" and "done" both start with "d", and if you've typed-in "d {id}", 
you're asked if you want to delete the task or abort.

# P.S.
The code is a bit scuffed, it might have surely been better, but I feel too mush exhausted 
to keep developing it further.

# DevLog
## 2024.10.29
## Done
1. Reading files
1. Parsing JSON (the parser is self-made, since C++ does not have any native tools to work with JSON; it can handle only string and object parameters at the moment (which is enough for the task); if you feed an integer or a boolean to it, it will process the input as a string)
## To do
1. Stringify objects
1. Write to file
1. User interface with the features, corresponding to the task
<br>

# UPD 2024.10.30
## Done
1. Writing to file, removing if needed
1. Stringifying objects (with a trailing comma at the moment)
1. Tested, works fine so far
## To do
1. Split the string by a delimiter (a single character) -> needed for parsing positional arguments
1. Remove parameters from the object
1. Update parameters of the object
1. Get datetime
<br>

# UPD 2024.10.31
## Done
1. The program is finished and tested (so far)
## To do
1. Ask user whether they want to delete a task (I always mix up "done" and "complete", resulting in deleting the task, which is "delete" (I just type "d"))
1. Add comments, some minor fixes

# 2024.11.05 - Done