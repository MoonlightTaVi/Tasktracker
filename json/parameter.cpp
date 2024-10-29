#include "parameter.h"
#include "object.h"
#include <string>

json::Parameter::Parameter (json::Object* objectValue) {
    this->type = 0;
    json::Object temp = *objectValue;
    this->objectValue = temp;
}
json::Parameter::Parameter (std::string stringValue) {
    this->type = 1;
    this->stringValue = stringValue;
}
json::Object* json::Parameter::getObjectValue() {
    Object *_default = NULL;
    if (this->type != 0) {
        return _default;
    }
    _default = &this->objectValue;
    return _default;
}
std::string json::Parameter::getStringValue() {
    if (this->type != 1) {
        return "";
    }
    return this->stringValue;
}
int json::Parameter::getType() {
    return this->type;
}