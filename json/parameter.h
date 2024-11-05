#ifndef _json_param_h_ // Include guards protect from circular dependency injection
#define _json_param_h_

#include <string>
#include "object.h"

namespace json {
    class Parameter {
            private:
                int type = -1; // Represents the variable type
                // Values of different types:
                Object objectValue;
                std::string stringValue;
                int intValue;
            public:
                Parameter(Object *objectValue); // Create from object
                Parameter (std::string stringValue); // ..from string
                Parameter (int intValue); // ..from integer
                Object* getObjectValue(); // Get values..
                std::string getStringValue();
                int getIntValue();
                int getType(); // Get type
    };

}
#endif