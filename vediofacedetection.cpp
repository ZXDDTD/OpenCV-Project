#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void detectAndDisplay( Mat frame );

//将分类器放到源文件夹
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
String nose_cascade_name = "haarcascade_mcs_nose.xml";
//String mouth_cascade_name = "haarcascade_mcs_mouth.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
CascadeClassifier nose_cascade;
//CascadeClassifier mouth_cascade;
string window_name = "Capture - Face detection";
RNG rng(12345);

int main( void )
{
  VideoCapture capture;
  Mat frame;

  //1. 载入已经训练好的分类器
  if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  if( !nose_cascade.load( nose_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
//  if( !nose_cascade.load( mouth_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  //2. 读录像
  capture.open( 0 );
  if( capture.isOpened() )
  {
    for(;;)
    {
      capture >> frame;

      //3. 如果录像不为空则调用函数检测
      if( !frame.empty() )
      {detectAndDisplay( frame ); }
      else
      { printf(" --(!) No captured frame -- Break!"); break; }

      int c = waitKey(10);
      if( (char)c == 'c' ) { break; }

    }
  }
  return 0;
}

//人脸检测函数
void detectAndDisplay( Mat frame )
{
   std::vector<Rect> faces;   //创建矩形类型的faces容器用来存放检测到的人脸矩形
   Mat frame_gray;

   cvtColor( frame, frame_gray, COLOR_BGR2GRAY ); //转灰度图
   equalizeHist( frame_gray, frame_gray );   //直方图均衡化
   //分类器多尺度检测函数
   face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
   //对每张脸都创建中心点对象并画图
   for( size_t i = 0; i < faces.size(); i++ )
    {
      Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
      ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 1, 8, 0 );
      Mat faceROI = frame_gray( faces[i] );  

      //在每张脸中的寻找眼睛
	  std::vector<Rect> eyes;
      eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );   //眼睛的多尺度检测函数
      for( size_t j = 0; j < eyes.size(); j++ )
      {
         Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
         int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
         circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 1, 8, 0 );
      }

	  //在每张脸中寻找鼻子
	  std::vector<Rect> nose;
	  nose_cascade.detectMultiScale( faceROI, nose, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
	  for( size_t k = 0; k < nose.size(); k++)
	  {
		 Point nose_center( faces[i].x + nose[k].x + nose[k].width/2, faces[i].y + nose[k].y + nose[k].height/2 );   //生成鼻子中心点类对象，并赋初值
		 ellipse( frame, nose_center, Size( nose[k].width/2, nose[k].height/2), 0, 0, 360, Scalar( 200, 0, 100 ), 1, 8, 0 );//画椭圆
	  }
		//在每张脸中寻找嘴巴
	    //std::vector<Rect> mouth;
		//mouth_cascade.detectMultiScale( faceROI, mouth, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
		//for( size_t l = 0; l < mouth.size(); l++)
		//{
		//	Point mouth_center( faces[i].x + mouth[l].x + mouth[l].width/2, faces[i].y + mouth[l].y + mouth[l].height/2 );
		//	ellipse( frame, mouth_center, Size( mouth[l].width/2, mouth[l].height/2), 0, 0, 360, Scalar( 255, 255, 255 ), 1, 8, 0 );
		//}
    }
    //在窗口上展示
    imshow( window_name, frame );
}
