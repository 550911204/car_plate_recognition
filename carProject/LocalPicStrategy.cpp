#include "LocalPicStrategy.h"



REGISTER(LocalPicStrategy);
LocalPicStrategy::LocalPicStrategy()
{
	this->LoadPic();
}


LocalPicStrategy::~LocalPicStrategy()
{
}

void LocalPicStrategy::LoadPic()
{
	m_image = imread(".\\zz\\41.jpg");
}

