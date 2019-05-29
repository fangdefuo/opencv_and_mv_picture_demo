#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>

#include <ctime>

using namespace cv;
using namespace std;

void main()
{
//    //批量读取图片（有序）
//    char filename[50];
//    char winName[50];
//    Mat srcImg;
//    for (int i = 1; i < 100; i++)
//    {
//        sprintf(filename,"%d.bmp",i);
//        sprintf(winName,"NO--%d",i);
//        srcImg=imread(filename);
//        if (srcImg.empty())
//            break;
//        imshow(winName,srcImg);
//    }
//    waitKey(0);
//    destroyAllWindows();
//}


///视频分解成图片

	Mat frame;
	char outfile[100];

	VideoCapture cap;
	cap.open(0);
	if(!cap.isOpened())  //打开失败
		return;
	int totalFrame = 200;

	//clock_t time_stt = clock();
	//int totalFrame = cap.get(CV_CAP_PROP_FRAME_COUNT); //获取视频总帧数

	for(int i = 1; i<=totalFrame; i++)
	{
		cap>>frame;
		if(frame.empty())
			break;
		sprintf(outfile, "G:\\test\\%d.png", i);
		imwrite(outfile, frame);
		imshow("video", frame);  
		//waitKey(15);
	}
	//cap.release();
	//cout <<"time use is  " << 1000* (clock() - time_stt)/(double)CLOCKS_PER_SEC << "ms"
   // << endl;
	waitKey (5000);

	destroyAllWindows(); 

	///图片合成视频

	//VideoWriter writer("E:\\out.avi", CV_FOURCC('X', 'V', 'I', 'D'), 20, Size(568, 320), true);
	//VideoCapture cap;
	//char filename[50];
	//Mat frame;
	//for(int i = 1; i<644; i++)
	//{
	//	sprintf(filename, "E:\\pic\\%d.bmp", i);
	//	//frame = imread(filename);
	//	cap.open(filename);
	//	if(!cap.isOpened())
	//		break;
	//	cap>>frame;
	//	if(frame.empty())
	//		break;
	//	writer<<frame;
	//}
	//
	//cout<<"write end!"<<endl;
	//destroyAllWindows();

	//保存视屏
	

 //   //打开摄像头
 //   VideoCapture captrue(0);
 //   //视频写入对象
 //   VideoWriter write;
 //   //写入视频文件名
 //   string outFlie = "E://fcq.avi";
 //   //获得帧的宽高
 //   int w = static_cast<int>(captrue.get(CV_CAP_PROP_FRAME_WIDTH));
 //   int h = static_cast<int>(captrue.get(CV_CAP_PROP_FRAME_HEIGHT));
 //   Size S(w, h);
 //   //获得帧率
 //   double r = captrue.get(CV_CAP_PROP_FPS);
 //   //打开视频文件，准备写入
 //   write.open(outFlie, -1, r, S, true);
	////打开失败
 //   if (!captrue.isOpened())
 //   {
 //      return;
 //   }
 //   bool stop = false;
 //   Mat frame;
 //   //循环
 //   while (!stop)
 //   {
 //       //读取帧
 //       if (!captrue.read(frame))
 //           break;
 //       imshow("Video", frame);
 //       //写入文件
 //       write.write(frame);
 //       if (waitKey(10) > 0)
 //       {
 //           stop = true;
 //       }
 //   }
 //   //释放对象
 //   captrue.release();
 //   write.release();
	//cvDestroyWindow("Video"); 
	//
 

}