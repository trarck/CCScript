#include "ScriptCore.h"
NS_YHSCRIPT_BEGIN

class JSStringWrapper
{
	JSString*	string;
	const char*	buffer;
    JSContext* m_context;
public:
	JSStringWrapper() {
		buffer = NULL;
	}
	JSStringWrapper(JSString* str, JSContext* cx = NULL) {
		set(str, cx);
	}
	JSStringWrapper(jsval val, JSContext* cx = NULL) {
		set(val, cx);
	}
	~JSStringWrapper() {
		if (buffer) {
			//JS_free(ScriptingCore::getInstance()->getGlobalContext(), (void*)buffer);
            //delete buffer;
            JS_free(m_context,(void*)buffer);
		}
	}
	void set(jsval val, JSContext* cx) {
		if (val.isString()) {
			this->set(val.toString(), cx);
		} else {
			buffer = NULL;
		}
	}
	void set(JSString* str, JSContext* cx) {
		string = str;
		if (!cx) {
			cx = ScriptCore::getInstance()->getGlobalContext();
		}

        // JS_EncodeString isn't supported in SpiderMonkey ff19.0.
        buffer = JS_EncodeString(cx, string);
//        unsigned short* pStrUTF16 = (unsigned short*)JS_GetStringCharsZ(cx, str);
//        buffer = cc_utf16_to_utf8(pStrUTF16, -1, NULL, NULL);
        m_context=cx;
	}
	std::string get() {
        return buffer;
    }

	operator std::string() {
		return std::string(buffer);
	}
	operator char*() {
		return (char*)buffer;
	}
private:
	/* Copy and assignment are not supported. */
    JSStringWrapper(const JSStringWrapper &another);
    JSStringWrapper &operator=(const JSStringWrapper &another);
};

NS_YHSCRIPT_END