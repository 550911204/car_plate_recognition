#pragma once
#include "LocatePlateStrategy.h"
class ContourIdentyStrategy :
	public LocatePlateStrategy
{
public:
	ContourIdentyStrategy();
	~ContourIdentyStrategy();
	virtual Mat FindPlate();
protected:
	Mat MyGaussianBlur(Mat& image);//高斯模糊
	Mat MySobel(Mat& image);//边缘检测
	Mat MyThreshold(Mat& image, int type);//二值化
	Mat MyMorph(Mat& image, int type);//开闭运算
	Mat FindInsidiousContour(Mat& image);//寻找潜在轮廓
	int VerifySizes(Rect m, Mat& input);//筛选轮廓
};

