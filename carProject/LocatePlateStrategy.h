#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include"Register.h"
using namespace cv;
class LocatePlateStrategy
{
public:
	LocatePlateStrategy();
	~LocatePlateStrategy();
	virtual Mat FindPlate()=0;
	Mat GetPlate();
	void SetImage(Mat& img);
protected:
	Mat m_image;
	Mat m_plateImage;
};

