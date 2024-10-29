# Task tracker (C++)
## Made for [roadmap.sh](https://roadmap.sh/projects/task-tracker)
### Current status: work-in-progress (as of 2024.10.29)
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

## Done
1. Reading files
1. Parsing JSON (the parser is self-made, since C++ does not have any native tools to work with JSON; it can handle only string and object parameters at the moment (which is enough for the task); if you feed an integer or a boolean to it, it will process the input as a string)
## To do
1. Stringify objects
1. Write to file
1. User interface with the features, corresponding to the task