//============================================================================
// Name        : main.cpp
// Author      : aawy
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : OpenCV3编程入门，第一章练习程序
//============================================================================

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//#include <opencv2/opencv.hpp>
using namespace cv;

// 图像腐蚀
int main_erosion()
{
	Mat srcImage=imread("1.jpg");
	imshow("erosion", srcImage);
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dstImage;
	erode(srcImage, dstImage, element);
	imshow("result", dstImage);
	waitKey(0);
	return 0;
}


// 图像模糊
int main_blur()
{
	Mat srcImage = imread("1.jpg");
	imshow("blur src", srcImage);
	Mat dstImage;
	blur(srcImage, dstImage, Size(7, 7));	// 均值滤波
	imshow("blur result", dstImage);
	waitKey(0);
	return 0;
}


// Canny边缘检测
int main_canny()
{
	Mat srcImage = imread("4.jpg");
	imshow("canny src", srcImage);
	Mat edge, grayImage;

	// orig -> gray
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	// blur with 3X3 matrix
	blur(grayImage, edge, Size(3, 3));
	// Canny
	Canny(edge, edge, 3, 9, 3);

	imshow("canny result", edge);
	waitKey(0);
	return 0;
}
