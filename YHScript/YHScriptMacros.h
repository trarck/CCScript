#ifndef YHSCRIPT_MACROS_H_
#define YHSCRIPT_MACROS_H_

#define NS_YHSCRIPT_BEGIN                     namespace yhscript {
#define NS_YHSCRIPT_END                       }
#define USING_NS_YHSCRIPT                     using namespace yhscript

#if defined(DEBUG)
#define YHSCRIPT_PRECONDITION( condition, ...) do {							\
	if( ! (condition) ) {														\
        cocos2d::CCLog("jsb: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );			\
        cocos2d::CCLog(__VA_ARGS__);                                        \
		JSContext* globalContext = ScriptingCore::getInstance()->getGlobalContext();	\
		if( ! JS_IsExceptionPending( globalContext ) ) {						\
			JS_ReportError( globalContext, __VA_ARGS__ );							\
		}																		\
		return JS_FALSE;														\
	}																			\
} while(0)

#define YHSCRIPT_PRECONDITION2( condition, context, ret_value, ...) do {             \
    if( ! (condition) ) {														\
        cocos2d::CCLog("jsb: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );			\
        cocos2d::CCLog(__VA_ARGS__);                                        \
        if( ! JS_IsExceptionPending( context ) ) {							\
            JS_ReportError( context, __VA_ARGS__ );								\
        }																		\
        return ret_value;														\
    }                                                                           \
} while(0)

#define YHSCRIPT_ASSERT( condition, error_msg) do {										\
	if( ! (condition) ) {														\
		CCLOG("jsb: ERROR in %s: %s\n", __FUNCTION__, error_msg);				\
		return false;															\
	}																			\
	} while(0)
#else

#define JSB_PRECONDITION do{} while(0)
#define JSB_PRECONDITION2 do{} while(0)
#define ASSERT do{} while(0)

#endif //PRECONDITION

#endif //YHSCRIPT_MACROS_H_

