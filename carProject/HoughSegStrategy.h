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
	Mat MyThreshold(Mat& image, int type);		//��ֵ��
	Mat MyCanny(Mat& image);					//��Ե���
	Mat MyRectify(Mat& grey, Mat& contour);		//��б����
	Mat MyWipeBorder(Mat& image);				//ȥ���߿�
	Mat MyRectPlate(Mat& image,int* pot);		//�ü�
	void MySegChar(Mat& image);					//�ָ��ַ�
};

