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

///////red hsv min values����
int h_min = 0;
int s_min = 145;
int v_min =162; //253
 ///red hsv max value
int h_max =10;
int s_max = 255;
int v_max = 255;

/////////red hsv min value����
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
	cap.open(0);  //������ͷ

	if(!cap.isOpened())  //�ж�����ͷ�Ƿ�� 
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

	///ʶ��ͼƬ����ɫ����
	//Mat srcImg = imread("G:\\Program Files\\VS\\vs_opencv_workspace\\video\\colordetection_1\\colordetection_1\\rgb.jpg");
	//Mat srcImg = imread("G:\\Program Files\\VS\\vs_opencv_workspace\\video\\colordetection_1\\colordetection_1\\duck2.jpg");
	//Mat srcImg = imread("G:\\Program Files\\VS\\vs_opencv_workspace\\video\\colordetection_1\\colordetection_1\\color1.jpg");
	


	//imshow("src", srcImg);
	Mat dstImg = srcImg.clone();
	Mat hsv_img;  //�洢HSVͼ��  
	//cvtColor(srcImg, hsv_img, CV_Lab2BGR);
	//cout <<"time use is      end:��������0  is  " << 1000* (clock() - time_stt0)/(double)CLOCKS_PER_SEC << "ms"
    //<< endl;
	clock_t time_stt1 = clock();
	cvtColor(srcImg, hsv_img, CV_BGR2HSV); //BGRת��HSV��ɫ�ռ�
	cout <<"time use is      end:��������1  is  " << 1000* (clock() - time_stt1)/(double)CLOCKS_PER_SEC << "ms" 
    << endl;
	//imshow("hsv_img", hsv_img);
	Scalar hsv_min(h_min,s_min, v_min);
	Scalar hsv_max(h_max, s_max, v_max);

	////Mat hsv_blue = Mat::zeros(srcImg.size(), CV_8U);
	Mat hsv_red = Mat::zeros(srcImg.size(), CV_8U);
	////Mat hsv_green = Mat::zeros(srcImg.size(),CV_8U);


	////inRange(hsv_img, hsv_min, hsv_max, hsv_blue);//ɸѡ��������HSV��ɫ�ռ���е�
	inRange(hsv_img, hsv_min, hsv_max, hsv_red);
	////inRange(hsv_img, hsv_min, hsv_max, hsv_green);

	//clock_t time_stt2 = clock();
	////medianBlur(hsv_blue, hsv_blue, 5);
	//medianBlur(hsv_red, hsv_red, 7);
	//cout <<"time use is      end:��������2  is  " << 1000* (clock() - time_stt2)/(double)CLOCKS_PER_SEC << "ms"
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
	//cout <<"time use is      end:��������3  is  " << 1000* (clock() - time_stt3)/(double)CLOCKS_PER_SEC << "ms"
 //   << endl;
	////imshow("erode", hsv_red);
	//clock_t time_stt4 = clock();
	//dilate(hsv_red,hsv_red, element2);
	//cout <<"time use is      end:��������4  is  " << 1000* (clock() - time_stt4)/(double)CLOCKS_PER_SEC << "ms"
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
	  if(boundRect[i].width>=width_max && boundRect[i].height>=height_max)  //ɸѡ��Ŀ������������һ����ʾ����
	  { 
		 
		width_max =  boundRect[i].width;
		height_max = boundRect[i].height;
		//t = i;
		rectangle(dstImg, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 255), 2, 8); //���α�ǣ�boundRect[i].tl()Ϊ���Ͻ����꣬boundRect[i].br()Ϊ���½�����	
		//Point org =  boundRect[i].tl();//����д��λ�ã�������㿪ʼ
		//cout<<"("<<(boundRect[i].tl().x + boundRect[i].br().x)/2<<" , "<<(boundRect[i].tl().y + boundRect[i].br().y)/2<<")"<<endl;
		t1=(boundRect[i].tl().x + boundRect[i].br().x)/2;
		t2=(boundRect[i].tl().y + boundRect[i].br().y)/2;

		//putText( dstImg, "blue", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);
		//putText( dstImg, "red", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);
		//putText( dstImg, "green", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);
	   }
	}

	// rectangle(dstImg, boundRect[t].tl(), boundRect[t].br(), Scalar(0, 255, 255), 2, 8); //���α�ǣ�boundRect[i].tl()Ϊ���Ͻ����꣬boundRect[i].br()Ϊ���½�����	
	// Point org =  boundRect[t].tl();//����д��λ�ã�������㿪ʼ
	// cout<<"("<<(boundRect[t].tl().x + boundRect[t].br().x)/2<<" , "<<(boundRect[t].tl().y + boundRect[t].br().y)/2<<")"<<endl;
	// putText( dstImg, "red", org, CV_FONT_HERSHEY_SIMPLEX, 1.2f, CV_RGB(0,255,0),2);

	imshow("result", dstImg);
	//waitKey(500);
	/*if(waitKey(20)>0)
		break;*/          
	cout <<"time use is      end:��������5  is  " << 1000* (clock() - time_stt5)/(double)CLOCKS_PER_SEC << "ms"
    << endl;
	
	//waitKey(0);
	/*****************************�򿪴���*************************************/
   clock_t time_stt6 = clock();
   HANDLE hCom;//ȫ�ֱ��������ھ��
   hCom = CreateFile(_T("COM7"),//COM1�ڱ���6��С����4
    GENERIC_READ | GENERIC_WRITE,//�������д
    0,//��ռ��ʽ
    NULL,
    OPEN_EXISTING,//�򿪶����Ǵ���
    0,//ͬ����ʽ
    //FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERAPPLE,//�ص���ʽ
    NULL);////////////////////////////////////////////////////////////////////////////////////////////////////////////////��ʱ
   cout <<"time use is      end:��������6  is  " << 1000* (clock() - time_stt6)/(double)CLOCKS_PER_SEC << "ms"
    << endl;

   if (hCom == (HANDLE)-1)
   {
    printf("��COMʧ�ܣ�");
    return ;
   }
  // /*********************************���ô���*********************************/
   SetupComm(hCom, 20480, 20480);//���뻺����������������Ĵ�С����20480
   COMMTIMEOUTS TimeOuts;
   
   //�趨����ʱ
   TimeOuts.ReadIntervalTimeout = 1000;
   TimeOuts.ReadTotalTimeoutMultiplier = 500;
   TimeOuts.ReadTotalTimeoutConstant = 5000;
   //�趨д��ʱ
   TimeOuts.WriteTotalTimeoutMultiplier = 500;
   TimeOuts.WriteTotalTimeoutConstant = 2000;
   SetCommTimeouts(hCom, &TimeOuts);//���ó�ʱ
   DCB dcb;
   GetCommState(hCom, &dcb);
   dcb.BaudRate = 115200;//������Ϊ115200

   //clock_t time_stt7 = clock();

   dcb.ByteSize = 8;//ÿ���ֽ���8λ
   dcb.Parity = NOPARITY;//����żУ��λ

   //clock_t time_stt7 = clock();

   dcb.StopBits = ONESTOPBIT;//1��ֹͣλ
   dcb.fParity = FALSE;
   dcb.fNull = FALSE;

   
   clock_t time_stt7 = clock();

   SetCommState(hCom, &dcb);/////////////////////////////////////////////////////////////////////////////////////////��ʱ

   cout <<"time use is      end:��������7  is  " << 1000* (clock() - time_stt7)/(double)CLOCKS_PER_SEC << "ms"
    << endl;//70ms


   PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//�ڶ�д����֮ǰ��ջ�����
   /******************************ͬ��д����*************************************/
    //cout <<"time use is      end:��������7  is  " << 1000* (clock() - time_stt7)/(double)CLOCKS_PER_SEC << "ms"
    //<< endl;//70ms
  /* cout <<"time use is      end:��������6  is  " << 1000* (clock() - time_stt6)/(double)CLOCKS_PER_SEC << "ms"
    << endl;*/////60ms
  
   unsigned char first = 0x3A;
   unsigned char second = 0xA3;
   unsigned char MessageLen = 10;//����ͷ+ָ��ID+���ݳ���+��Ч����+���У��
   unsigned char ID=0x19;
   unsigned char x1 =( t1>>8)&0x00FF;//����x�߰�λ
   unsigned char x2 = t1&0x00FF;//����x�Ͱ�λ
   unsigned char y1 = ( t2>>8)&0x00FF;//����Y�߰�λ
   unsigned char y2 = t2&0x00FF;//����Y�Ͱ�λ

   /*cout <<"time use is      end:��������6  is  " << 1000* (clock() - time_stt6)/(double)CLOCKS_PER_SEC << "ms"
    << endl;*/

   unsigned char result[100] = { 0 };//д�봮�ڻ�����������
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

   
   //��������У����
   
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


   /*cout <<"time use is      end:��������6  is  " << 1000* (clock() - time_stt6)/(double)CLOCKS_PER_SEC << "ms"
    << endl;*/
  
   DWORD dwwrittenLen = 10;
   COMSTAT ComStat;
   DWORD dwErrorFlags;
   BOOL bWriteStat;
   ClearCommError(hCom,&dwErrorFlags,&ComStat);
    if (!WriteFile(hCom, result, 10,&dwwrittenLen, NULL))
    {
     printf("��������ʧ�ܣ�\n");
    }
	cout<<"("<<t1<<" , "<<t2 <<")"<<endl;
    printf("Main Baseline�����ڷ������ݳɹ���");
	
	/*cout <<"time use is      end:��������6  is  " << 1000* (clock() - time_stt6)/(double)CLOCKS_PER_SEC << "ms"
    << endl;*/

	cout <<"time use is      end:��������8  is  " << 1000* (clock() - time_stt00)/(double)CLOCKS_PER_SEC << "ms"
    << endl;
   // waitKey(10);
    
   /***********�رմ���***********/
   CloseHandle(hCom);
  //// waitKey(0);
   if(waitKey(20)>0)
		break;
 }


}