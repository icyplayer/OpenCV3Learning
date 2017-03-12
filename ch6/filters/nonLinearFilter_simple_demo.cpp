/*
 * linearFilter_simple_demo.cpp
 *
 *  Created on: 2017年3月11日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_medianBlur()
{
	// Load image
	Mat image = imread("2.jpg");
	if(!image.data){
		printf("read image failed.\n");
		return false;
	}

	// Create window
	namedWindow("median blur - origin");
	namedWindow("median blur - result");
	namedWindow("median blur - result1");
	namedWindow("median blur - result2");

	// Median bluring
	Mat out1, out3, out2;
	medianBlur(image, out1, 3);
	medianBlur(image, out2, 5);
	medianBlur(image, out3, 7);

	// Display
	imshow("median blur - origin", image);
	imshow("median blur - result1", out1);
	imshow("median blur - result2", out2);
	imshow("median blur - result3", out3);

	waitKey(0);
	return 0;
}

int main_bilateralFilter()
{
	// Load image
	Mat image = imread("2.jpg");
	if(!image.data){
		printf("read image failed.\n");
		return false;
	}

	// Create window
	namedWindow("bilateral filter - origin");
	namedWindow("bilateral filter - result");

	// Bilateral Filtering
	Mat out;
	bilateralFilter(image, out, 25, 25*2, 25/2);

	// Display
	imshow("bilateral filter - origin", image);
	imshow("bilateral filter - result", out);

	waitKey(0);
	return 0;
}

//
