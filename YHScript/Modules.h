//
//  ScriptCore.h
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef YHSCRIPT_JSVALUTIL_H_
#define YHSCRIPT_JSVALUTIL_H_

#include "cocos2d.h"
#include "jsapi.h"
#include "YHScriptMacros.h"

NS_YHSCRIPT_BEGIN

 typedef void (* addon_register_func)(JSContext *cx,JSObject *exports);

class Module
{
public:
   int version;
   void *dso_handle;
   std::string filename;
   node::addon_register_func register_func;
   std::string name;
};

class Modules
{
public:

    static void registerModules(const std::string& moduleName);
    
private:

    static std::map<std::string,
};
/**
* use node line api
* 不是在创建js rutime的时候把所有模块一次性绑定到，global对象，而是动态加载。
* 分为内置模块(c/c++),原生模块(js to c/c++),用户模块(js)
* 
*/
JSBool binding();

NS_YHSCRIPT_END

#endif //YHSCRIPT_JSVALUTIL_H_
