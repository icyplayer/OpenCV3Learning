/*
 * threshold_basic_demo.cpp
 *
 *  Created on: 2017年3月13日
 *      Author: icyplayer
 */

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#define WINDOW_NAME "window"

using namespace cv;
using namespace std;

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

void on_Threshold(int, void *);

int main()
{
	g_srcImage = imread("pool.jpg");
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);

	createTrackbar("mode", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);
	createTrackbar("param-value", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);
	on_Threshold(0, 0);

	while(1){
		int key = waitKey(20);
		if((char) key == 27){
			break;
		}
	}

	return 0;
}


void on_Threshold(int, void *)
{
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
	imshow(WINDOW_NAME, g_dstImage);
}
