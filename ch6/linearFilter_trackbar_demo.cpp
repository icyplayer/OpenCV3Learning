/*
 * linearFilter_trackbar_demo.cpp
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

// Global variables
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3;
int g_nBoxFilterValue = 3;
int g_nMeanBlurValue = 3;
int g_nGaussianBlurValue = 3;

// Static function
static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);


int main_linearFilterTrackbar()
{
	// Load image
	g_srcImage = imread("1.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	// Copy image
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();

	// Display original image
	namedWindow("gaussian blur - origin", 1); // WINDOW_AUTOSIZE = 1
	imshow("gaussian blur - origin", g_srcImage);

	// 1. Box filtering
	namedWindow("box filter", 1);
	createTrackbar("kernel:", "box filter", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);

	// 2. Mean filtering
	namedWindow("mean filter", 1);
	createTrackbar("kernel:", "mean filter", &g_nMeanBlurValue, 40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);
//	createTrackbar(TrackbarName, WINDOW_NAME, &nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);
	// 3. Gaussian blur
	namedWindow("gaussian blur", 1);
	createTrackbar("kernel:", "gaussian blur", &g_nGaussianBlurValue, 40, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);

	cout <<"\tScroll trackbar to watch effect\n\n"
			<<"\tPress <q> to exist" <<endl;

	while(char(waitKey(1)) != 'q'){}
	return 0;
}


static void on_BoxFilter(int, void*)
{
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue+1, g_nBoxFilterValue+1));
	imshow("box filter", g_dstImage1);
}


static void on_MeanBlur(int, void*)
{
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue+1, g_nMeanBlurValue+1), Point(-1, -1));
	imshow("mean filter", g_dstImage2);
}


static void on_GaussianBlur(int, void*)
{
	GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1), 0, 0);
	imshow("gaussian blur", g_dstImage3);
}


