#include "LoadPicStrategy.h"



LoadPicStrategy::LoadPicStrategy()
{
}


LoadPicStrategy::~LoadPicStrategy()
{
}

Mat LoadPicStrategy::GetPic()
{
	imshow("ԭͼ", m_image);
	cvWaitKey(0);
	return m_image;
}

void LoadPicStrategy::LoadPic()
{
}
