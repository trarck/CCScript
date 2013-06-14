#ifndef YHSCRIPT_MODULES_PERSON_H_
#define YHSCRIPT_MODULES_PERSON_H_

#include "jsapi.h"
#include <string>
#include "../Module.h"

NS_YHSCRIPT_MODULES_BEGIN

class Natives
{
public:
    static void registerModule(JSContext *cx,JSObject *module);
    static Module s_moduleData;
};

NS_YHSCRIPT_MODULES_END
	
#endif //YHSCRIPT_MODULES_PERSON_H_