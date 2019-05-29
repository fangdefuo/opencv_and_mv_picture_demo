#include <iostream>  
#include <fstream>  
#include <io.h>  
#include "opencv2/opencv.hpp"
using namespace cv;  
using namespace std;  

#define BOARD_SCALE 20
#define BOARD_HEIGHT 6
#define BOARD_WIDTH 8

//��ȡĳһ�ļ��е������ļ���
void getFiles(string path, vector<string>& files)
{
    //�ļ����  
    long   hFile = 0;
    //�ļ���Ϣ������һ���洢�ļ���Ϣ�Ľṹ��  
    struct _finddata_t fileinfo;
    string p;//�ַ��������·��
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//�����ҳɹ��������
    {
        do
        {
            //�����Ŀ¼,����֮�����ļ����ڻ����ļ��У�  
            if ((fileinfo.attrib &  _A_SUBDIR))
            {
                //�ļ���������"."&&�ļ���������".."
                //.��ʾ��ǰĿ¼
                //..��ʾ��ǰĿ¼�ĸ�Ŀ¼
                //�ж�ʱ�����߶�Ҫ���ԣ���Ȼ�����޵ݹ�������ȥ�ˣ�
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            //�������,�����б�  ,����������жϣ�ֻ����.jpg���ļ��ż����б�
            else
            {
                string a=".bmp";
                string b=".jpg";
                string::size_type idx1,idx2;
                char* temp = fileinfo.name;
                string temp1 = temp;
                idx1=temp1.find(a);
                idx2=temp1.find(b);
                if(idx1 == string::npos && idx2 != string::npos )
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        //_findclose������������
        _findclose(hFile);
    }
}

void main()   
{  
    vector<string> files;
    files.clear();
    string filePath = "G:\\image_1/";
    getFiles(filePath, files );

    cout << "�ҵ����ļ���"<< endl;
    for(int i = 0;i<files.size();i++)
    {
        cout << files[i] <<endl;
    }


    //��ȡÿһ��ͼ�񣬴�����ȡ���ǵ㣬Ȼ��Խǵ���������ؾ�ȷ��   
    cout<<"��ʼ��ȡ�ǵ㡭����������"<<endl;  
    int image_count=0;  /* ͼ������ */  
    Size image_size;  /* ͼ��ĳߴ� */  
    Size board_size = Size(BOARD_HEIGHT,BOARD_WIDTH);    /* �궨����ÿ�С��еĽǵ��� */  
    vector<Point2f> image_points_buf;  /* ����ÿ��ͼ���ϼ�⵽�Ľǵ� */  
    vector<vector<Point2f>> image_points_seq; /* �����⵽�����нǵ� */ 

    for(int i = 0;i<files.size();i++)
    {  
        cout<<files[i]<<endl;

        Mat imageInput=imread(files[i]);

        /* ��ȡ�ǵ� */  
        if (0 == findChessboardCorners(imageInput,board_size,image_points_buf))  
        {             
            cout<<"can not find chessboard corners!\n"; //�Ҳ����ǵ�  
            continue;
        }   
        else   
        {  
            //�ҵ�һ����Ч��ͼƬ
            image_count++;
            if (image_count == 1)  //�����һ��ͼƬʱ��ȡͼ������Ϣ  
            {  
                image_size.width = imageInput.cols;  
                image_size.height =imageInput.rows;           
                cout<<"image_size.width = "<<image_size.width<<endl;  
                cout<<"image_size.height = "<<image_size.height<<endl;  
            }  

            Mat view_gray;  
            cvtColor(imageInput,view_gray,CV_RGB2GRAY);

            /* �����ؾ�ȷ�� */  
            //find4QuadCornerSubpix(view_gray,image_points_buf,Size(5,5)); //�Դ���ȡ�Ľǵ���о�ȷ��  
            cornerSubPix(view_gray, image_points_buf, 
                Size(5,5), 
                Size(-1,-1), 
                TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 
                30,        // max number of iterations 
                0.1));     // min accuracy

            image_points_seq.push_back(image_points_buf);  //���������ؽǵ�

            /* ��ͼ������ʾ�ǵ�λ�� */  
            drawChessboardCorners(view_gray,board_size,image_points_buf,true); //������ͼƬ�б�ǽǵ� 

            //д���ļ�
            string filePath = files[i]; 
            filePath+=".bmp"; 
            imwrite(filePath,view_gray);   
        }  
    }  

    int total = image_points_seq.size();  
    cout<< "��ʹ����"<<total << "��ͼƬ"<<endl;
    cout<<"�ǵ���ȡ��ɣ�\n"; 


    cout<<"��ʼ�궨������������\n";  
    /*������ά��Ϣ*/  
    Size square_size = Size(BOARD_SCALE,BOARD_SCALE);  /* ʵ�ʲ����õ��ı궨����ÿ�����̸�Ĵ�С */  
    vector<vector<Point3f>> object_points; /* ����궨���Ͻǵ����ά���� */  
    /*�������*/  
    Mat cameraMatrix=Mat(3,3,CV_32FC1,Scalar::all(0)); /* ������ڲ������� */  
    vector<int> point_counts;  // ÿ��ͼ���нǵ������  
    Mat distCoeffs=Mat(1,5,CV_32FC1,Scalar::all(0)); /* �������5������ϵ����k1,k2,p1,p2,k3 */  
    vector<Mat> tvecsMat;  /* ÿ��ͼ�����ת���� */  
    vector<Mat> rvecsMat; /* ÿ��ͼ���ƽ������ */  
    /* ��ʼ���궨���Ͻǵ����ά���� */  
    int i,j,t;  
    for (t=0;t<image_count;t++)   
    {  
        vector<Point3f> tempPointSet;  
        for (i=0;i<board_size.height;i++)   
        {  
            for (j=0;j<board_size.width;j++)   
            {  
                Point3f realPoint;  
                /* ����궨�������������ϵ��z=0��ƽ���� */  
                realPoint.x = i*square_size.width;  
                realPoint.y = j*square_size.height;  
                realPoint.z = 0;  
                tempPointSet.push_back(realPoint);  
            }  
        }  
        object_points.push_back(tempPointSet);  
    }  

    /* ��ʼ��ÿ��ͼ���еĽǵ��������ٶ�ÿ��ͼ���ж����Կ��������ı궨�� */  
    for (i=0;i<image_count;i++)  
    {  
        point_counts.push_back(board_size.width*board_size.height);  
    }


    /* ��ʼ�궨 */  
    calibrateCamera(object_points,image_points_seq,image_size,cameraMatrix,distCoeffs,rvecsMat,tvecsMat,CV_CALIB_RATIONAL_MODEL);  
    cout<<"�궨��ɣ�\n";  

    //�Ա궨�����������  
    ofstream fout("caliberation_result.txt");  /* ����궨������ļ� */   

    double total_err = 0.0; /* ����ͼ���ƽ�������ܺ� */  
    double err = 0.0; /* ÿ��ͼ���ƽ����� */  
    vector<Point2f> image_points2; /* �������¼���õ���ͶӰ�� */  
    cout<<"\tÿ��ͼ��ı궨��\n";  
    fout<<"ÿ��ͼ��ı궨��\n";  
    for (i=0;i<image_count;i++)  
    {  
        vector<Point3f> tempPointSet=object_points[i];  
        /* ͨ���õ������������������Կռ����ά���������ͶӰ���㣬�õ��µ�ͶӰ�� */  
        projectPoints(tempPointSet,rvecsMat[i],tvecsMat[i],cameraMatrix,distCoeffs,image_points2);  
        /* �����µ�ͶӰ��;ɵ�ͶӰ��֮������*/  
        vector<Point2f> tempImagePoint = image_points_seq[i];  
        Mat tempImagePointMat = Mat(1,tempImagePoint.size(),CV_32FC2);  
        Mat image_points2Mat = Mat(1,image_points2.size(), CV_32FC2);  
        for (int j = 0 ; j < tempImagePoint.size(); j++)  
        {  
            image_points2Mat.at<Vec2f>(0,j) = Vec2f(image_points2[j].x, image_points2[j].y);  
            tempImagePointMat.at<Vec2f>(0,j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);  
        }  
        err = norm(image_points2Mat, tempImagePointMat, NORM_L2);  
        total_err += err/=  point_counts[i];     
        cout<<"��"<<i+1<<"��ͼ���ƽ����"<<err<<"����"<<endl;     
        fout<<"��"<<i+1<<"��ͼ���ƽ����"<<err<<"����"<<endl;     
    }  

    cout<<"����ƽ����"<<total_err/image_count<<"����"<<endl;     
    fout<<"����ƽ����"<<total_err/image_count<<"����"<<endl<<endl;     

    //���涨����      
    cout<<"��ʼ���涨����������������"<<endl;         
    Mat rotation_matrix = Mat(3,3,CV_32FC1, Scalar::all(0)); /* ����ÿ��ͼ�����ת���� */  
    fout<<"����ڲ�������"<<endl;     
    fout<<cameraMatrix<<endl<<endl;     
    fout<<"����ϵ����\n";     
    fout<<distCoeffs<<endl<<endl<<endl;     
    for (int i=0; i<image_count; i++)   
    {   
        fout<<"��"<<i+1<<"��ͼ�����ת������"<<endl;     
        fout<<tvecsMat[i]<<endl;      
        /* ����ת����ת��Ϊ���Ӧ����ת���� */     
        Rodrigues(tvecsMat[i],rotation_matrix);     
        fout<<"��"<<i+1<<"��ͼ�����ת����"<<endl;     
        fout<<rotation_matrix<<endl;     
        fout<<"��"<<i+1<<"��ͼ���ƽ��������"<<endl;     
        fout<<rvecsMat[i]<<endl<<endl;     
    }     
    cout<<"��ɱ���"<<endl;   
    fout<<endl;

    while(1);
    return ;  
}