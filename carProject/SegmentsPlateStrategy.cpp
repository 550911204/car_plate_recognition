#include "SegmentsPlateStrategy.h"



SegmentsPlateStrategy::SegmentsPlateStrategy()
{
}


SegmentsPlateStrategy::~SegmentsPlateStrategy()
{
}


void SegmentsPlateStrategy::SetImage(Mat& img)
{
	m_image = img;
}

Mat * SegmentsPlateStrategy::GetSingle()
{
	return m_singleChar;
}
