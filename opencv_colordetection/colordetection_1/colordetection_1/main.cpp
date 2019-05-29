  #include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

/////red hsv min value
int h_min = 0;
int s_min = 145;
int v_min =253;
///red hsv max value
int h_max =10;
int s_max = 255;
int v_max = 255;


/////red hsv min value
//int h_min = 0;
//int s_min = 100;
//int v_min =100;
/////red hsv max value
//int h_max =10;
//int s_max = 255;
//int v_max = 255;

///green
//int h_min = 52;
//int s_min = 101;
//int v_min =114;
/////green hsv max value
//int h_max =77;
//int s_max = 255;
//int v_max = 255;
///green hsv min value
//int h_min = 35;
//int s_min = 110;
//int v_min =106;
/////green hsv max value
//int h_max =77;
//int s_max = 255;
//int v_max = 255;


///blue hsv min value
//int h_min = 90;
//int s_min = 100;
//int v_min =100;
/////blue hsv max value
//int h_max =120;
//int s_max = 255;
//int v_max = 255;
//



void main()
{
	VideoCapture cap;
	cap.open(0);  //������ͷ

	if(!cap.isOpened())  //�ж�����ͷ�Ƿ�� 
		return; 
	 
	Mat srcImg;
	while(1)
	{
	
	  cap>>srcImg;
	  if(srcImg.empty())
		 break;
      //imshow("video", srcImg);

	///ʶ��ͼƬ����ɫ����
	//Mat srcImg = imread("G:\\Program Files\\VS\\vs_opencv_workspace\\video\\colordetection_1\\colordetection_1\\rgb.jpg");
	//Mat srcImg = imread("G:\\Program Files\\VS\\vs_opencv_workspace\\video\\colordetection_1\\colordetection_1\\duck2.jpg");
	//Mat srcImg = imread("G:\\Program Files\\VS\\vs_opencv_workspace\\video\\colordetection_1\\colordetection_1\\color1.jpg");
	


	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();
	Mat hsv_img;  //�洢HSVͼ��
	cvtColor(srcImg, hsv_img, CV_BGR2HSV); //BGRת��HSV��ɫ�ռ�
	imshow("hsv_img", hsv_img);
	Scalar hsv_min(h_min,s_min, v_min);
	Scalar hsv_max(h_max, s_max, v_max);

	////Mat hsv_blue = Mat::zeros(srcImg.size(), CV_8U);
	Mat hsv_red = Mat::zeros(srcImg.size(), CV_8U);
	////Mat hsv_green = Mat::zeros(srcImg.size(),CV_8U);


	////inRange(hsv_img, hsv_min, hsv_max, hsv_blue);//ɸѡ��������HSV��ɫ�ռ���е�
	inRange(hsv_img, hsv_min, hsv_max, hsv_red);
	////inRange(hsv_img, hsv_min, hsv_max, hsv_green);


	////medianBlur(hsv_blue, hsv_blue, 5);
	medianBlur(hsv_red, hsv_red, 7);
	////medianBlur(hsv_green, hsv_green, 5);


	////imshow("hsv_blue", hsv_blue);
	imshow("hsv_red", hsv_red);
    //imshow("hsv_green", hsv_green);



	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(9, 9));
	erode(hsv_red, hsv_red, element);
	imshow("erode", hsv_red);
	dilate(hsv_red,hsv_red, element2);
	imshow("dilate", hsv_red);
   

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy; 

	////findContours(hsv_blue, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	findContours(hsv_red, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	////findContours(hsv_green, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//

	vector<Rect> boundRect(contours.size());
	int width_max =20;
	int height_max = 20;
	//int t = 0;
	for(int i=0; i<contours.size(); i++)
	{
	  boundRect[i] = boundingRect(Mat(contours[i]));
	 // int width_max = boundRect[0].width;
	  //int height_max = boundRect[0].height; 
	  if(boundRect[i].width>=width_max && boundRect[i].height>=height_max)  //ɸѡ��Ŀ������������һ����ʾ����
	  { 
		/*width_max =  boundRect[i].width;
		height_max = boundRect[i].height;*/
		//t = i;
		rectangle(dstImg, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 255), 2, 8); //���α�ǣ�boundRect[i].tl()Ϊ���Ͻ����꣬boundRect[i].br()Ϊ���½�����	
		Point org =  boundRect[i].tl();//����д��λ�ã�������㿪ʼ
		cout<<"("<<(boundRect[i].tl().x + boundRect[i].br().x)/2<<" , "<<(boundRect[i].tl().y + boundRect[i].br().y)/2<<")"<<endl;


		//putText( dstImg, "blue", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);
		putText( dstImg, "red", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);
		//putText( dstImg, "green", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);
	   }
	}

	 //rectangle(dstImg, boundRect[t].tl(), boundRect[t].br(), Scalar(0, 255, 255), 2, 8); //���α�ǣ�boundRect[i].tl()Ϊ���Ͻ����꣬boundRect[i].br()Ϊ���½�����	
	 //Point org =  boundRect[t].tl();//����д��λ�ã�������㿪ʼ
	 //cout<<"("<<(boundRect[t].tl().x + boundRect[t].br().x)/2<<" , "<<(boundRect[t].tl().y + boundRect[t].br().y)/2<<")"<<endl;
	 //putText( dstImg, "red", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);

	imshow("result", dstImg);
	//waitKey(500);
	if(waitKey(20)>0)
		break;
	}
	//waitKey(0);
}