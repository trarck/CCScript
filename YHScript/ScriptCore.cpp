//
//  ScriptCore.cpp
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include "ScriptCore.h"
#include "JSStringWrapper.h"
// for debug socket
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <io.h>
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#endif
#include <pthread.h>

#ifdef ANDROID
#include <android/log.h>
#include <jni/JniHelper.h>
#include <netinet/in.h>
#endif

#ifdef ANDROID
#define  LOG_TAG    "ScriptCore.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) js_log(__VA_ARGS__)
#endif

NS_YHSCRIPT_BEGIN

static const int kMaxJSLogLen = 16*1024;
char *_js_log_buf = NULL;

jsval frame = JSVAL_NULL, script = JSVAL_NULL;
int clientSocket;

// name ~> JSScript map
std::map<std::string, JSScript*> filename_script;
// port ~> socket map
std::map<int,int> ports_sockets;
// name ~> globals
std::map<std::string, js::RootedObject*> globals;

// server entry point for the bg thread
void* serverEntryPoint(void*);

static void executeJSFunctionFromReservedSpot(JSContext *cx, JSObject *obj,
                                              jsval &dataVal, jsval &retval) {

    jsval func = JS_GetReservedSlot(obj, 0);

    if(func == JSVAL_VOID) { return; }
    jsval thisObj = JS_GetReservedSlot(obj, 1);
    JSAutoCompartment ac(cx, obj);
    if(thisObj == JSVAL_VOID) {
        JS_CallFunctionValue(cx, obj, func, 1, &dataVal, &retval);
    } else {
        assert(!JSVAL_IS_PRIMITIVE(thisObj));
        JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(thisObj), func, 1, &dataVal, &retval);
    }
}


void js_log(const char *format, ...) {
    if (_js_log_buf == NULL) {
        _js_log_buf = (char *)calloc(sizeof(char), kMaxJSLogLen+1);
    }
    va_list vl;
    va_start(vl, format);
    int len = vsnprintf(_js_log_buf, kMaxJSLogLen, format, vl);
    va_end(vl);
    if (len) {
        CCLOG("JS: %s\n", _js_log_buf);
    }
}



JSBool JSBCore_platform(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getPlatform");
        return JS_FALSE;
    }

    JSString * platform;

    // config.deviceType: Device Type
    // 'mobile' for any kind of mobile devices, 'desktop' for PCs, 'browser' for Web Browsers
    // #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    //     platform = JS_InternString(_cx, "desktop");
    // #else
    platform = JS_InternString(cx, "mobile");
    // #endif

    jsval ret = STRING_TO_JSVAL(platform);

    JS_SET_RVAL(cx, vp, ret);

    return JS_TRUE;
};

JSBool JSBCore_version(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getVersion");
        return JS_FALSE;
    }

    char version[256];
    snprintf(version, sizeof(version)-1, "%s - %s", "1","1");
    JSString * js_version = JS_InternString(cx, version);

    jsval ret = STRING_TO_JSVAL(js_version);
    JS_SET_RVAL(cx, vp, ret);

    return JS_TRUE;
};

JSBool JSBCore_os(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getOS");
        return JS_FALSE;
    }

    JSString * os;

    // osx, ios, android, windows, linux, etc..
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    os = JS_InternString(cx, "ios");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    os = JS_InternString(cx, "android");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    os = JS_InternString(cx, "windows");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
    os = JS_InternString(cx, "marmalade");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    os = JS_InternString(cx, "linux");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)
    os = JS_InternString(cx, "bada");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    os = JS_InternString(cx, "blackberry");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    os = JS_InternString(cx, "osx");
#else
    os = JS_InternString(cx, "unknown");
#endif

    jsval ret = STRING_TO_JSVAL(os);
    JS_SET_RVAL(cx, vp, ret);

    return JS_TRUE;
};

JSBool JSB_core_restartVM(JSContext *cx, uint32_t argc, jsval *vp)
{
    ScriptCore::getInstance()->reset();
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
};

