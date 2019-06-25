#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include"Register.h"
using namespace cv;
//¼ÓÔØÍ¼Æ¬»ùÀà
class LoadPicStrategy
{
public:
	LoadPicStrategy();
	~LoadPicStrategy();
	Mat GetPic();
	virtual void LoadPic();
protected:
	Mat m_image;
};
