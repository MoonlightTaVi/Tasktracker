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
            public:
                Parameter(Object *objectValue);
                Parameter (std::string stringValue);
                Object* getObjectValue();
                std::string getStringValue();
                int getType();
    };

}
#endif