void registerDefaultClasses(JSContext* cx, JSObject* global) {
    // first, try to get the ns
    jsval nsval;
    JSObject *ns;
    JS_GetProperty(cx, global, "yh", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, global, "yh", &nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }

    ////
    //// Javascript controller (__jsc__)
    ////
    //JSObject *jsc = JS_NewObject(cx, NULL, NULL, NULL);
    //jsval jscVal = OBJECT_TO_JSVAL(jsc);
    //JS_SetProperty(cx, global, "__jsc__", &jscVal);

    //JS_DefineFunction(cx, jsc, "garbageCollect", ScriptCore::forceGC, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    //JS_DefineFunction(cx, jsc, "dumpRoot", ScriptCore::dumpRoot, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    //JS_DefineFunction(cx, jsc, "addGCRootObject", ScriptCore::addRootJS, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    //JS_DefineFunction(cx, jsc, "removeGCRootObject", ScriptCore::removeRootJS, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    //JS_DefineFunction(cx, jsc, "executeScript", ScriptCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );

    //// register some global functions
    //JS_DefineFunction(cx, global, "require", ScriptCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "log", ScriptCore::log, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "executeScript", ScriptCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "forceGC", ScriptCore::forceGC, 0, JSPROP_READONLY | JSPROP_PERMANENT);

    /*JS_DefineFunction(cx, global, "__getPlatform", JSBCore_platform, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "__getOS", JSBCore_os, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "__getVersion", JSBCore_version, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "__restartVM", JSB_core_restartVM, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );*/
}

static void sc_finalize(JSFreeOp *freeOp, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (global class)", obj);
}

static JSClass global_class = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, sc_finalize,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

ScriptCore::ScriptCore()
: m_runtime(NULL)
, m_context(NULL)
, m_global(NULL)
, m_debugGlobal(NULL)
{

}

ScriptCore::~ScriptCore()
{
    cleanup();
}

void ScriptCore::start() {
    // for now just this
    this->createGlobalContext();
    registerDefaultClasses(m_context,m_global);
}


void ScriptCore::cleanup()
{
    //localStorageFree();
    //removeAllRoots(m_context);
    if (m_context)
    {
        JS_DestroyContext(m_context);
        m_context = NULL;
    }
    if (m_runtime)
    {
        JS_DestroyRuntime(m_runtime);
        m_runtime = NULL;
    }
    JS_ShutDown();
    if (_js_log_buf) {
        free(_js_log_buf);
        _js_log_buf = NULL;
    }

   /* js_type_class_t* current, *tmp;
    HASH_ITER(hh, _js_global_type_ht, current, tmp)
    {
        HASH_DEL(_js_global_type_ht, current);
        free(current->jsclass);
        free(current);
    }
    HASH_CLEAR(hh, _js_global_type_ht);*/
}

void ScriptCore::reset()
{
    cleanup();
    start();
}


void ScriptCore::createGlobalContext() {
    if (this->m_context && this->m_runtime) {
        JS_DestroyContext(this->m_context);
        JS_DestroyRuntime(this->m_runtime);
        this->m_context = NULL;
        this->m_runtime = NULL;
    }
    // Removed from Spidermonkey 19.
    //JS_SetCStringsAreUTF8();
    this->m_runtime = JS_NewRuntime(8L * 1024L * 1024L, JS_USE_HELPER_THREADS);
    JS_SetGCParameter(m_runtime, JSGC_MAX_BYTES, 0xffffffff);
	
    this->m_context = JS_NewContext(m_runtime, 8192);
    JS_SetOptions(this->m_context, JSOPTION_TYPE_INFERENCE|JSOPTION_METHODJIT);
    JS_SetVersion(this->m_context, JSVERSION_LATEST);
    //JS_SetOptions(this->m_context, JS_GetOptions(this->m_context) & ~JSOPTION_METHODJIT);
    //JS_SetOptions(this->m_context, JS_GetOptions(this->m_context) & ~JSOPTION_METHODJIT_ALWAYS);
    JS_SetErrorReporter(this->m_context, ScriptCore::reportError);
#if defined(JS_GC_ZEAL) && defined(DEBUG)
    //JS_SetGCZeal(this->m_context, 2, JS_DEFAULT_ZEAL_FREQ);
#endif
    this->m_global = NewGlobalObject(m_context);
#if JSB_ENABLE_DEBUGGER
    JS_SetDebugMode(m_context, JS_TRUE);
#endif
    //for (std::vector<sc_register_sth>::iterator it = registrationList.begin(); it != registrationList.end(); it++) {
    //    sc_register_sth callback = *it;
    //    callback(this->m_context, this->m_global);
    //}
}

