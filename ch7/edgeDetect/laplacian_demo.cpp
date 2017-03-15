/*
 * laplacian_demo.cpp
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


int main_laplacian()
{
	Mat srcImage, srcGrayImage, dstImage, abs_dst;
	srcImage = imread("img/3.jpg");

	imshow("Laplacian - origin", srcImage);

	// Denoise with gaussian blur
	GaussianBlur(srcImage, srcImage, Size(3,3), 0, 0, BORDER_DEFAULT);

	// Convert to grayscale
	cvtColor(srcImage, srcGrayImage, COLOR_BGR2GRAY);

	// Laplacian
	Laplacian(srcGrayImage, dstImage, CV_16S, 3, 1, 0, BORDER_DEFAULT);


	convertScaleAbs(dstImage, abs_dst);
	imshow("Laplacian - result", abs_dst);

	waitKey(0);
	return 0;
}
