#include "ContourIdentyStrategy.h"
#include<iostream>
using namespace std;

REGISTER(ContourIdentyStrategy);
ContourIdentyStrategy::ContourIdentyStrategy()
{
}


ContourIdentyStrategy::~ContourIdentyStrategy()
{
}

Mat ContourIdentyStrategy::FindPlate()
{
	Mat img_grey;
	cvtColor(m_image, img_grey, CV_BGR2GRAY);//����Ϊ�Ҷ�ͼ��
	Mat img_gaussian;
	img_gaussian = MyGaussianBlur(img_grey);//��˹ģ�� ����
	Mat img_sobel;
	img_sobel = MySobel(img_gaussian);//��Ե���
	Mat img_threshold;
	img_threshold = MyThreshold(img_sobel,0);//��ֵ��
	Mat img_thresGaussian;
	img_thresGaussian = MyGaussianBlur(img_threshold);//��˹ģ��
	Mat img_thres;
	img_thres = MyThreshold(img_thresGaussian,1);//��ֵ��
	Mat img_morphClose;
	img_morphClose = MyMorph(img_thres, 0);//������
	Mat img_morphOpen;
	img_morphOpen = MyMorph(img_morphClose, 1);//������
	m_plateImage = FindInsidiousContour(img_morphOpen);//Ѱ�ҳ�������
	return m_plateImage;
}

Mat ContourIdentyStrategy::MyGaussianBlur(Mat& image)
{
	Mat gaussianBlur;
	GaussianBlur(image, gaussianBlur, Size(9, 9), 3.0);
	imshow("��˹", gaussianBlur);
	cvWaitKey(0);
	return gaussianBlur;
}

Mat ContourIdentyStrategy::MySobel(Mat& image)
{
	Mat sobelimg;
	Sobel(image, sobelimg, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	imshow("ͻ����ֱ��Ե", sobelimg);
	cvWaitKey(0);
	return sobelimg;
}

Mat ContourIdentyStrategy::MyThreshold(Mat& image, int type)
{
	Mat thresholdimg;
	if(0 == type)
		threshold(image, thresholdimg, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
	else if(1 == type)
		threshold(image, thresholdimg, 0, 255, CV_THRESH_BINARY);
	imshow("��ֵ��", thresholdimg);
	cvWaitKey(0);
	return thresholdimg;
}

Mat ContourIdentyStrategy::MyMorph(Mat& image, int type)
{
	Mat morpgImag;
	if (0 == type) {//������
		Mat element = getStructuringElement(MORPH_RECT, Size(10, 4));
		morphologyEx(image, morpgImag, CV_MOP_CLOSE, element);
		imshow("������", morpgImag);
		cvWaitKey(0);
	}
	else if (1 == type) {//������
		Mat element(8, 8, CV_8U, Scalar(1));
		morphologyEx(image, morpgImag, MORPH_OPEN, element);
		imshow("������", morpgImag);
		cvWaitKey(0);
	}
	return morpgImag;
}

Mat ContourIdentyStrategy::FindInsidiousContour(Mat& image)
{
	//Ѱ��Ǳ������
	vector<vector<Point>> contours;
	findContours(image, contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	Mat insidious;
	m_image.copyTo(insidious);
	drawContours(insidious, contours,-1,Scalar(0, 0, 255),1);
	imshow("��������", insidious);
	cvWaitKey(0);
	// �ų��ǳ��ƵĿ�������
	vector<vector<Point> >::iterator itc = contours.begin();
	vector<Rect> rects;
	while (itc != contours.end()){
		// minAreaRect����������С��Χ��ת����
		Rect mr = boundingRect(Mat(*itc));
		Mat resultPlate;
		m_image.copyTo(resultPlate);
		drawContours(resultPlate, Mat(*itc),-1,Scalar(0, 0, 255),1);
		if (!VerifySizes(mr, image))
			itc = contours.erase(itc);
		else {
			++itc;
			rects.push_back(mr);
		}
	}
	Mat plate;
	m_image.copyTo(plate);
	drawContours(plate, contours,-1,Scalar(0, 0, 255),1);
	imshow("��λ����", plate);
	cvWaitKey(0);
	vector<Rect>::iterator it = rects.begin();
	plate = m_image(*it);
	m_plateImage = plate;
	imshow("��ȡ������", plate);
	cvWaitKey(0);
	return plate;
}

int ContourIdentyStrategy::VerifySizes(Rect m, Mat & input)
{
	double k = m.width / m.height;//����
	double per = (double)m.area() / (input.cols*input.rows);//���ռ����
	double  height_per = (double)m.y / input.cols;//�ߵı�
	if (k>2.1 && k<3.90 && per>0.02 && per<0.04 && height_per<0.9 && height_per>0.7)
		return 1;
	else
		return 0;
}