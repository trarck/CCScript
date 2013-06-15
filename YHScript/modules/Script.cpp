#include "Script.h"
#include "../ScriptCore.h"

NS_YHSCRIPT_MODULES_BEGIN

JSBool evaluateScript(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
        jsval* argv = JS_ARGV(cx, vp);
        JSString* str = JS_ValueToString(cx, argv[0]);
        JSAutoByteString contentBytes(cx,str);
        const char* content=contentBytes.ptr();
        unsigned int contentLength=strlen(content);
        JSBool res = false;
		jsval rval;
        if (argc == 2 ) {
            JSObject* global = JSVAL_TO_OBJECT(argv[1]);

            res = ScriptCore::getInstance()->evaluateString(content,contentLength,&rval,"",global,cx);

        } else {
            JSObject* glob = JS_GetGlobalForScopeChain(cx);
            res = ScriptCore::getInstance()->evaluateString(content,contentLength,&rval,"",glob,cx);
        }
		JS_SET_RVAL(cx, vp, rval);
        return res;
    }
    return JS_TRUE;
}

JSBool executeScript(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
        jsval* argv = JS_ARGV(cx, vp);
        JSString* str = JS_ValueToString(cx, argv[0]);
        JSAutoByteString pathBytes(cx,str);
        const char* path=pathBytes.ptr();

        JSBool res = false;
		jsval rval;
        if (argc == 2 ) {
            JSObject* glob = JSVAL_TO_OBJECT(argv[1]);

            res = ScriptCore::getInstance()->executeScriptFile(path,&rval,glob,cx);

        } else {
            JSObject* glob = JS_GetGlobalForScopeChain(cx);
            res = ScriptCore::getInstance()->executeScriptFile(path,&rval,glob,cx);
        }
		JS_SET_RVAL(cx, vp, rval);
        return res;
    }
    return JS_TRUE;
}

Module Script::s_moduleData=YHSCRIPT_MODULE_DATA(evals,Script::registerModule);

void Script::registerModule(JSContext *cx,JSObject *module)
{
    JS_DefineFunction(cx, module, "evaluate", evaluateScript, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, module, "execute", executeScript, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}

NS_YHSCRIPT_MODULES_END