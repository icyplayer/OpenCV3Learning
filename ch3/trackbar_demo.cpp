/*
 * trackbar_demo.cpp
 *
 *  Created on: 2017年3月7日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#define WINDOW_NAME "linear mixed demo"

const int g_nMaxAlphaValue = 100; // Maximum alpha value

Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;


// Callback function for trackbar
void on_Trackbar(int g_nAlphaValueSlider, void*)
{
	double g_dAlphaValue;
	double g_dBetaValue;

	g_dAlphaValue = (double)g_nAlphaValueSlider/g_nMaxAlphaValue;
	g_dBetaValue = (1.0 - g_dAlphaValue);

	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
	imshow(WINDOW_NAME, g_dstImage);
}


int main(int argc, char** argv)
{

	int g_nAlphaValueSlider; // Trackbar's corresponding variable

	g_srcImage1 = imread("2.jpg");
	g_srcImage2 = imread("3.jpg");
	if(!g_srcImage1.data){
		printf("Image 2.jpg read in failed.\n");
		return -1;
	}
	if(!g_srcImage2.data){
		printf("Image 3.jpg read in failed.\n");
		return -1;
	}

	g_nAlphaValueSlider = 70;
	namedWindow(WINDOW_NAME, 1);

	// Create a trackbar widget
	char TrackbarName[50];
	sprintf(TrackbarName, "alpha %d", g_nMaxAlphaValue);
	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	// Show result by callback function
	on_Trackbar(g_nAlphaValueSlider, 0);

	waitKey(0);
	return 0;
}
