#ifndef _json_obj_h_
#define _json_obj_h_

#include <map>
#include <string>

namespace json {

    class Parameter;
    class Object {
        std::map<std::string, Parameter> body;
        public:
            void add(std::string key, Parameter *value);
            Parameter* get(std::string key);
            bool has(std::string key);
            void update(std::string key, Parameter *newValue);
            void remove(std::string key);
            std::map<std::string, Parameter> getBody();
            std::string toString(int indent);
            std::string stringify();
    };

    void createObject(Object &saveTo, std::string &src, int &start);
}

#endif