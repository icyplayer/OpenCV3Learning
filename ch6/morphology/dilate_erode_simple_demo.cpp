/*
 * dilate_erode_simple_demo.cpp
 *
 *  Created on: 2017年3月12日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_dilate()
{
	// Load image
	Mat image = imread("4.jpg");
	if(!image.data){
		printf("read image failed.\n");
		return false;
	}

	// Create window
	namedWindow("dilate - origin");
	namedWindow("dilate - result");

	// Median bluring
	Mat out, element;
	element = getStructuringElement(MORPH_RECT, Size(15, 15));
	dilate(image, out, element);
//	dilate(image, out, element, Point(-1, -1), 1); // Iterate 1 time
//	dilate(image, out, element, Point(-1, -1), 3); // Iterate 3 times

	// Display
	imshow("dilate - origin", image);
	imshow("dilate - result", out);

	waitKey(0);
	return 0;
}

int main_erode()
{
	// Load image
	Mat image = imread("4.jpg");
	if(!image.data){
		printf("read image failed.\n");
		return false;
	}

	// Create window
	namedWindow("erode - origin");
	namedWindow("erode - result");

	// Median bluring
	Mat out, element;
	element = getStructuringElement(MORPH_RECT, Size(15, 15));
	erode(image, out, element);

	// Display
	imshow("erode - origin", image);
	imshow("erode - result1", out);

	waitKey(0);
	return 0;
}
