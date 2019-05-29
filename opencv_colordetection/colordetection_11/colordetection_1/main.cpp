#include "opencv2/opencv.hpp"
#include <iostream>
#include <chrono>

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "tchar.h"

#include <ctime>

using namespace cv;
using namespace std;


/////red hsv min value
//int h_min = 15;
//int s_min = 149;
//int v_min =38;
/////red hsv max value
//int h_max =71;
// int s_max = 255;
//int v_max = 134;

///////red hsv min values室内
int h_min = 0;
int s_min = 145;
int v_min =162; //253
 ///red hsv max value
int h_max =10;
int s_max = 255;
int v_max = 255;

/////////red hsv min value室外
//int h_min = 10;
//int s_min = 145;
//int v_min =162; //253
// ///red hsv max value
//int h_max =180;
//int s_max = 255;
//int v_max = 255;



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
	
	//waitKey(60000);
	VideoCapture cap;
	cap.open(0);  //打开摄像头

	if(!cap.isOpened())  //判断摄像头是否打开 
		return; 

	Mat srcImg;
	while(1)
	{
	  clock_t time_stt00 = clock();
	  clock_t time_stt0 = clock();
	  cap>>srcImg;
	  if(srcImg.empty())
		 break;
	    
      //imshow("video", srcImg);

	///识别图片中颜色物体
	//Mat srcImg = imread("G:\\Program Files\\VS\\vs_opencv_workspace\\video\\colordetection_1\\colordetection_1\\rgb.jpg");
	//Mat srcImg = imread("G:\\Program Files\\VS\\vs_opencv_workspace\\video\\colordetection_1\\colordetection_1\\duck2.jpg");
	//Mat srcImg = imread("G:\\Program Files\\VS\\vs_opencv_workspace\\video\\colordetection_1\\colordetection_1\\color1.jpg");
	


	//imshow("src", srcImg);
	Mat dstImg = srcImg.clone();
	Mat hsv_img;  //存储HSV图像  
	//cvtColor(srcImg, hsv_img, CV_Lab2BGR);
	//cout <<"time use is      end:————0  is  " << 1000* (clock() - time_stt0)/(double)CLOCKS_PER_SEC << "ms"
    //<< endl;
	clock_t time_stt1 = clock();
	cvtColor(srcImg, hsv_img, CV_BGR2HSV); //BGR转到HSV颜色空间
	cout <<"time use is      end:————1  is  " << 1000* (clock() - time_stt1)/(double)CLOCKS_PER_SEC << "ms" 
    << endl;
	//imshow("hsv_img", hsv_img);
	Scalar hsv_min(h_min,s_min, v_min);
	Scalar hsv_max(h_max, s_max, v_max);

	////Mat hsv_blue = Mat::zeros(srcImg.size(), CV_8U);
	Mat hsv_red = Mat::zeros(srcImg.size(), CV_8U);
	////Mat hsv_green = Mat::zeros(srcImg.size(),CV_8U);


	////inRange(hsv_img, hsv_min, hsv_max, hsv_blue);//筛选轮廓是在HSV颜色空间进行的
	inRange(hsv_img, hsv_min, hsv_max, hsv_red);
	////inRange(hsv_img, hsv_min, hsv_max, hsv_green);

	//clock_t time_stt2 = clock();
	////medianBlur(hsv_blue, hsv_blue, 5);
	//medianBlur(hsv_red, hsv_red, 7);
	//cout <<"time use is      end:————2  is  " << 1000* (clock() - time_stt2)/(double)CLOCKS_PER_SEC << "ms"
    //<< endl;
	////medianBlur(hsv_green, hsv_green, 5);


	////imshow("hsv_blue", hsv_blue);
	//imshow("hsv_red", hsv_red);
    //imshow("hsv_green", hsv_green);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	//Mat element2 = getStructuringElement(MORPH_RECT, Size(9, 9));
	//clock_t time_stt3 = clock();
	//erode(hsv_red, hsv_red, element);
	//cout <<"time use is      end:————3  is  " << 1000* (clock() - time_stt3)/(double)CLOCKS_PER_SEC << "ms"
 //   << endl;
	////imshow("erode", hsv_red);
	//clock_t time_stt4 = clock();
	//dilate(hsv_red,hsv_red, element2);
	//cout <<"time use is      end:————4  is  " << 1000* (clock() - time_stt4)/(double)CLOCKS_PER_SEC << "ms"
 //   << endl;
	////imshow("dilate", hsv_red);


   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy; 

	////findContours(hsv_blue, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	findContours(hsv_red, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	////findContours(hsv_green, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//

	vector<Rect> boundRect(contours.size());
	clock_t time_stt5 = clock();
	int t1 = 0;
	int t2 = 0;
	for(int i=0; i<contours.size(); i++)
	{
	  boundRect[i] = boundingRect(Mat(contours[i]));
	   int width_max =20;
	   int height_max = 20;
	 //int width_max = boundRect[0].width;
	 //int height_max = boundRect[0].height; 
	  if(boundRect[i].width>=width_max && boundRect[i].height>=height_max)  //筛选出目标轮廓中最大的一个显示出来
	  { 
		 
		width_max =  boundRect[i].width;
		height_max = boundRect[i].height;
		//t = i;
		rectangle(dstImg, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 255), 2, 8); //矩形标记，boundRect[i].tl()为左上角坐标，boundRect[i].br()为右下角坐标	
		//Point org =  boundRect[i].tl();//文字写的位置，从这个点开始
		//cout<<"("<<(boundRect[i].tl().x + boundRect[i].br().x)/2<<" , "<<(boundRect[i].tl().y + boundRect[i].br().y)/2<<")"<<endl;
		t1=(boundRect[i].tl().x + boundRect[i].br().x)/2;
		t2=(boundRect[i].tl().y + boundRect[i].br().y)/2;

		//putText( dstImg, "blue", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);
		//putText( dstImg, "red", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);
		//putText( dstImg, "green", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);
	   }
	}

	// rectangle(dstImg, boundRect[t].tl(), boundRect[t].br(), Scalar(0, 255, 255), 2, 8); //矩形标记，boundRect[i].tl()为左上角坐标，boundRect[i].br()为右下角坐标	
	// Point org =  boundRect[t].tl();//文字写的位置，从这个点开始
	// cout<<"("<<(boundRect[t].tl().x + boundRect[t].br().x)/2<<" , "<<(boundRect[t].tl().y + boundRect[t].br().y)/2<<")"<<endl;
	// putText( dstImg, "red", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);

	imshow("result", dstImg);
	//waitKey(500);
	/*if(waitKey(20)>0)
		break;*/          
	cout <<"time use is      end:————5  is  " << 1000* (clock() - time_stt5)/(double)CLOCKS_PER_SEC << "ms"
    << endl;
	
	//waitKey(0);
	/*****************************打开串口*************************************/
   clock_t time_stt6 = clock();
   HANDLE hCom;//全局变量，串口句柄
   hCom = CreateFile(_T("COM7"),//COM1口本机6，小电脑4
    GENERIC_READ | GENERIC_WRITE,//允许读和写
    0,//独占方式
    NULL,
    OPEN_EXISTING,//打开而不是创建
    0,//同步方式
    //FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERAPPLE,//重叠方式
    NULL);////////////////////////////////////////////////////////////////////////////////////////////////////////////////耗时
   cout <<"time use is      end:————6  is  " << 1000* (clock() - time_stt6)/(double)CLOCKS_PER_SEC << "ms"
    << endl;

   if (hCom == (HANDLE)-1)
   {
    printf("打开COM失败！");
    return ;
   }
  // /*********************************配置串口*********************************/
   SetupComm(hCom, 20480, 20480);//输入缓冲区和输出缓冲区的大小都是20480
   COMMTIMEOUTS TimeOuts;
   
   //设定读超时
   TimeOuts.ReadIntervalTimeout = 1000;
   TimeOuts.ReadTotalTimeoutMultiplier = 500;
   TimeOuts.ReadTotalTimeoutConstant = 5000;
   //设定写超时
   TimeOuts.WriteTotalTimeoutMultiplier = 500;
   TimeOuts.WriteTotalTimeoutConstant = 2000;
   SetCommTimeouts(hCom, &TimeOuts);//设置超时
   DCB dcb;
   GetCommState(hCom, &dcb);
   dcb.BaudRate = 115200;//波特率为115200

   //clock_t time_stt7 = clock();

   dcb.ByteSize = 8;//每个字节有8位
   dcb.Parity = NOPARITY;//无奇偶校验位

   //clock_t time_stt7 = clock();

   dcb.StopBits = ONESTOPBIT;//1个停止位
   dcb.fParity = FALSE;
   dcb.fNull = FALSE;

   
   clock_t time_stt7 = clock();

   SetCommState(hCom, &dcb);/////////////////////////////////////////////////////////////////////////////////////////耗时

   cout <<"time use is      end:————7  is  " << 1000* (clock() - time_stt7)/(double)CLOCKS_PER_SEC << "ms"
    << endl;//70ms


   PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//在读写串口之前清空缓冲区
   /******************************同步写串口*************************************/
    //cout <<"time use is      end:————7  is  " << 1000* (clock() - time_stt7)/(double)CLOCKS_PER_SEC << "ms"
    //<< endl;//70ms
  /* cout <<"time use is      end:————6  is  " << 1000* (clock() - time_stt6)/(double)CLOCKS_PER_SEC << "ms"
    << endl;*/////60ms
  
   unsigned char first = 0x3A;
   unsigned char second = 0xA3;
   unsigned char MessageLen = 10;//数据头+指令ID+数据长度+有效数据+求和校验
   unsigned char ID=0x19;
   unsigned char x1 =( t1>>8)&0x00FF;//像素x高八位
   unsigned char x2 = t1&0x00FF;//像素x低八位
   unsigned char y1 = ( t2>>8)&0x00FF;//像素Y高八位
   unsigned char y2 = t2&0x00FF;//像素Y低八位

   /*cout <<"time use is      end:————6  is  " << 1000* (clock() - time_stt6)/(double)CLOCKS_PER_SEC << "ms"
    << endl;*/

   unsigned char result[100] = { 0 };//写入串口缓存区的数组
   int len = sizeof(short int);
   int len1 = sizeof(float);
   int len2 = sizeof(char);
   memcpy(result, &first, len2);
   memcpy(result + len2, &second, len2);
   memcpy(result + 2 * len2, &MessageLen, len2);
   memcpy(result + 3 * len2, &ID, len2);
   result[4]= x1;
   result[5]= x2;
   result[6]= y1;
   result[7]= y2;

   
   //计算出求和校验码
   
       short int sBcc = 0;
        for(int i=2; i<8; i++)
        {
            if(result[i] < 0)
            {
                result[i] = (char)(result[i] + 256);
                sBcc += (result[i] & 0x00FF);
            }
            else
                sBcc += (result[i] & 0x00FF);
        }

        result[8] = (char)((sBcc >> 8) & 0x00FF);
        result[9] = (char)(sBcc & 0x00FF);


   /*cout <<"time use is      end:————6  is  " << 1000* (clock() - time_stt6)/(double)CLOCKS_PER_SEC << "ms"
    << endl;*/
  
   DWORD dwwrittenLen = 10;
   COMSTAT ComStat;
   DWORD dwErrorFlags;
   BOOL bWriteStat;
   ClearCommError(hCom,&dwErrorFlags,&ComStat);
    if (!WriteFile(hCom, result, 10,&dwwrittenLen, NULL))
    {
     printf("发送数据失败！\n");
    }
	cout<<"("<<t1<<" , "<<t2 <<")"<<endl;
    printf("Main Baseline往串口发送数据成功！");
	
	/*cout <<"time use is      end:————6  is  " << 1000* (clock() - time_stt6)/(double)CLOCKS_PER_SEC << "ms"
    << endl;*/

	cout <<"time use is      end:————8  is  " << 1000* (clock() - time_stt00)/(double)CLOCKS_PER_SEC << "ms"
    << endl;
   // waitKey(10);
    
   /***********关闭串口***********/
   CloseHandle(hCom);
  //// waitKey(0);
   if(waitKey(20)>0)
		break;
 }


}