#ifndef LINEF
#define LINEF


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>

using namespace  std;
using namespace cv;

# define PI 3.1415926
class LineFinder {
private:
	// 直线对应的点参数向量   
	std::vector<cv::Vec4i> lines;
	//步长   
	double deltaRho;
	double deltaTheta;
	// 判断是直线的最小投票数   
	int minVote;
	// 判断是直线的最小长度   
	double minLength;
	// 同一条直线上点之间的距离容忍度   
	double maxGap;
public:
	//初始化   
	LineFinder() : deltaRho(1), deltaTheta(PI / 180),
		minVote(10), minLength(0.), maxGap(0.) {}
	// 设置步长   
	void setAccResolution(double dRho, double dTheta) {
		deltaRho = dRho;
		deltaTheta = dTheta;
	}
	// 设置最小投票数   
	void setMinVote(int minv) {
		minVote = minv;
	}
	// 设置最小线段长度和线段间距容忍度   
	void setLineLengthAndGap(double length, double gap) {
		minLength = length;
		maxGap = gap;
	}

	//寻找线段   
	std::vector<cv::Vec4i> findLines(cv::Mat& binary) {
		lines.clear();
		cv::HoughLinesP(binary, lines, deltaRho, deltaTheta, minVote, minLength, maxGap);
		return lines;
	}
	//寻找lines中的最大线段
	cv::Vec4i findMaxline(std::vector<cv::Vec4i> lines, int n, double *d, int k)
	{

		for (int i = 0; i<n; i++)
		{
			Vec4i L = lines[i];
			d[i] = sqrtf((L[0] - L[2]) ^ 2 + (L[1] - L[3]) ^ 2);
		}
		for (int i = 1; i<n; i++)
		{
			double temp = d[0];
			if (d[i]>temp)
				k = i;
		}
		return lines[k];
	}
	// 画线段   
	void drawDetectedLines(cv::Mat &image, cv::Scalar color = cv::Scalar(255, 255, 255))
	{
		std::vector<cv::Vec4i>::const_iterator it2 = lines.begin();
		while (it2 != lines.end())
		{
			cv::Point pt1((*it2)[0], (*it2)[1]);
			cv::Point pt2((*it2)[2], (*it2)[3]);
			cv::line(image, pt1, pt2, color);
			++it2;
		}
	}
};
#endif