#include "parameter.h"
#include "object.h" // Look at this header for some explanation
#include <iostream>

void json::Object::add(std::string key, json::Parameter* value) {
    std::string newKey = key;
    json::Parameter temp = *value; // Depointerize
    body.insert(std::pair<std::string,json::Parameter>(newKey, temp));
}
json::Parameter* json::Object::get(std::string key) {
    json::Parameter *temp = &this->body.find(key)->second; // Return a pointer to a value
    return temp;
}
bool json::Object::has(std::string key) {
    return this->body.count(key) > 0;
}
void json::Object::update(std::string key, json::Parameter *newValue) {
    if (!this->has(key)) {
        return;
    }
    this->remove(key);
    Parameter temp = *newValue; // Depointerize
    body.insert(std::pair<std::string,json::Parameter>(key, temp));
}
void json::Object::remove(std::string key) {
    this->body.erase(key);
}
std::map<std::string, json::Parameter>* json::Object::getBody() {
    std::map<std::string, json::Parameter> *temp = &this->body;
    return temp;
}
std::string json::Object::toString(int indent) { // For testing
    std::string prefix = "";
    std::string ret = "";
    for (int i = 0; i < indent; i++) {
        prefix += "\t";
    }
    std::map<std::string, json::Parameter>::iterator it;
    for (it = this->body.begin(); it != this->body.end(); it++) {
        ret += prefix + it->first + ": ";
        if (it->second.getType() == 0) {
            ret += "\n" + it->second.getObjectValue()->toString(indent+1);
        } else if (it->second.getType() == 1) {
            ret += it->second.getStringValue() + "\n";
        }
    }
    return ret;
}
std::string json::Object::stringify() {
    std::string ret = "{";
    std::map<std::string, json::Parameter>::iterator it;
    for (it = this->body.begin(); it != this->body.end(); it++) {
        ret += "\"" + it->first + "\":"; // Key
        switch (it->second.getType()) { // Parameter
            case 0:
            {
                ret += it->second.getObjectValue()->stringify(); // Recursive call on a nested object
                break;
            }
            case 1:
            {
                ret += "\"" + it->second.getStringValue() += "\"";
                break;
            }
            case 2:
            {
                ret += "\"" + std::to_string(it->second.getIntValue()) += "\"";
                break;
            }
            default:
            {
                std::cerr << "Error stringifying object.\n";
                return "";
            }
        }
        ret += ","; // Trailing comma
    }
    ret += "}";
    return ret;
}

void json::createObject(json::Object &saveTo, std::string &src, int &start) {
    std::string currentKey = "";
    std::string currentStringValue = "";
    bool isEditingKey = true;
    bool isEditingValue = false;
    bool metQuotation = false;
    for (int i = start; i < src.length(); i++) { // Iterate from the "start"
        if (metQuotation && src[i] != '"') { // The text inside the quotation marks ignores the rules
            if (isEditingKey) {
                currentKey += src[i];
            }
            if (isEditingValue) {
                currentStringValue += src[i];
            }
            continue;
        }
        switch (src[i])
        {
            case '{': // Probably nested object
            {
                if (currentKey != "") {
                    json::Object nestedObject = json::Object();
                    json::createObject(nestedObject, src, i);
                    json::Object *p = &nestedObject;
                    json::Parameter *newParamPtr = new json::Parameter(p);
                    saveTo.add(currentKey, newParamPtr);
                    currentKey = "";
                    currentStringValue = "";
                    isEditingKey = true;
                    isEditingValue = false;
                }
                continue;
            }
            case ',': // Delimiter of the parameters
            {
                isEditingValue = false;
                isEditingKey = true;
                if (currentKey == "" || currentStringValue == "") {
                    continue;
                }
                json::Parameter newParam = json::Parameter(currentStringValue);
                json::Parameter *newParamP = &newParam;
                saveTo.add(currentKey, newParamP);
                currentKey = "";
                continue;
            }
            case ':': // Delimiter between the parameter name (key) and the parameter
            {
                currentStringValue = "";
                isEditingKey = false;
                isEditingValue = true;
                continue;
            }
            case '"':
            {
                metQuotation = !metQuotation;
                continue;
            }
            case ('\n', '\t', ' '):
            {
                continue; // Skip
            }
            case '}': // End of the object
            {
                if (currentKey != "" && currentStringValue != "") { // The last parameter
                    json::Parameter newParam = json::Parameter(currentStringValue);
                    json::Parameter *newParamP = &newParam;
                    saveTo.add(currentKey, newParamP);
                }
                start = i++; // Increase the iterator (if it is a nested object, it shares the iterator with the parental one)
                return;
            }
            default: // Any other character
            {
                if (!std::isalnum(src[i]) && !metQuotation) { // If not in-between a quote, only alphanumeric allowed
                    continue;
                }
                if (isEditingValue) {
                    currentStringValue += src[i];
                    continue;
                }
                if (isEditingKey) {
                    currentKey += src[i];
                }
            }
        }
    }
}