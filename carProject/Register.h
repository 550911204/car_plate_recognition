#pragma once
#include"ClassFactory.h"
//×¢²áÆ÷Àà
class Register
{
public:
	Register(string classname, PTRCreateObject ptrCreate);
	~Register();
};

#define REGISTER(classname)									\
	classname* objectCreator##classname(){					\
		return new classname;								\
	}														\
	Register g_creatorRegister##classname(					\
		#classname,(PTRCreateObject)objectCreator##classname)	