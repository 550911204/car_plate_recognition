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
	Mat MyGaussianBlur(Mat& image);//��˹ģ��
	Mat MySobel(Mat& image);//��Ե���
	Mat MyThreshold(Mat& image, int type);//��ֵ��
	Mat MyMorph(Mat& image, int type);//��������
	Mat FindInsidiousContour(Mat& image);//Ѱ��Ǳ������
	int VerifySizes(Rect m, Mat& input);//ɸѡ����
};

