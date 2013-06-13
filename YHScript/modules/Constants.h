#ifndef YHSCRIPT_MODULES_CONSTANTS_H_
#define YHSCRIPT_MODULES_CONSTANTS_H_

#include "jsapi.h"
#include <string>
#include "../Module.h"

NS_YHSCRIPT_BEGIN

class Constants
{
public:
    static void registerConstants(JSContext *cx,JSObject *module);
    static Module moduleData;
};

NS_YHSCRIPT_END
	
#endif //YHSCRIPT_MODULES_CONSTANTS_H_