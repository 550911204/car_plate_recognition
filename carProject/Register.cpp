#include "Register.h"


Register::Register(string classname, PTRCreateObject ptrCreate)
{
	ClassFactory::getInstance().registClass(classname, ptrCreate);
}

Register::~Register()
{
}
