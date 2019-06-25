#include "HoughSegStrategy.h"
#include <string>

REGISTER(HoughSegStrategy);
HoughSegStrategy::HoughSegStrategy()
{
}


HoughSegStrategy::~HoughSegStrategy()
{
}

void HoughSegStrategy::SegmentsChar()
{
	Mat img_grey;
	cvtColor(m_image, img_grey, CV_BGR2GRAY);//����Ϊ�Ҷ�ͼ��
	Mat img_threshold;
	img_threshold = MyThreshold(img_grey, 0);//��ֵ��
	erode(img_threshold, img_threshold, Mat());//��ʴ����
	Mat img_contour;
	img_contour = MyCanny(img_grey);//��Ե���
	Mat img_fix;
	img_fix = MyRectify(img_grey, img_contour);//��б����
	Mat img_fixedThres;
	img_fixedThres = MyThreshold(img_fix, 0);
	Mat img_finalPlate;
	img_finalPlate = MyWipeBorder(img_fixedThres);
	MySegChar(img_finalPlate);
}


Mat HoughSegStrategy::MyThreshold(Mat& image, int type)
{
	Mat thresholdimg;
	if (0 == type)
		threshold(image, thresholdimg, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
	else if (1 == type)
		threshold(image, thresholdimg, 0, 255, CV_THRESH_BINARY);
	imshow("��ֵ��", thresholdimg);
	cvWaitKey(0);
	return thresholdimg;
}

Mat HoughSegStrategy::MyCanny(Mat& image)
{
	Mat result;
	Canny(image, result, 125, 350);
	imshow("��Ե���", result);
	cvWaitKey(0);
	return result;
}

Mat HoughSegStrategy::MyRectify(Mat& grey, Mat& contour)
{
	LineFinder finder;
	finder.setMinVote(70); //������СͶƱ��
	finder.setLineLengthAndGap(100, 25);  //// ������С�߶γ��Ⱥ��߶μ�����̶�  
	vector<Vec4i> lines = finder.findLines(contour); //Ѱ���߶�
	double * d = new double[lines.size()];
	Vec4i Maxline = finder.findMaxline(lines, lines.size(), d, 0);
	double angle = fastAtan2(Maxline[3] - Maxline[1], Maxline[2] - Maxline[0]);
	Point2f center_point(grey.cols / 2, grey.rows / 2);
	Mat rotateMat = getRotationMatrix2D(center_point, angle, 1.0);//��ת
	warpAffine(grey, grey, rotateMat, grey.size());//��ת
	imshow("��бУ��", grey);
	cvWaitKey(0);
	return grey;
}

Mat HoughSegStrategy::MyWipeBorder(Mat& image)
{
	//ȥ���߿�
	int imgLR[100] = { 0 };
	int imgTop = 0; int imgBottom = 0;
	for (int ht = 0; ht < image.rows; ht++){//��λ��߽�
		for (int wt = 0; wt < image.cols; wt++){
			if (image.at<uchar>(ht, wt) != 0)
				imgLR[ht]++;
		}
		if (imgLR[ht] > 10){
			imgTop = ht;
			break;
		}
	}
	for (int ht = image.rows - 1; ht>0; ht--){//��λ�ұ߽�
		for (int wt = 0; wt < image.cols; wt++){
			if (image.at<uchar>(ht, wt) == 255)
				imgLR[ht]++;
		}
		if (imgLR[ht] > 30){
			imgBottom = ht;
			break;
		}
	}
	int imgR_w[350] = { 0 };
	int imgRight = 0;		int imgLeft = 0;
	for (int wt_new = 2; wt_new < image.cols; wt_new++){//��λ�ϱ߽�
		for (int ht_new = imgTop + 15; ht_new < imgBottom; ht_new++){
			if (255 == image.at<uchar>(ht_new, wt_new))
				imgR_w[wt_new]++;
		}
		if ((imgR_w[wt_new - 2] + imgR_w[wt_new - 1] + imgR_w[wt_new])>10){
			imgLeft = wt_new;
			break;
		}
	}
	for (int wt_new = image.cols - 3; wt_new >0; wt_new--){//��λ�±߽�
		for (int ht_new = imgTop + 15; ht_new < imgBottom; ht_new++){
			if (255 == image.at<uchar>(ht_new, wt_new))
				imgR_w[wt_new]++;
		}
		if ((imgR_w[wt_new] + imgR_w[wt_new + 1] + imgR_w[wt_new + 2])>10){
			imgRight = wt_new - 3;
			break;
		}
	}
	Mat plateWipe;
	int potLR[4] = { imgLeft + 5, imgTop + 8, imgRight - (imgLeft + 5), (imgBottom - (imgTop + 10)) };
	plateWipe = MyRectPlate(image, potLR);
	GaussianBlur(plateWipe, plateWipe, Size(3, 3), 3.0);
	threshold(plateWipe, plateWipe, 0, 255, CV_THRESH_OTSU);
	//ȥ��í��
	int imgRow[100] = { 0 };int imgCol[350] = { 0 };
	int imgT = 0;int	imgB = 0;
	for (int ht = 0; ht <plateWipe.rows; ht++){//��λ�ϱ߽�
		for (int wt = 0; wt < plateWipe.cols; wt++){
			if (plateWipe.at<uchar>(ht, wt) == 255)
				imgRow[ht]++;
		}
		if (imgRow[ht] > 30){
			imgT = ht;
			break;
		}
	}
	for (int ht = plateWipe.rows - 1; ht>0; ht--){//��λ�±߽�
		for (int wt = 0; wt < plateWipe.cols; wt++){
			if (plateWipe.at<uchar>(ht, wt) == 255)
				imgCol[ht]++;
		}
		if (imgCol[ht] > 20){
			imgB = ht;
			break;
		}
	}
	int potTB[4] = { 0, imgT, plateWipe.cols, imgB - imgT };
	Mat img_result;
	img_result = MyRectPlate(plateWipe, potTB);
	return img_result;
}

Mat HoughSegStrategy::MyRectPlate(Mat& image,int* pot)
{
	Mat result;
	result = image(Rect(pot[0], pot[1], pot[2], pot[3]));
	imshow("ȥ���߿�", result);
	cvWaitKey(0);
	return result;
}
 
void HoughSegStrategy::MySegChar(Mat& image)
{
	bool lab = false;//�Ƿ����һ���ַ��ָ�״̬
	int xnum = 0;
	int rect_left;
	int rect_right;
	for (int wt = 0; wt < image.cols; wt++){
		int count = 0;
		for (int ht = 0; ht < image.rows; ht++){
			if ((255 == image.at<uchar>(ht, wt)))
				count++;
		}
		if (!lab && (count>5)){
			rect_left = wt;
			lab = true;
		}
		if (lab && (count<5) && (wt>(rect_left + 15)) && (xnum<7)){
			rect_right = wt;
			lab = false;
			m_singleChar[xnum] = image(Rect(rect_left, 0, rect_right - rect_left + 1, image.rows - 1));
			imshow("Char NO:" + std::to_string(xnum), m_singleChar[xnum]);
			cvWaitKey(0);
			xnum++;
		}
	}
}

