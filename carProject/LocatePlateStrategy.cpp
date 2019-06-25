#include "LocatePlateStrategy.h"

LocatePlateStrategy::LocatePlateStrategy()
{
}

LocatePlateStrategy::~LocatePlateStrategy()
{
}



Mat LocatePlateStrategy::GetPlate()
{
	return m_plateImage;
}

void LocatePlateStrategy::SetImage(Mat& img)
{
	m_image = img;
}
