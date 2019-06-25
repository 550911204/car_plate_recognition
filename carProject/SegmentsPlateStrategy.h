#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include"Register.h"
using namespace cv;
//·Ö¸î×Ö·û»ùÀà
class SegmentsPlateStrategy
{
public:
	SegmentsPlateStrategy();
	~SegmentsPlateStrategy();
	virtual void SegmentsChar()=0;
	void SetImage(Mat& img);
	Mat* GetSingle();
protected:
	Mat m_image;
	Mat m_singleChar[7];
};

