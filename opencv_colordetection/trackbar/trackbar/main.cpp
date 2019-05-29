#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

Mat srcImg;
Mat hsv_img;

int h_min=0, s_min=0, v_min=0;
int h_max=180, s_max=255, v_max=46;

void OnChange(int, void* param)
{
	Scalar hsv_min(h_min, s_min, v_min);
	Scalar hsv_max(h_max, s_max, v_max);
	Mat dstImg = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC3);
	inRange(hsv_img, hsv_min, hsv_max, dstImg);

	imshow("HSV", dstImg);
}

void main()
{
	srcImg = imread("G:\\Program Files\\VS\\vs_opencv_workspace\\video\\colordetection_1\\colordetection_1\\duck2.jpg");
	imshow("src", srcImg);
	cvtColor(srcImg, hsv_img, CV_BGR2HSV);  //转换到HSV颜色空间
	namedWindow("HSV", CV_WINDOW_AUTOSIZE);
	createTrackbar("h_min", "HSV", &h_min, 180, OnChange, 0);
	createTrackbar("s_min", "HSV", &s_min, 255, OnChange, 0);
	createTrackbar("v_min", "HSV", &v_min, 255, OnChange, 0);
	createTrackbar("h_max", "HSV", &h_max, 180, OnChange, 0);
	createTrackbar("s_max", "HSV", &s_max, 255, OnChange, 0);
	createTrackbar("v_max", "HSV", &v_max, 255, OnChange, 0);

	OnChange(h_min, 0);
	OnChange(s_min, 0);
	OnChange(v_min, 0);
	OnChange(h_max, 0);
	OnChange(s_max, 0);
	OnChange(v_max, 0);
 
	waitKey(0);
}