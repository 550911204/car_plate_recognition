#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "LocalPicStrategy.h"
#include"ContourIdentyStrategy.h"
#include"HoughSegStrategy.h"
#include"OCRStrategy.h"
#include<fstream>
#include <iostream>
using namespace  std;
using namespace cv;



int main()
{
	ifstream infile;
	infile.open("./config.txt");   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
	string strategy[4];
	for (int i = 0; i < 4; i++)
		getline(infile, strategy[i]);
	infile.close();             //关闭文件输入流 

	Mat image;
	//*********第一部分——加载图片*************//
	LoadPicStrategy* loadPic = (LoadPicStrategy*)ClassFactory::getInstance().GetClassByName(strategy[0]);
	image = loadPic->GetPic();
	//*********第二部分——车牌定位*************//
	LocatePlateStrategy* locatPlate = (LocatePlateStrategy*)ClassFactory::getInstance().GetClassByName(strategy[1]);
	locatPlate->SetImage(image);
	image = locatPlate->FindPlate();
	//*********第三部分——字符分割*************//
	SegmentsPlateStrategy* segPlate = (SegmentsPlateStrategy*)ClassFactory::getInstance().GetClassByName(strategy[2]);
	segPlate->SetImage(image);
	segPlate->SegmentsChar();
	//*********第四部分——字符识别*************//
	RecogCharStrategy* regChar = (RecogCharStrategy*)ClassFactory::getInstance().GetClassByName(strategy[3]);
	regChar->SetImage(segPlate->GetSingle());
	cout << regChar->RecChar() << endl;
	system("pause");
	return 0;
}


