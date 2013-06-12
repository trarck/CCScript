//
//  ScriptCore.h
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef YHSCRIPT_SCRIPTCORE_H_
#define YHSCRIPT_SCRIPTCORE_H_

#include <assert.h>
#include "cocos2d.h"
#include "jsapi.h"
#include "YHScriptMacros.h"

NS_YHSCRIPT_BEGIN

class ScriptCore
{

public:
	~ScriptCore();

	static ScriptCore *getInstance() {
		static ScriptCore* pInstance = NULL;
        if (pInstance == NULL) {
            pInstance = new ScriptCore();
        }
		return pInstance;
	};

    /**
	 * initialize everything
	 */
	void start();

	/**
	 * cleanup everything
	 */
	void cleanup();

	/**
	 * cleanup everything then initialize everything
	 */
	void reset();

	/**
	 * Will create a new context. If one is already there, it will destroy the old context
	 * and create a new one.
	 */
	void createGlobalContext();

    /**
	 * will eval the specified string
	 * @param string The string with the javascript code to be evaluated
	 * @param outVal The jsval that will hold the return value of the evaluation.
	 * Can be NULL.
	 */
	JSBool evaluateString(const char *string, jsval *outVal, const char *filename , JSObject* global , JSContext* cx );

    JSBool evaluateString(const char *string, jsval *outVal, const char *filename , JSObject* global){
        return evaluateString(string,outVal,filename,global,m_context);
    }

    JSBool evaluateString(const char *string, jsval *outVal, const char *filename ){
        return evaluateString(string,outVal,filename,m_global,m_context);
    }

    JSBool evaluateString(const char *string, jsval *outVal){
        return evaluateString(string,outVal,"");
    }

    JSBool evaluateString(const char *string){
        jsval rval;
        return evaluateString(string,&rval);
    }

	/**
	 * will run the specified string
	 * @param string The path of the script to be run
	 */
	JSBool executeScriptFile(const char *path, JSObject* global , JSContext* cx );

    JSBool executeScriptFile(const char *path, JSObject* global )
    {
         return executeScriptFile(path,global,m_context);
    }
    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    JSBool executeScriptFile(const char* path) { return executeScriptFile(path,m_global,m_context); }

     /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    JSBool executeCompiledScript(JSScript* script,jsval* outVal, JSObject* global , JSContext* cx);

    JSBool executeCompiledScript(JSScript* script,jsval* outVal, JSObject* global){
        return executeCompiledScript(script,outVal,global,m_context);
    }
    
    JSBool executeCompiledScript(JSScript* script,jsval* outVal){
        return executeCompiledScript(script,outVal,m_global,m_context);
    }

    JSBool executeCompiledScript(JSScript* script){
        jsval outVal;
        return executeCompiledScript(script,&outVal);
    }

    JSScript* CompileScriptFile(const char *path, JSObject* global , JSContext* cx );

    JSScript* CompileScriptString(const char *string, JSObject* global , JSContext* cx );
    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
	virtual int executeGlobalFunction(const char* functionName) { return 0; }

    void executeJSFunctionWithThisObj(jsval thisObj, jsval callback,jsval *data);

    /**
	 * @param cx
	 * @param message
	 * @param report
	 */
	static void reportError(JSContext *cx, const char *message, JSErrorReport *report);

	/**
	 * Log something using CCLog
	 * @param cx
	 * @param argc
	 * @param vp
	 */
	static JSBool log(JSContext *cx, uint32_t argc, jsval *vp);

    JSBool setReservedSpot(uint32_t i, JSObject *obj, jsval value);

	/**
	 * run a script from script :)
	 */
	static JSBool executeScript(JSContext *cx, uint32_t argc, jsval *vp);

	/**
	 * Force a cycle of GC
	 * @param cx
	 * @param argc
	 * @param vp
	 */
	static JSBool forceGC(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool dumpRoot(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool addRootJS(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool removeRootJS(JSContext *cx, uint32_t argc, jsval *vp);

    
	/**
	 * @return the global context
	 */
	JSContext* getGlobalContext() {return m_context;}

	JSObject* getDebugGlobal() { return m_debugGlobal; }
	JSObject* getGlobalObject() { return m_global; }
    

 private:
     
	ScriptCore();

    void string_report(jsval val);

    JSRuntime* m_runtime;
	JSContext* m_context;
	JSObject * m_global;
	JSObject * m_debugGlobal;

};

JSObject* NewGlobalObject(JSContext* cx, bool debug = false);
JSBool jsStartDebugger(JSContext* cx, unsigned argc, jsval* vp);
JSBool jsGetScript(JSContext* cx, unsigned argc, jsval* vp);

NS_YHSCRIPT_END

#endif //YHSCRIPT_SCRIPTCORE_H_
