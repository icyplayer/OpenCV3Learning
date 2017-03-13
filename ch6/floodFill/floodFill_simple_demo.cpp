/*
 * floodFill_simple_demo.cpp
 *
 *  Created on: 2017年3月13日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_floodFill_simple()
{
	Mat image = imread("6.jpg");
	namedWindow("origin");
	namedWindow("result");
	imshow("origin", image);

	Rect ccomp;
	floodFill(image, Point(50, 300), Scalar(155, 255, 55), &ccomp,
			  Scalar(20, 20, 20), Scalar(20, 20, 20));
	imshow("result", image);

	waitKey(0);
	return 0;
}




