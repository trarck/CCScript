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

class ScriptCore
{
	JSRuntime* m_runtime;
	JSContext* m_context;
	JSObject * m_global;
	JSObject * m_debugGlobal;

	ScriptCore();
public:
	~ScriptCore();

	static ScriptCore *getInstance() {
		static ScriptCore* pInstance = NULL;
        if (pInstance == NULL) {
            pInstance = new ScriptCore();
        }
		return pInstance;
	};

	void executeJSFunctionWithThisObj(jsval thisObj, jsval callback,sval *data)
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is excuted correctly.
     @return other if the string is excuted wrongly.
     */
	int executeString(const char* codes) { return 0; }

    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    virtual  int executeScriptFile(const char* filename) { return 0; }

    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
	virtual int executeGlobalFunction(const char* functionName) { return 0; }

	/**
	 * will eval the specified string
	 * @param string The string with the javascript code to be evaluated
	 * @param outVal The jsval that will hold the return value of the evaluation.
	 * Can be NULL.
	 */
	JSBool evalString(const char *string, jsval *outVal, const char *filename = NULL, JSContext* cx = NULL, JSObject* global = NULL);

	/**
	 * will run the specified string
	 * @param string The path of the script to be run
	 */
	JSBool runScript(const char *path, JSObject* global = NULL, JSContext* cx = NULL);

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
	 * @return the global context
	 */
	JSContext* getGlobalContext() {
		return m_context;
	};

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
	 * enable the debug environment
	 */
	void debugProcessInput(std::string str);
	void enableDebugger();
	JSObject* getDebugGlobal() { return m_debugGlobal; }
	JSObject* getGlobalObject() { return m_global; }
    
 private:
    void string_report(jsval val);
};

// some utility functions
// to native
JSBool jsval_to_int32( JSContext *cx, jsval vp, int32_t *ret );
JSBool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *ret );
JSBool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *ret );
JSBool jsval_to_long_long(JSContext *cx, jsval v, long long* ret);
JSBool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret);

// from native
jsval int32_to_jsval( JSContext *cx, int32_t l);
jsval uint32_to_jsval( JSContext *cx, uint32_t number );
jsval long_long_to_jsval(JSContext* cx, long long v);
jsval std_string_to_jsval(JSContext* cx, std::string& v);
jsval c_string_to_jsval(JSContext* cx, const char* v, size_t length = -1);

JSObject* NewGlobalObject(JSContext* cx, bool debug = false);
JSBool jsStartDebugger(JSContext* cx, unsigned argc, jsval* vp);
JSBool jsGetScript(JSContext* cx, unsigned argc, jsval* vp);

JSBool JSBDebug_StartDebugger(JSContext* cx, unsigned argc, jsval* vp);
JSBool JSBDebug_BufferRead(JSContext* cx, unsigned argc, jsval* vp);
JSBool JSBDebug_BufferWrite(JSContext* cx, unsigned argc, jsval* vp);
JSBool JSBDebug_LockExecution(JSContext* cx, unsigned argc, jsval* vp);
JSBool JSBDebug_UnlockExecution(JSContext* cx, unsigned argc, jsval* vp);

#endif //YHSCRIPT_SCRIPTCORE_H_
