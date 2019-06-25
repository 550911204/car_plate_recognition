#pragma once
#include "SegmentsPlateStrategy.h"
#include "hough_find_line.cpp"
#include<iostream>
using namespace std;
class HoughSegStrategy :
	public SegmentsPlateStrategy
{
public:
	HoughSegStrategy();
	~HoughSegStrategy();
	virtual void SegmentsChar();
protected:
	Mat MyThreshold(Mat& image, int type);		//¶þÖµ»¯
	Mat MyCanny(Mat& image);					//±ßÔµ¼ì²â
	Mat MyRectify(Mat& grey, Mat& contour);		//ÇãÐ±½ÃÕý
	Mat MyWipeBorder(Mat& image);				//È¥³ý±ß¿ò
	Mat MyRectPlate(Mat& image,int* pot);		//²Ã¼ô
	void MySegChar(Mat& image);					//·Ö¸î×Ö·û
};

