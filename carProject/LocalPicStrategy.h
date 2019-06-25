#pragma once
#include "LoadPicStrategy.h"
class LocalPicStrategy :
	public LoadPicStrategy
{
public:
	LocalPicStrategy();
	~LocalPicStrategy();
	virtual void LoadPic();
};