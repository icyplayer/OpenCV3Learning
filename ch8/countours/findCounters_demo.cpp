/*
 * findCounters_demo.cpp
 *
 *  Created on: 2017年3月16日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_findContours()
{
	Mat srcImage;
	srcImage = imread("image/1.jpg", 0);
	if(!srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	imshow("origin", srcImage);

	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	srcImage = srcImage > 119;
	imshow("thresholded", srcImage);

	// Define contours and hierarchy
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	// Find contours
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	int index = 0;
	for(; index >= 0; index = hierarchy[index][0]){
		Scalar color(rand()&255, rand()&255, rand()&255);
		drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
	}

	imshow("contours", dstImage);
	waitKey(0);
	return 0;
}

