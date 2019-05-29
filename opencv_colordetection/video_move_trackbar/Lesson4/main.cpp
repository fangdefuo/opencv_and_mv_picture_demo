#include "opencv2/opencv.hpp"
#include <iostream>
//#include "opencv2/core/mat.hpp"
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
	VideoCapture cap;
	cap.open(0); //����Ƶ
//	
//	Size size0 = Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
//	//VideoWriter writer("E:\\out.avi", CV_FOURCC('X', 'V', 'I', 'D'), 20, size0, true);
//	//VideoWriter writer("E:\\out.avi", -1,20, size0, false);
//
//	
//	//cap.open(0); //����Ƶ
//	//VideoCapture cap("E:\\2.avi");
//	//cap.open("http://www.laganiere.name/bike.avi");
	if(!cap.isOpened())
		return;
//
//	int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);  //֡���
//	int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //֡�߶�
//	int frameRate = cap.get(CV_CAP_PROP_FPS);  //֡�� x frames/s
//	int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT); //��֡��
//
//	cout<<"��Ƶ���="<<width<<endl;
//	cout<<"��Ƶ�߶�="<<height<<endl;
//	cout<<"��Ƶ��֡��="<<totalFrames<<endl;
//	cout<<"֡��="<<frameRate<<endl;    
//
//
//
	//Mat srcImg ;

	while(1)
	{
	  cap>>srcImg ;
	  if(srcImg .empty())
		  break;
	   /*if( srcImg.type != CV_8UC1 && srcImg.type != CV_8UC3 )
	  {
	    cout<<"�������ɫͼ��Ҷ�ͼ"<<endl;

	  }*/
	  //Canny(frame, frame, 30, 100);
	  imshow("video", srcImg );
	 // cvtColor(srcImg, hsv_img, CV_Lab2BGR);  //ת����HSV��ɫ�ռ�
	  cvtColor(srcImg, hsv_img, CV_BGR2HSV);
		
	  //writer<<frame;
	  //writer.write(frame);
	  //cap.read(frame);
	  imshow("video", srcImg );
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
 
	  //waitKey(0);
	  if(waitKey(20)>0)
		 break;
	}
	//cout<<"write end!";
	/*cap.release();
	destroyAllWindows();*/
}




//#include "opencv2/opencv.hpp"
//#include <iostream>
//using namespace cv;
//using namespace std;


//void main()
//{ 
////	VideoCapture cap;
////	cap.open(0); //������ͷ
//	
//	//Size size0 = Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
//	//VideoWriter writer("E:\\out.avi", CV_FOURCC('X', 'V', 'I', 'D'), 20, size0, true);
//	//VideoWriter writer("E:\\out.avi", -1,20, size0, false);
//
//	/*if(!cap.isOpened())
//		return;*/
//
//	//int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);  //֡���
//	//int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //֡�߶�
//	//int frameRate = cap.get(CV_CAP_PROP_FPS);  //֡�� x frames/s
//	//int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT); //��֡��
//
//	//cout<<"��Ƶ���="<<width<<endl;
//	//cout<<"��Ƶ�߶�="<<height<<endl;
//	//cout<<"��Ƶ��֡��="<<totalFrames<<endl;
//	//cout<<"֡��="<<frameRate<<endl;
//
//	Mat frame = imread("G:\\Program Files\\VS\opencv_source\\Դ��(1--35)\\Lesson4\\Debug\\1.jpg");
//	/*int rows;
//	int cols;*/
//
//	//while(1)
//	//{
//		//cap>>frame;
//		/*Mat_<Vec3b>::iterator colorit;  //���õ������ķ���
//		for(colorit = frame.begin<Vec3b>(); colorit != frame.end<Vec3b>(); ++colorit)
//		{
//	      if((*colorit)[0] >= 230 && (*colorit)[1] <= 10 && (*colorit)[2] <= 10)  //blueʶ��
//		  {
//		    
//		  
//		  }
//		  if((*colorit)[0] <= 10 && (*colorit)[1] >= 230 && (*colorit)[2] <= 10)  //greenʶ��
//		  {
//		    
//		  
//		  }
//		  if((*colorit)[0] <= 10 && (*colorit)[1] <= 10 && (*colorit)[2] >= 10)   //redʶ��
//		  {
//		    
//		  
//		  }
//	    }*/
//	  long int b = 0; 
//	  long int g = 0;
//	  long int r = 0;
//
//	  long int bx = 0;
//	  long int by = 0;
//
//	  long int gx = 0;
//	  long int gy = 0;
//
//	  long int rx = 0;
//	  long int ry = 0;
//
//		for(int i = 0; i <= frame.rows; i++)
//		{
//		  for(int j= 0; j <= frame.cols; j++)
//		  {
//		     if(frame.at<Vec3b>(i,j)[0] >= 230 && frame.at<Vec3b>(i,j)[1] <= 50 && frame.at<Vec3b>(i,j)[2] <= 50)  //blue���
//			 {
//			   b = b + 1;
//			   bx = bx + j;
//			   by = by + i;
//			 }
//		      if(frame.at<Vec3b>(i,j)[0] <= 50 && frame.at<Vec3b>(i,j)[1] >= 230 && frame.at<Vec3b>(i,j)[2] <= 50)  //green���
//			 {
//			   g = g + 1;
//			   gx = gx + j;
//			   gy = gy + i; 
//			 }
//			  if(frame.at<Vec3b>(i,j)[0] <= 50 && frame.at<Vec3b>(i,j)[1] <= 50 && frame.at<Vec3b>(i,j)[2] >= 230)  //blue���
//			 {
//			   r = r + 1;
//			   rx = rx + j;
//			   ry = ry + i;
//			 }
//		  }
//		}
//		if(b > g && b > r)
//		{
//		  bx = bx/b;
//		  by = by/b;
//		  cout<<"��ɫ"<<"("<<bx<<" , "<<by<<")"<<endl;
//		}
//		else if(g > b && g > r)
//		{
//		   gx = gx/g;
//		   gy = gy/g;
//		   cout<<"��ɫ"<<"("<<gx<<" , "<<gy<<")"<<endl;
//		}
//		else if(r > b && r > g)
//		{
//		   rx = rx/r;
//		   ry = ry/r;
//		   cout<<"��ɫ"<<"("<<rx<<" , "<<ry<<")"<<endl;
//		}
//		else
//		{
//		
//		  cout<<"error"<<endl;
//		
//		}
		//cvtColor(frame, frame, CV_BGR2HSV);
		//if(frame.empty())
			//break;
		//writer<<frame;
		//writer.write(frame);
		//cap.read(frame);
		//imshow("video", frame);
		//if(waitKey(0));
			//break;
	//}
	//cout<<"write end!";
	//cap.release();
//	//destroyAllWindows();
//		waitKey(0);
//}