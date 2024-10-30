#ifndef _json_param_h_
#define _json_param_h_

#include <string>
#include "object.h"

namespace json {
    class Parameter {
            private:
                int type = -1;
                Object objectValue;
                std::string stringValue;
                int intValue;
            public:
                Parameter(Object *objectValue);
                Parameter (std::string stringValue);
                Parameter (int intValue);
                Object* getObjectValue();
                std::string getStringValue();
                int getIntValue();
                int getType();
    };

}
#endif