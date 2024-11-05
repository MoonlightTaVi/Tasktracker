#ifndef _json_obj_h_ // Include guards protect from circular dependency injection
#define _json_obj_h_

#include <map>
#include <string>

namespace json {

    class Parameter; // Forward declaration
    class Object {
        std::map<std::string, Parameter> body; // The body of the object (a map of parameter name-parameter)
        public:
            void add(std::string key, Parameter *value); // Add parameter
            Parameter* get(std::string key); // Get parameter
            bool has(std::string key); // Contains parameter?
            void update(std::string key, Parameter *newValue); // Update parameter
            void remove(std::string key); // Remove parameter
            std::map<std::string, Parameter>* getBody(); // Get the body of the object
            std::string toString(int indent); // Print to console (for testing)
            std::string stringify(); // Transform to a JSON string
    };

    void createObject(Object &saveTo, std::string &src, int &start); // Create an object from a JSON string
}

#endif