JSBool ScriptCore::evaluateString(const char *string, jsval *outVal, const char *filename , JSObject* global , JSContext* cx )
{
    return JS_EvaluateScript(cx, global, string, strlen(string),
                           filename, 0, outVal);
}

//JSBool ScriptCore::evalString(const char *string, jsval *outVal, const char *filename, JSContext* cx, JSObject* global)
//{
//    jsval rval;
//    if (cx == NULL)
//        cx = m_context;
//    if (global == NULL)
//        global = m_global;
//    JSScript* script = JS_CompileScript(cx, global, string, strlen(string), filename, 1);
//    if (script) {
//        // JSAutoCompartment ac(cx, global);
//        JSAutoCompartment ac(cx, global);
//        JSBool evaluatedOK = JS_ExecuteScript(cx, global, script, &rval);
//        if (JS_FALSE == evaluatedOK) {
//            fprintf(stderr, "(evaluatedOK == JS_FALSE)\n");
//        }
//        return evaluatedOK;
//    }
//    return JS_FALSE;
//}



JSBool ScriptCore::executeScriptFile(const char *path, JSObject* global, JSContext* cx)
{
    if (!path) {
        return false;
    }

    cocos2d::CCFileUtils *futil = cocos2d::CCFileUtils::sharedFileUtils();
    std::string rpath;
    if (path[0] == '/') {
        rpath = path;
    } else {
        rpath = futil->fullPathForFilename(path);
    }

    if (global == NULL) {
        global = m_global;
    }
    if (cx == NULL) {
        cx = m_context;
    }

    js::RootedObject obj(cx, global);
	JS::CompileOptions options(cx);
	options.setUTF8(true).setFileAndLine(rpath.c_str(), 1);
    
    // this will always compile the script, we can actually check if the script
    // was compiled before, because it can be in the global map
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    unsigned char *content = NULL;
    unsigned long contentSize = 0;

    content = (unsigned char*)CCString::createWithContentsOfFile(rpath.c_str())->getCString();
    contentSize = strlen((char*)content);
    // Not supported in SpiderMonkey 19.0
    //JSScript* script = JS_CompileScript(cx, global, (char*)content, contentSize, path, 1);
    JSScript *script = JS::Compile(cx, obj, options, (char*)content, contentSize);
#else
    // Removed in SpiderMonkey 19.0
    //JSScript* script = JS_CompileUTF8File(cx, global, rpath.c_str());
	JSScript *script = JS::Compile(cx, obj, options, rpath.c_str());
#endif
    JSBool evaluatedOK = false;
    if (script) {
        jsval rval;
        filename_script[path] = script;
        JSAutoCompartment ac(cx, global);
        evaluatedOK = JS_ExecuteScript(cx, global, script, &rval);
        if (JS_FALSE == evaluatedOK) {
            JS_ReportPendingException(cx);
        }
    }
    return evaluatedOK;
}

JSBool ScriptCore::executeCompiledScript(JSScript* script,jsval* outVal, JSObject* global , JSContext* cx)
{

    JSBool evaluatedOK = false;
    JSAutoCompartment ac(cx, global);
    evaluatedOK = JS_ExecuteScript(cx, global, script, outVal);
    if (JS_FALSE == evaluatedOK) {
        JS_ReportPendingException(cx);
    }
    return evaluatedOK;
}

