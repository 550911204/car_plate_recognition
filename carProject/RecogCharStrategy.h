#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include"Register.h"
using namespace cv;
//字符识别基类
class RecogCharStrategy
{
public:
	RecogCharStrategy();
	~RecogCharStrategy();
	virtual string RecChar()=0;
	void SetImage(Mat* img);
	string GetPlate();
protected:
	Mat* m_image;
	string m_plate;
};

