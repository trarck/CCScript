//
//  ScriptCore.h
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef YHSCRIPT_MODULES_H_
#define YHSCRIPT_MODULES_H_

#include <string>
#include <map>
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

class Modules
{
public:

    /**
     * 初始化内置模块
     */
    static void init();

    /**
     * 添加一个内置模块
     */
    static void addModules(Module* module);

     /**
     * 获取一个内置模块
     */
    static Module* getModule(const std::string& name);

    /**
     * 移除所有内置模块
     */
    static void removeAllModules();
    
   /**
    * use node line api
    * 不是在创建js rutime的时候把所有模块一次性绑定到，global对象，而是动态加载。
    * 分为内置模块(c/c++),原生模块(js to c/c++),用户模块(js)
    * 
    */
    static JSBool binding(JSContext *cx,uint32_t argc,jsval *vp);

private:

    static std::map<std::string,Module*> s_modules;

    static std::map<std::string,JSObject*> s_moduleExportsCache;
};


NS_YHSCRIPT_END

#endif //YHSCRIPT_MODULES_H_
