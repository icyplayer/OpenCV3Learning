/*
 * edgeDetect_demo.cpp
 *
 *  Created on: 2017年3月14日
 *      Author: icyplayer
 */


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat g_srcImage, g_srcImage1, g_srcGrayImage, g_dstImage;

// Canny
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1; // Trackbar param

// Sobel
Mat g_sobelGradient_x, g_sobelGradient_y;
Mat g_sobelAbsGradient_x, g_sobelAbsGradient_y;
int g_sobelKernelSize = 1; // Trackbar param

// Scharr
Mat g_scharrGradient_x, g_scharrGradient_y;
Mat g_scharrAbsGradient_x, g_scharrAbsGradient_y;

// global function
static void on_Canny(int, void *);
static void on_Sobel(int, void *);
void Scharr();

// main
int main()
{
	g_srcImage = imread("5.jpg");
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	namedWindow("origin");
	imshow("origin", g_srcImage);

	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	convertScaleAbs(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);

	namedWindow("Canny", 1);
	namedWindow("Sobel", 1);

	// Create trackbar
	createTrackbar("param: ", "Canny", &g_cannyLowThreshold, 120, on_Canny);
	createTrackbar("param: ", "Sobel", &g_sobelKernelSize, 3, on_Sobel);

	on_Canny(0, 0);
	on_Sobel(0, 0);

	Scharr();

	while(char (waitKey(1)) != 'q'){
	}

	return 0;
}


// BUG: Can't see anything except black screen!
static void on_Canny(int, void *)
{
	// Denoise
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));
	// Run canny
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold*3, 3);
	// Set 0
	g_dstImage = Scalar::all(0);
	// Copy to destination with mask
	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);
	// Show result
	imshow("Canny", g_dstImage);
}


static void on_Sobel(int, void *)
{
	// Calculate grad in X axis
	Sobel(g_srcImage, g_sobelGradient_x, CV_16S, 1, 0, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_x, g_sobelAbsGradient_x);

	// Calculate grad in Y axis
	Sobel(g_srcImage, g_sobelGradient_y, CV_16S, 0, 1, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_y, g_sobelAbsGradient_y);

	addWeighted(g_sobelAbsGradient_x, 0.5, g_sobelAbsGradient_y, 0.5, 0, g_dstImage);

	imshow("Sobel", g_dstImage);
}


void Scharr()
{
	// Calculate grad in X axis
	Scharr(g_srcImage, g_scharrGradient_x, CV_16S, 1, 0, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_x, g_scharrAbsGradient_x);

	// Calculate grad in Y axis
	Scharr(g_srcImage, g_scharrGradient_y, CV_16S, 0, 1, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_y, g_scharrAbsGradient_y);

	addWeighted(g_scharrAbsGradient_x, 0.5, g_scharrAbsGradient_y, 0.5, 0, g_dstImage);

	imshow("Scharr", g_dstImage);
}

