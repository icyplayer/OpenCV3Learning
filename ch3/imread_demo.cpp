/*
 * show_version.cpp
 *
 *  Created on: 2017年3月6日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
//#include <stdio.h>

using namespace cv;

int color_channel()
{
	Mat img1 = imread("1.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	Mat img2 = imread("1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img3 = imread("1.jpg", CV_LOAD_IMAGE_COLOR);

	imshow("origin", img1);
	imshow("gray", img2);
	imshow("colorful", img3);

	waitKey(0);
	return 0;
}





