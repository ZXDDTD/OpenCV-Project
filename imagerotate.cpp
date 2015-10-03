#include <opencv2\opencv.hpp>
#include <iostream>
#include "highgui.h"

using namespace std;

//逆时针旋转图像degree角度（原尺寸）  
void rotateImage(IplImage* img, IplImage *img_rotate,int degree)  
{  
    //旋转中心为图像中心  
    CvPoint2D32f center;    
    center.x=float (img->width/2.0+0.5);  
    center.y=float (img->height/2.0+0.5);  
    //计算二维旋转的仿射变换矩阵  
    float m[6];              
    CvMat M = cvMat( 2, 3, CV_32F, m );  
    cv2DRotationMatrix( center, degree,1, &M);  
    //变换图像，并用黑色填充其余值  
    cvWarpAffine(img,img_rotate, &M,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS,cvScalarAll(0) );  


}  

int main(){
	IplImage* img1=cvLoadImage("fruits.jpg");
	IplImage* img2=cvLoadImage("fruits.jpg");
	rotateImage(img1, img2, 45);
	cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("rotate", CV_WINDOW_AUTOSIZE);
	cvShowImage("original",img1);
	cvShowImage("rotate",img2);
	cvWaitKey(0);
	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	cvDestroyWindow("original");
	cvDestroyWindow("rotate");
}
