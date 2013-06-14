#include "Natives.h"
#include "../ScriptCore.h"
#include "script_natives.h"

NS_YHSCRIPT_MODULES_BEGIN

JSBool evaluateNativeSource(JSContext* cx,JSObject* module,const char *source,unsigned length,jsval* rval){
    
    ScriptCore* scriptCore=ScriptCore::getInstance();
    scriptCore->evaluateString(source,length,rval);

/*
    JSObject *global=JS_GetGlobalObject(cx);

    if (!JS_DefineProperty(cx, global, "module", OBJECT_TO_JSVAL(module),
	                       JS_PropertyStub, JS_StrictPropertyStub, JSPROP_ENUMERATE)) {
	   return JS_FALSE;
	}

    ScriptCore* scriptCore=ScriptCore::getInstance();

    jsval fun;
    JSObject* exports=JS_NewObject(cx,NULL,NULL,NULL);
    if (!JS_DefineProperty(cx, module, "exports", OBJECT_TO_JSVAL(exports),
	                       JS_PropertyStub, JS_StrictPropertyStub, JSPROP_ENUMERATE)) {
	   return JS_FALSE;
	}

    scriptCore->evaluateString(source,length,&fun);

    if(fun==JSVAL_VOID) return JS_FALSE;*/

    ////exports, require, module, __filename, __dirname
    //jsval argv[3];
    //unsigned int argc=3;

    //argv[0] = OBJECT_TO_JSVAL(exports);
    //argv[1] = OBJECT_TO_JSVAL(exports);
    //argv[2] = OBJECT_TO_JSVAL(module);

    //if(!JS_CallFunctionValue(scriptCore->getContext(),scriptCore->getGlobal(),fun,argc,argv,NULL)){
    //    return JS_FALSE;
    //}
    return JS_TRUE;
}

Module Natives::s_moduleData=YHSCRIPT_MODULE_DATA(Natives,Natives::registerModule);

void Natives::registerModule(JSContext *cx,JSObject *module)
{
	for (int i = 0; natives[i].name; ++i) {
        if (natives[i].source != node_native) {
            Local<String> name = String::New(natives[i].name);
            Handle<String> source = BUILTIN_ASCII_ARRAY(natives[i].source, natives[i].source_len);
            target->Set(name, source);
        }
    }
}

NS_YHSCRIPT_MODULES_END