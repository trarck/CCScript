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

class Module
{
public:

    Module();
    ~Module();
    bool init();

    void load();

protected:

    std::map<std::string,JSObject> m_moduleCache;
};

NS_YHSCRIPT_END

#endif //YHSCRIPT_JSVALUTIL_H_
