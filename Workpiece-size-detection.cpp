#include <opencv2/opencv.hpp>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
using namespace cv;

char image_name[10];
char windows_name[10];
int b = 1;
int* c = &b;
int i = 1;
void SavePic(Mat a)
{
	if(i<=40) 
	{
		sprintf(image_name,"%s%d%s","image" , i , ".jpg");	//图像名加编码	
		if(i==40) 
		imwrite(image_name,a);
		i++;
	}
	if(i==41)
	{
		//for(i=0;i<=39;i++)
		//{
		//	sprintf(image_name,"%s%d%s","image" , i , ".jpg");	//图像名加编码
		//	remove(image_name);
		//}
		Mat image = imread("image40.jpg");
		//imshow("Processing Image", image);
		Mat gray, binaryimage;
		cvtColor(image, gray, CV_RGB2GRAY);
		//imshow("Processing Image", gray);
		threshold(gray, binaryimage,105,256,CV_THRESH_BINARY);
		imshow("Processing Image", binaryimage);
		IplImage binaryimage2 = IplImage(binaryimage);//将Mat类对象binaryimage转成IplImage结构
		int x = binaryimage2.width;
		int y = binaryimage2.height;
		cout<<"x="<<x<<endl<<"y="<<y<<endl;
		//cout<<"像素值:"<<binaryimage.row(240) <<endl;
		cout<<binaryimage.at<uchar>(240,240)<<endl;
	  /*for(int i=0;i<=480;i++)
		{
			for(int j=0; j<=640; j++)
			{
				binaryimage.at<uchar>(i,j);
			}
		}*/
		//vector<vector<Point> > contours;
		//vector<Vec4i>hierarchy;
		//Mat dst = Mat::zeros(img.rows, img.cols, CV_8UC3);
		//findContours(binaryimage, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
		//imshow("Processing Image", contours);
		//findContours( binaryimage2 , contours , CV_RETR_LIST, CV_CHAIN_APPROX_NONE, Point(0, 0));
		//Point center;
		//center.x = x/2;
		//center.y = y/2;
		//cout<<"x="<<center.x<<endl<<"y="<<center.y<<endl;
		*c = 0;
	}
	//ifstream fin(image_name);
	//if(!fin) 
	//{
		//imwrite(image_name,a);
	//}
	//else
	//{
		//remove(image_name);

	//}

	
	
	//for(int i=0;i<3;i++)
	//{
	//	sprintf(image_name,"%s%d%s","image" , i , ".jpg");	//图像名加编码
	//	ifstream fin(image_name);							//读取括号中的文件，返回
	//	if(!fin)
	//	{
	//		imwrite(image_name,a);						//用上面的图像名保存图像
	//	}
	//	else
	//	{
	//		remove(image_name);
	//		imwrite(image_name,a);
	//	}
	//}
}


int main()
{

	time_t t=time(NULL);
	char* time;
	time = ctime(&t);
	printf("time:%s", time);
	VideoCapture capture(0);
	Mat frame;										//建立一个mat容器数组

	while(1)
	{
		capture>>frame;									//将捕捉的图像传入容器
		//sprintf(windows_name,"%s%d","camera" , i );	//图像名加编码
		imshow("camera",frame);							//展示图像到窗口camera
		char key = cvWaitKey(20);
		if (*c) 
		{
			SavePic(frame);
		}

		if(key==27) break;
		
	}
	return 0;
}

