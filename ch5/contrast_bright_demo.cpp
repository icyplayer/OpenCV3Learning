/*
 * contrast_bright_demo.cpp
 *
 *  Created on: 2017年3月10日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Formula: g(x) = a*f(x) + b
static void on_ContrastAndBright(int, void*);


int g_nContrastValue;
int g_nBrightValue;
Mat g_srcImage, g_dstImage;

int main_contrast_and_bright()
{
	// 1. read in image
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		printf("g_srcImage read in failed.\n");
		return false;
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	// 2. Set contrast and bright value
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	// 3. Create result display window
	namedWindow("result", 1);

	// 4. Create trackbar
	createTrackbar("contrast: ", "result", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("bright: ", "result", &g_nBrightValue, 200, on_ContrastAndBright);

	// 5. Init callback function
	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);

	// 6. Quit when 'q' pressed down
	while(char(waitKey(1)) != 'q'){}

	return 0;
}


static void on_ContrastAndBright(int, void*)
{
	namedWindow("origin", 1);

	// Formula: g_dstImage(i,j) = a*g_srcImage(i,j) + b
	// saturate_cast<uchar>: upper overflow protection
	for (int y = 0; y < g_srcImage.rows; ++y){
		for(int x = 0; x < g_srcImage.cols; ++x){
			for(int c = 0; c < 3; ++c){
				g_dstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(
						(g_nContrastValue*0.01) * (g_srcImage.at<Vec3b>(y, x)[c]) +\
						g_nBrightValue);
			}
		}
	}

	// Display image
	imshow("origin", g_srcImage);
	imshow("result", g_dstImage);
}

