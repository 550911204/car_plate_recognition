#pragma once
#include <map>
#include <string>
using namespace std;
typedef void* (*PTRCreateObject)(void);
//π§≥ß¿‡
class ClassFactory
{
public:
	~ClassFactory();
	void* GetClassByName(string classname);
	void registClass(string classname, PTRCreateObject method);
	static ClassFactory& getInstance();
private:
	ClassFactory() {};
	map<string, PTRCreateObject>m_classMap;
};

