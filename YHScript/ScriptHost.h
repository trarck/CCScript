//
//  ScriptCore.h
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef YHSCRIPT_SCRIPTHOST_H_
#define YHSCRIPT_SCRIPTHOST_H_

#include "cocos2d.h"
#include "jsapi.h"
#include "YHScriptMacros.h"

NS_YHSCRIPT_BEGIN
class ScriptHost
{
public:

    /**
     * 初始化process模块
     */
    static void init(JSContext* cx,JSObject* global,JSObject* host);
};


NS_YHSCRIPT_END

#endif //YHSCRIPT_SCRIPTHOST_H_
