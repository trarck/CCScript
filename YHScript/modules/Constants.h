#ifndef YHSCRIPT_MODULES_CONSTANTS_H_
#define YHSCRIPT_MODULES_CONSTANTS_H_

#include "jsapi.h"
#include <string>
#include "../Module.h"

NS_YHSCRIPT_MODULES_BEGIN

class Constants
{
public:
    static void registerModule(JSContext *cx,JSObject *module);
    static Module s_moduleData;
};

NS_YHSCRIPT_MODULES_END
	
#endif //YHSCRIPT_MODULES_CONSTANTS_H_