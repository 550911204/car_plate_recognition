#include "ClassFactory.h"


ClassFactory::~ClassFactory()
{
}

void * ClassFactory::GetClassByName(string classname)
{
	map<string, PTRCreateObject>::const_iterator iter;
	iter = m_classMap.find(classname);
	if (iter == m_classMap.end())
		return NULL;
	else
		return iter->second();
}

void ClassFactory::registClass(string classname, PTRCreateObject method)
{
	m_classMap.insert(pair<string, PTRCreateObject>(classname, method));
}

ClassFactory & ClassFactory::getInstance()
{
	static ClassFactory sLo_factory;
	return sLo_factory;
}
