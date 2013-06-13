#ifndef YHSCRIPT_MODULE_H_
#define YHSCRIPT_MODULE_H_

#include "cocos2d.h"
#include "jsapi.h"
#include "YHScriptMacros.h"

NS_YHSCRIPT_BEGIN

typedef void (* module_register_func)(JSContext *cx,JSObject *module);

struct ModuleStruct
{
//public:
   int version;
   void *dso_handle;
   std::string filename;
   module_register_func register_func;
   std::string name;
};

typedef struct ModuleStruct Module;

NS_YHSCRIPT_END

#endif //YHSCRIPT_MODULE_H_
