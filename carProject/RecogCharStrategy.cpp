#include "RecogCharStrategy.h"



RecogCharStrategy::RecogCharStrategy()
{
}


RecogCharStrategy::~RecogCharStrategy()
{
}

void RecogCharStrategy::SetImage(Mat* img)
{
	m_image = img;
}

string RecogCharStrategy::GetPlate()
{
	return m_plate;
}
