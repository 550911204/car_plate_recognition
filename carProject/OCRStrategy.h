#pragma once
#include "RecogCharStrategy.h"

class OCRStrategy :
	public RecogCharStrategy
{
public:
	OCRStrategy();
	~OCRStrategy();
	virtual string RecChar();
};

