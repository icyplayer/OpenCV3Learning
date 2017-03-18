/*
 * moments_demo.cpp
 *
 *  Created on: 2017年3月17日
 *      Author: icyplayer
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;



namespace mo{

#define WINDOW_NAME1 "origin"
#define WINDOW_NAME2 "moments"

Mat g_srcImage, g_grayImage;

// Canny threshold
int g_nThresh = 100;
int g_nThresh_max = 255;

// Color
RNG g_rng(12345);
Mat g_cannyMat_output;


vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

// callback fucntion
void on_ThreshChange(int, void*);

};


int main_moments()
{
	using namespace mo;
	g_srcImage = imread("image/5.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}

	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("threshold", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return 0;
}


namespace mo
{

void on_ThreshChange(int, void*)
{
	// Canny edge detect
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh*2, 3);

	// Find contours
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy,
				 RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// Calculate moments
	vector<Moments> mu(g_vContours.size());
	for(int i = 0; i < g_vContours.size(); ++i){
		mu[i] = moments(g_vContours[i], false);
	}
	// Calculate central moments
	vector<Point2f> mc(g_vContours.size());
	for(unsigned int i = 0; i < g_vContours.size(); ++i){
		mc[i] = Point2f(static_cast<float>(mu[i].m10/mu[i].m00),
				static_cast<float>(mu[i].m01/mu[i].m00));
	}

	// Draw contours
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for(int i = 0; i < g_vContours.size(); ++i){
		Scalar color = Scalar(g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}

	// Display
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);

	// Calculate image's area with m00, and compare to OpenCV
	printf("\toutput: Area and moment's size\n");
	for(unsigned int i = 0; i < g_vContours.size(); ++i){
		cout <<"-------------------------------------------\n"
		     <<"Area of moment[" <<i <<"]:\n";
		printf("by(M_00) = %.2f \tby(OpenCV) = %.2f\tLength:%.2f\n\n",
			   mu[i].m00, contourArea(g_vContours[i]), arcLength(g_vContours[i], true));
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
}


};

