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
	infile.open("./config.txt");   //���ļ����������ļ��������� 
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 
	string strategy[4];
	for (int i = 0; i < 4; i++)
		getline(infile, strategy[i]);
	infile.close();             //�ر��ļ������� 

	Mat image;
	//*********��һ���֡�������ͼƬ*************//
	LoadPicStrategy* loadPic = (LoadPicStrategy*)ClassFactory::getInstance().GetClassByName(strategy[0]);
	image = loadPic->GetPic();
	//*********�ڶ����֡������ƶ�λ*************//
	LocatePlateStrategy* locatPlate = (LocatePlateStrategy*)ClassFactory::getInstance().GetClassByName(strategy[1]);
	locatPlate->SetImage(image);
	image = locatPlate->FindPlate();
	//*********�������֡����ַ��ָ�*************//
	SegmentsPlateStrategy* segPlate = (SegmentsPlateStrategy*)ClassFactory::getInstance().GetClassByName(strategy[2]);
	segPlate->SetImage(image);
	segPlate->SegmentsChar();
	//*********���Ĳ��֡����ַ�ʶ��*************//
	RecogCharStrategy* regChar = (RecogCharStrategy*)ClassFactory::getInstance().GetClassByName(strategy[3]);
	regChar->SetImage(segPlate->GetSingle());
	cout << regChar->RecChar() << endl;
	system("pause");
	return 0;
}


