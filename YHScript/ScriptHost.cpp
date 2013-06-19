#include "ScriptHost.h"
#include "cocos2d.h"
#include "Modules.h"
#include "JSValUtil.h"

USING_NS_CC;

NS_YHSCRIPT_BEGIN

/**
 * 返回resource目录
 */
JSBool 
cwd(JSContext *cx,uint32_t argc,jsval *vp)
{
    if(argc==0){
        std::vector<std::string> searchPaths=CCFileUtils::sharedFileUtils()->getSearchPaths();
        //first search paths is resource dir
		jsval jsret=std_string_to_jsval(cx,searchPaths.at(0));
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
    }
	JS_ReportError(cx, "[ScriptHost::CWD]wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
/**
 * 初始化内置模块
 */
void ScriptHost::init(JSContext* cx,JSObject* global,JSObject* host)
{
    //添加模块动态加载函数
    JS_DefineFunction(cx, host, "binding", Modules::binding, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, host, "cwd", cwd, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
}

NS_YHSCRIPT_END