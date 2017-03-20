/*
 * matchTemp_demo.cpp
 *
 *  Created on: 2017年3月20日
 *      Author: icyplayer
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


namespace mt
{

#define WINDOW_NAME1 "origin"
#define WINDOW_NAME2 "result"

Mat g_srcImage, g_templateImage, g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

void on_Matching(int, void *);

};


int main()
{
	using namespace mt;
	// 1. Read in image and convert to HSV space
	g_srcImage = imread("image/6-1.jpg", 1);
	g_templateImage = imread("image/6-2.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	if(!g_templateImage.data){
		printf("read g_templateImage failed.\n");
		return false;
	}

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);

	createTrackbar("method", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching);
	on_Matching(0, 0);
	waitKey(0);
	return 0;
}


namespace mt
{

void on_Matching(int, void *)
{
	Mat srcImage;
	g_srcImage.copyTo(srcImage);

	// Init Mat for result output
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
	g_resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1); // result MUST be (W-w+1, H-h+1)

	// Match template and normalize
	matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());

	// Locate best matching
	double minValue, maxValue;
	Point minLocation, maxLocation, matchLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

	// SQDIFF, SQDIFF_NORMED: less is better; for the rest: the larger the better
	if(g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED){
		matchLocation = minLocation;
	}
	else{
		matchLocation = maxLocation;
	}

	// Draw rectangle and display result
	rectangle(srcImage, matchLocation,
			  Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),
			  Scalar(0, 0, 255), 2, 8, 0);
	rectangle(g_resultImage, matchLocation,
			  Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),
			  Scalar(0, 0, 255), 2, 8, 0);


	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, g_resultImage);

}

};

