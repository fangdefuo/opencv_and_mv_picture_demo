#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>

#include <ctime>

using namespace cv;
using namespace std;

void main()
{
//    //������ȡͼƬ������
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


///��Ƶ�ֽ��ͼƬ

	Mat frame;
	char outfile[100];

	VideoCapture cap;
	cap.open(0);
	if(!cap.isOpened())  //��ʧ��
		return;
	int totalFrame = 200;

	//clock_t time_stt = clock();
	//int totalFrame = cap.get(CV_CAP_PROP_FRAME_COUNT); //��ȡ��Ƶ��֡��

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

	///ͼƬ�ϳ���Ƶ

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

	//��������
	

 //   //������ͷ
 //   VideoCapture captrue(0);
 //   //��Ƶд�����
 //   VideoWriter write;
 //   //д����Ƶ�ļ���
 //   string outFlie = "E://fcq.avi";
 //   //���֡�Ŀ��
 //   int w = static_cast<int>(captrue.get(CV_CAP_PROP_FRAME_WIDTH));
 //   int h = static_cast<int>(captrue.get(CV_CAP_PROP_FRAME_HEIGHT));
 //   Size S(w, h);
 //   //���֡��
 //   double r = captrue.get(CV_CAP_PROP_FPS);
 //   //����Ƶ�ļ���׼��д��
 //   write.open(outFlie, -1, r, S, true);
	////��ʧ��
 //   if (!captrue.isOpened())
 //   {
 //      return;
 //   }
 //   bool stop = false;
 //   Mat frame;
 //   //ѭ��
 //   while (!stop)
 //   {
 //       //��ȡ֡
 //       if (!captrue.read(frame))
 //           break;
 //       imshow("Video", frame);
 //       //д���ļ�
 //       write.write(frame);
 //       if (waitKey(10) > 0)
 //       {
 //           stop = true;
 //       }
 //   }
 //   //�ͷŶ���
 //   captrue.release();
 //   write.release();
	//cvDestroyWindow("Video"); 
	//
 

}