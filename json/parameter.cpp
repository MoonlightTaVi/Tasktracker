#include "parameter.h"
#include "../tools/parse-int.h"

json::Parameter::Parameter (json::Object* objectValue) {
    this->type = 0;
    json::Object temp = *objectValue;
    this->objectValue = temp;
}
json::Parameter::Parameter (std::string stringValue) {
    this->type = 1;
    this->stringValue = stringValue;
}
json::Parameter::Parameter (int intValue) {
    this->type = 2;
    this->intValue =intValue;
}
json::Object* json::Parameter::getObjectValue() {
    Object *_default = nullptr;
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
int json::Parameter::getIntValue() {
    if (this->type != 2) {
        if (this->type == 1) {
            int temp = str::parseInt(this->stringValue);
            if (temp != -1) {
                this->intValue = temp;
                this->type = 2;
                return this->intValue;
            }
        }
        return 0;
    }
    return this->intValue;
}
int json::Parameter::getType() {
    return this->type;
}