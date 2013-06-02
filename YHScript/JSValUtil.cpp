//
//  ScriptCore.cpp
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include "JSValUtil.h"
#include <jsfriendapi.h>

NS_YHSCRIPT_BEGIN

JSBool jsval_to_int32( JSContext *cx, jsval vp, int32_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    YHSCRIPT_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    YHSCRIPT_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    *outval = (int32_t)dp;

    return ok;
}

JSBool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    YHSCRIPT_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    YHSCRIPT_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    *outval = (uint32_t)dp;

    return ok;
}

JSBool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    YHSCRIPT_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    YHSCRIPT_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    *outval = (uint16_t)dp;

    return ok;
}

JSBool jsval_to_long_long(JSContext *cx, jsval vp, long long* r) {
	JSObject *tmp_arg;
	JSBool ok = JS_ValueToObject( cx, vp, &tmp_arg );
	YHSCRIPT_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
	YHSCRIPT_PRECONDITION2( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, JS_FALSE, "Not a TypedArray object");
	YHSCRIPT_PRECONDITION2( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(long long), cx, JS_FALSE, "Invalid Typed Array length");
	
	uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
	long long ret =  arg_array[0];
	ret = ret << 32;
	ret |= arg_array[1];
	
	*r = ret;
	return JS_TRUE;
}

JSBool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret) {
    JSString *tmp = JS_ValueToString(cx, v);
    YHSCRIPT_PRECONDITION2(tmp, cx, JS_FALSE, "Error processing arguments");

    *ret = JS_EncodeString(cx,tmp);
    return JS_TRUE;
}


// From native type to jsval
jsval int32_to_jsval( JSContext *cx, int32_t number )
{
    return INT_TO_JSVAL(number);
}

jsval uint32_to_jsval( JSContext *cx, uint32_t number )
{
    return UINT_TO_JSVAL(number);
}

jsval long_long_to_jsval(JSContext* cx, long long v) {
    JSObject *tmp = JS_NewUint32Array(cx, 2);
    uint32_t *data = (uint32_t *)JS_GetArrayBufferViewData(tmp);
    data[0] = ((uint32_t *)(&v))[0];
    data[1] = ((uint32_t *)(&v))[1];
    return OBJECT_TO_JSVAL(tmp);
}

jsval std_string_to_jsval(JSContext* cx, std::string& v) {
    return c_string_to_jsval(cx, v.c_str());
}

jsval c_string_to_jsval(JSContext* cx, const char* v, size_t length /* = -1 */) {
    if (v == NULL) {
        return JSVAL_NULL;
    }
    jsval ret = JSVAL_NULL;

    JSString* str=JS_NewStringCopyN(cx,v,length);

    if (str) {
        ret = STRING_TO_JSVAL(str);
    }
    return ret;
}

NS_YHSCRIPT_END