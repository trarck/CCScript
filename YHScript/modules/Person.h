#ifndef YHSCRIPT_MODULES_PERSON_H_
#define YHSCRIPT_MODULES_PERSON_H_

#include "jsapi.h"
#include <string>

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
    static void registerPersonModule(JSContext *cx,JSObject *module);
    static JSObject* s_person_prototype;
};


	
#endif //YHSCRIPT_MODULES_PERSON_H_