/*
 * morph_simple_demo.cpp
 *
 *  Created on: 2017年3月13日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_morph()
{
	Mat image = imread("5.jpg");
	namedWindow("origin");
	namedWindow("result");
	imshow("origin", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
//	morphologyEx(image, image, MORPH_OPEN, element);
//	morphologyEx(image, image, MORPH_CLOSE, element);
	morphologyEx(image, image, MORPH_GRADIENT, element);
//	morphologyEx(image, image, MORPH_TOPHAT, element);
//	morphologyEx(image, image, MORPH_BLACKHAT, element);
//	morphologyEx(image, image, MORPH_ERODE, element);
//	morphologyEx(image, image, MORPH_DILATE, element);

	imshow("result", image);
	waitKey(0);
	return 0;
}




