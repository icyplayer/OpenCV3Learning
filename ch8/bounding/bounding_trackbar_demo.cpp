/*
 * bounding_trackbar_demo.cpp
 *
 *  Created on: 2017年3月17日
 *      Author: icyplayer
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


namespace bounding{

#define WINDOW_NAME1 "origin"
#define WINDOW_NAME2 "bounding"

Mat g_srcImage, g_grayImage;

// Canny threshold
int g_nThresh = 50;
int g_nThresh_max = 255;

// Color
RNG g_rng(12345);

Mat g_thresholdImage_output;

vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

// callback fucntion
void on_ContoursChange(int, void*);

};


int main_bounding()
{
	using namespace bounding;
	g_srcImage = imread("image/4.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}

	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("threshold", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ContoursChange);
	on_ContoursChange(0, 0);

	waitKey(0);
	return 0;
}


namespace bounding
{

void on_ContoursChange(int, void*)
{
	// Canny edge detect
	threshold(g_grayImage, g_thresholdImage_output, g_nThresh, 255, THRESH_BINARY);

	// Find contours
	findContours(g_thresholdImage_output, g_vContours, g_vHierarchy,
					 RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point> > contours_poly(g_vContours.size());
	vector<Rect> boundRect(g_vContours.size());
	vector<Point2f> center(g_vContours.size());
	vector<float> radius(g_vContours.size());

	// Loop each part of the image
	for(unsigned int i = 0; i < g_vContours.size(); ++i){
		approxPolyDP(Mat(g_vContours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);
	}

	// Draw contuors and convex
	Mat drawing = Mat::zeros(g_thresholdImage_output.size(), CV_8UC3);
	for(unsigned int i = 0; i < g_vContours.size(); ++i){
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point()); // Draw poly
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0); // Draw rectangle
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0); // Draw circle
	}

	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);
}

};

