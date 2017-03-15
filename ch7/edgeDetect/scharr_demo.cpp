/*
 * sobel_demo.cpp
 *
 *  Created on: 2017年3月14日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


using namespace cv;
using namespace std;


int main_scharr()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dstImage;
	Mat srcImage = imread("img/4.jpg");

	imshow("Scharr - origin", srcImage);

	// Calculate grad in X axis
	Scharr(srcImage, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("Scharr - X result", abs_grad_x);

	// Calculate grad in Y axis
	Scharr(srcImage, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Scharr - Y result", abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dstImage);

	imshow("Scharr - Whole result", dstImage);
	waitKey(0);
	return 0;
}
