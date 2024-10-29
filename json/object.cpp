#include "parameter.h"
#include "object.h"
#include <map>
#include <string>
#include <iostream>

void json::Object::add(std::string key, json::Parameter* value) {
    std::string newKey = key;
    json::Parameter temp = *value;
    body.insert(std::pair<std::string,json::Parameter>(newKey, temp));
}
json::Parameter* json::Object::get(std::string key) {
    json::Parameter *temp = &this->body.find(key)->second;
    return temp;
}
std::string json::Object::toString(int indent) {
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

void json::createObject(json::Object &saveTo, std::string &src, int &start) {
    std::string currentKey = "";
    std::string currentStringValue = "";
    bool isEditingKey = true;
    bool isEditingValue = false;
    bool metQuotation = false;
    for (int i = start; i < src.length(); i++) {
        switch (src[i])
        {
            case '{':
            {
                if (currentKey != "") {
                    json::Object nestedObject = json::Object();
                    json::createObject(nestedObject, src, i);
                    json::Object *p = &nestedObject;
                    json::Parameter newParam = json::Parameter(p);
                    json::Parameter *newParamP = &newParam;
                    saveTo.add(currentKey, newParamP);
                    currentKey = "";
                    currentStringValue = "";
                    isEditingKey = true;
                    isEditingValue = false;
                }
                continue;
            }
            case ',':
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
            case ':':
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
                if (!metQuotation) {
                    continue;
                }
                if (isEditingKey) {
                    currentKey += src[i];
                    continue;
                }
                if (isEditingValue) {
                    currentStringValue += src[i];
                }
                continue;
            }
            case '}':
            {
                if (currentKey != "" || currentStringValue != "") {
                    json::Parameter newParam = json::Parameter(currentStringValue);
                    json::Parameter *newParamP = &newParam;
                    saveTo.add(currentKey, newParamP);
                }
                start = i++;
                return;
            }
            default:
            {
                if (!std::isalnum(src[i]) && !metQuotation) {
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