JSScript* ScriptCore::CompileScriptFile(const char *path, JSObject* global , JSContext* cx )
{
    if (!path) {
        return false;
    }

    cocos2d::CCFileUtils *futil = cocos2d::CCFileUtils::sharedFileUtils();
    std::string rpath;
    if (path[0] == '/') {
        rpath = path;
    } else {
        rpath = futil->fullPathForFilename(path);
    }

    if (global == NULL) {
        global = m_global;
    }
    if (cx == NULL) {
        cx = m_context;
    }

    js::RootedObject obj(cx, global);
	JS::CompileOptions options(cx);
	options.setUTF8(true).setFileAndLine(rpath.c_str(), 1);
    
    // this will always compile the script, we can actually check if the script
    // was compiled before, because it can be in the global map
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    unsigned char *content = NULL;
    unsigned long contentSize = 0;

    content = (unsigned char*)CCString::createWithContentsOfFile(rpath.c_str())->getCString();
    contentSize = strlen((char*)content);
    // Not supported in SpiderMonkey 19.0
    //JSScript* script = JS_CompileScript(cx, global, (char*)content, contentSize, path, 1);
    JSScript *script = JS::Compile(cx, obj, options, (char*)content, contentSize);
#else
    // Removed in SpiderMonkey 19.0
    //JSScript* script = JS_CompileUTF8File(cx, global, rpath.c_str());
	JSScript *script = JS::Compile(cx, obj, options, rpath.c_str());
#endif
    return script;
}

JSScript* ScriptCore::CompileScriptString(const char *string, JSObject* global , JSContext* cx )
{
    if (global == NULL) {
        global = m_global;
    }
    if (cx == NULL) {
        cx = m_context;
    }

    js::RootedObject obj(cx, global);
	JS::CompileOptions options(cx);
	options.setUTF8(true).setFileAndLine("", 1);
    unsigned long len = strlen(string);
    // Not supported in SpiderMonkey 19.0
    //JSScript* script = JS_CompileScript(cx, global, (char*)content, contentSize, path, 1);
    JSScript *script = JS::Compile(cx, obj, options, string, len);
    return script;
}

void ScriptCore::executeJSFunctionWithThisObj(jsval thisObj, jsval callback,
                                                 jsval *data) {
    jsval retval;
    if(callback != JSVAL_VOID || thisObj != JSVAL_VOID) {
        JS_CallFunctionValue(m_context, JSVAL_TO_OBJECT(thisObj), callback, 1, data, &retval);
    }
}

void ScriptCore::reportError(JSContext *cx, const char *message, JSErrorReport *report)
{
    js_log("%s:%u:%s\n",
            report->filename ? report->filename : "<no filename=\"filename\">",
            (unsigned int) report->lineno,
            message);
};


JSBool ScriptCore::log(JSContext* cx, uint32_t argc, jsval *vp)
{
    if (argc > 0) {
        JSString *string = NULL;
        JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &string);
        if (string!=NULL) {
            JSStringWrapper wrapper(string,cx);
            js_log((char *)wrapper);
        }
    }
    return JS_TRUE;
}

JSBool ScriptCore::setReservedSpot(uint32_t i, JSObject *obj, jsval value) {
    JS_SetReservedSlot(obj, i, value);
    return JS_TRUE;
}

JSBool ScriptCore::executeScript(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
        jsval* argv = JS_ARGV(cx, vp);
        JSString* str = JS_ValueToString(cx, argv[0]);
        std::string path=JS_EncodeString(cx,str);
        JSBool res = false;
        if (argc == 2 && argv[1].isString()) {
            JSString* globalName = JSVAL_TO_STRING(argv[1]);
            std::string name=JS_EncodeString(cx,globalName);
            js::RootedObject* rootedGlobal = globals[name];
            if (rootedGlobal) {
                res = ScriptCore::getInstance()->executeScriptFile(path.c_str(), rootedGlobal->get());
            } else {
                JS_ReportError(cx, "Invalid global object: %s", name.c_str());
                return JS_FALSE;
            }
        } else {
            JSObject* glob = JS_GetGlobalForScopeChain(cx);
            res = ScriptCore::getInstance()->executeScriptFile(path.c_str(), glob);
        }
        return res;
    }
    return JS_TRUE;
}

JSBool ScriptCore::forceGC(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSRuntime *rt = JS_GetRuntime(cx);
    JS_GC(rt);
    return JS_TRUE;
}

static void dumpNamedRoot(const char *name, void *addr,  JSGCRootType type, void *data)
{
    CCLOG("Root: '%s' at %p", name, addr);
}

