//
//  ScriptCore.cpp
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include "Modules.h"
#include "JSValUtil.h"
#include "modules/Person.h"
#include "modules/Constants.h"

NS_YHSCRIPT_BEGIN

std::map<std::string,Module*> Modules::s_modules;

std::map<std::string,JSObject*> Modules::s_moduleExportsCache;
 /**
 * 初始化内置模块
 */
void Modules::init()
{
    addModule(&Constants::moduleData);
    //init person module
    addModule(&PersonModule::moduleData);
}

/**
 * 添加一个内置模块
 */
void Modules::addModule(Module* module)
{
    s_modules[module->name]=module;
}

/**
 * 获取一个内置模块
 */
Module*  Modules::getModule(const std::string& name)
{
    return s_modules[name];    
}

/**
 * 移除所有内置模块
 */
void Modules::removeAllModules()
{
    
}

/**
* use node line api
* 不是在创建js rutime的时候把所有模块一次性绑定到，global对象，而是动态加载。
* 分为内置模块(c/c++),原生模块(js to c/c++),用户模块(js)
* 
*/
JSBool Modules::binding(JSContext *cx,uint32_t argc,jsval *vp)
{
    //获取js参数
    jsval *argv = JS_ARGV(cx, vp);
    jsval jsret;
    JSObject* exports=NULL;

    std::string moduleName;
    //取得模块名。第一个参数为模块名
    jsval_to_std_string(cx,argv[0],&moduleName);
    //从缓存取得模块的注册结果
    std::map<std::string,JSObject*>::iterator iter;
    iter=s_moduleExportsCache.find(moduleName);
    if(iter!=s_moduleExportsCache.end()){
        exports=iter->second;
        jsret=OBJECT_TO_JSVAL(exports);
    }else{
        //取得模块
        Module* module=getModule(moduleName);
    
        if(module){
            JSObject* exports=JS_NewObject(cx, NULL, NULL, NULL);
            module->register_func(cx,exports);
            s_moduleExportsCache[moduleName]=exports;

            jsret=OBJECT_TO_JSVAL(exports);
        }else{
            jsret=JSVAL_NULL;
        }
    }
    JS_SET_RVAL(cx, vp, jsret);
    return JS_TRUE;
}

NS_YHSCRIPT_END