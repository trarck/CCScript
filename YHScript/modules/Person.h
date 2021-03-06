#ifndef YHSCRIPT_MODULES_PERSON_H_
#define YHSCRIPT_MODULES_PERSON_H_

#include "jsapi.h"
#include <string>
#include "../Module.h"

NS_YHSCRIPT_MODULES_BEGIN

class Person
{

public:
	
	Person();
	~Person();
	
	int getAge(){return m_age;}
	void setAge(int newAge){m_age=newAge;}
	std::string getName(){return m_name;}
	void setName(std::string newName){m_name=newName;}

private:
	int m_age;
	std::string m_name;
	
};

class PersonModule
{
public:
    static void registerModule(JSContext *cx,JSObject *module);
    static JSObject* s_modulePrototype;
    static Module s_moduleData;
};

NS_YHSCRIPT_MODULES_END
	
#endif //YHSCRIPT_MODULES_PERSON_H_