JSBool ScriptCore::dumpRoot(JSContext *cx, uint32_t argc, jsval *vp)
{
    // JS_DumpNamedRoots is only available on DEBUG versions of SpiderMonkey.
    // Mac and Simulator versions were compiled with DEBUG.
#if DEBUG
//    JSContext *_cx = ScriptCore::getInstance()->getGlobalContext();
//    JSRuntime *rt = JS_GetRuntime(_cx);
//    JS_DumpNamedRoots(rt, dumpNamedRoot, NULL);
//    JS_DumpHeap(rt, stdout, NULL, JSTRACE_OBJECT, NULL, 2, NULL);
#endif
    return JS_TRUE;
}

JSBool ScriptCore::addRootJS(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JSObject *o = NULL;
        if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "o", &o) == JS_TRUE) {
            if (JS_AddNamedObjectRoot(cx, &o, "from-js") == JS_FALSE) {
                LOGD("something went wrong when setting an object to the root");
            }
        }
        return JS_TRUE;
    }
    return JS_FALSE;
}

JSBool ScriptCore::removeRootJS(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JSObject *o = NULL;
        if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "o", &o) == JS_TRUE) {
            JS_RemoveObjectRoot(cx, &o);
        }
        return JS_TRUE;
    }
    return JS_FALSE;
}


void ScriptCore::string_report(jsval val) {
    if (JSVAL_IS_NULL(val)) {
        LOGD("val : (JSVAL_IS_NULL(val)");
        // return 1;
    } else if ((JSVAL_IS_BOOLEAN(val)) &&
               (JS_FALSE == (JSVAL_TO_BOOLEAN(val)))) {
        LOGD("val : (return value is JS_FALSE");
        // return 1;
    } else if (JSVAL_IS_STRING(val)) {
        JSString *str = JS_ValueToString(this->getGlobalContext(), val);
        if (NULL == str) {
            LOGD("val : return string is NULL");
        } else {
            LOGD("val : return string =\n%s\n", JS_EncodeString(m_context,str));
        }
    } else if (JSVAL_IS_NUMBER(val)) {
        double number;
        if (JS_FALSE ==
            JS_ValueToNumber(this->getGlobalContext(), val, &number)) {
            LOGD("val : return number could not be converted");
        } else {
            LOGD("val : return number =\n%f", number);
        }
    }
}

#pragma mark - Debug


JSBool jsGetScript(JSContext* cx, unsigned argc, jsval* vp)
{
    jsval* argv = JS_ARGV(cx, vp);
    if (argc == 1 && argv[0].isString()) {
        JSString* str = argv[0].toString();
        JSScript* script = filename_script[JS_EncodeString(cx,str)];
        if (script) {
            JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL((JSObject*)script));
        } else {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
        }
    }
    return JS_TRUE;
}

JSObject* NewGlobalObject(JSContext* cx, bool debug)
{
    JSObject* glob = JS_NewGlobalObject(cx, &global_class, NULL);
    if (!glob) {
        return NULL;
    }
    JSAutoCompartment ac(cx, glob);
    JSBool ok = JS_TRUE;
    ok = JS_InitStandardClasses(cx, glob);
    if (ok)
        JS_InitReflect(cx, glob);
    if (!ok)
        return NULL;

    return glob;
}

JSBool jsb_set_reserved_slot(JSObject *obj, uint32_t idx, jsval value)
{
    JSClass *klass = JS_GetClass(obj);
    unsigned int slots = JSCLASS_RESERVED_SLOTS(klass);
    if( idx >= slots )
        return JS_FALSE;

    JS_SetReservedSlot(obj, idx, value);

    return JS_TRUE;
}

JSBool jsb_get_reserved_slot(JSObject *obj, uint32_t idx, jsval& ret)
{
    JSClass *klass = JS_GetClass(obj);
    unsigned int slots = JSCLASS_RESERVED_SLOTS(klass);
    if( idx >= slots )
        return JS_FALSE;

    ret = JS_GetReservedSlot(obj, idx);

    return JS_TRUE;
}

NS_YHSCRIPT_END