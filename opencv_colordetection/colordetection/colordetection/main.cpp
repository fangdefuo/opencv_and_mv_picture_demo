#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;


void main()
{
	VideoCapture cap;
	cap.open(0); //������ͷ
	if(!cap.isOpened())
		return;
	Mat frame;
	while(1)
	{
	  cap>>frame;
	  if(!frame.empty())
	  {
	    int b = 0; 
		int g = 0;
		int r = 0;

		int bx = 0;
		int by = 0;

		int gx = 0;
		int gy = 0;

		int rx = 0;
		int ry = 0;
		   
		for(int i = 0; i <= frame.rows; i++)
		{
		  for(int j= 0; j <= frame.cols; j++)
		  {
		     if(frame.at<Vec3b>(i,j)[0] >= 230 && frame.at<Vec3b>(i,j)[1] <= 50 && frame.at<Vec3b>(i,j)[2] <= 50)  //blue���
			 {
			   b = b + 1;
			   bx = bx + j;
			   by = by + i;
			 }
		      if(frame.at<Vec3b>(i,j)[0] <= 50 && frame.at<Vec3b>(i,j)[1] >= 230 && frame.at<Vec3b>(i,j)[2] <= 50)  //green���
			 {
			   g = g + 1;
			   gx = gx + j;
			   gy = gy + i; 
			 }
			  if(frame.at<Vec3b>(i,j)[0] <= 50 && frame.at<Vec3b>(i,j)[1] <= 50 && frame.at<Vec3b>(i,j)[2] >= 230)  //blue���
			 {
			   r = r + 1;
			   rx = rx + j;
			   ry = ry + i;
			 }
		  }
		}
		if(b > g && b > r)
		{
		  bx = bx/b;
		  by = by/b;
		  cout<<"��ɫ"<<"("<<bx<<" , "<<by<<")"<<endl;
		}
		if(g > b && g > r)
		{
		   gx = gx/g;
		   gy = gy/g;
		   cout<<"��ɫ"<<"("<<gx<<" , "<<gy<<")"<<endl;
		}
		if(r > b && r > g)
		{
		   rx = rx/r;
		   ry = ry/r;
		   cout<<"��ɫ"<<"("<<rx<<" , "<<ry<<")"<<endl;
		}
	  }
	  else
	    break;
	  imshow("video", frame);
	  waitKey(200);
	}

}
/*Mat_<Vec3b>::iterator colorit;  //���õ������ķ���
		for(colorit = frame.begin<Vec3b>(); colorit != frame.end<Vec3b>(); ++colorit)
		{
	      if((*colorit)[0] >= 230 && (*colorit)[1] <= 10 && (*colorit)[2] <= 10)  //blueʶ��
		  {
		    
		  
		  }
		  if((*colorit)[0] <= 10 && (*colorit)[1] >= 230 && (*colorit)[2] <= 10)  //greenʶ��
		  {
		    
		  
		  }
		  if((*colorit)[0] <= 10 && (*colorit)[1] <= 10 && (*colorit)[2] >= 10)   //redʶ��
		  {
		    
		  
		  }
	    }*/