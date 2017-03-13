/*
 * morph_trackbar_demo.cpp
 *
 *  Created on: 2017年3月13日
 *      Author: icyplayer
 */


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


#define OPEN_CLOSE 		0
#define ERODE_DILATE	1
#define TOP_BLACK_HAT 	2


Mat g_srcImage, g_dstImage;
int g_nElementShape = MORPH_RECT;

int g_nMaxIterationNum = 10;

int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;

std::string winNames[3] = {"Open/Close", "Erode/Dilate", "Top Hat/Black Hat"};


static void on_OpenClose(int, void*);
static void on_ErodeDilate(int, void*);
static void on_TopBlackHat(int, void*);


int main_morph_trackbar()
{
	// 1. Load image
	g_srcImage = imread("captain.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}

	// 2. Display original image
	namedWindow("origin", 1);
	imshow("origin", g_srcImage);

	// 3. Create 3 window
	namedWindow(winNames[OPEN_CLOSE], 1);
	namedWindow(winNames[ERODE_DILATE], 1);
	namedWindow(winNames[TOP_BLACK_HAT], 1);

	// 4. Init var
	g_nOpenCloseNum = 9;
	g_nErodeDilateNum = 9;
	g_nTopBlackHatNum = 2;

	// Create trackbar
	createTrackbar("iteration", winNames[OPEN_CLOSE], &g_nOpenCloseNum, g_nMaxIterationNum*2+1, on_OpenClose);
	createTrackbar("iteration", winNames[ERODE_DILATE], &g_nErodeDilateNum, g_nMaxIterationNum*2+1, on_ErodeDilate);
	createTrackbar("iteration", winNames[TOP_BLACK_HAT], &g_nTopBlackHatNum, g_nMaxIterationNum*2+1, on_TopBlackHat);

	while(1){
		int c;
		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackHatNum, 0);

		// Get key pressed
		c = waitKey(0);
		if((char)c == 'q' || (char)c == 27){// <q> or <ESC>
			break;
		}
		if((char)c == 49){// <1>
			g_nElementShape = MORPH_ELLIPSE;
		}
		else if((char)c == 50){// <2>
			g_nElementShape = MORPH_RECT;
		}
		else if((char)c == 51){// <3>
			g_nElementShape = MORPH_CROSS;
		}
		else if((char)c == ' '){
			g_nElementShape = (g_nElementShape + 1) %3;// Loop between 3 shapes
		}
	}

	return 0;
}


static void on_OpenClose(int, void*)
{
	int offset = g_nOpenCloseNum - g_nMaxIterationNum; // Offset
	int abs_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape,
						Size(abs_offset*2+1, abs_offset*2+1),
						Point(abs_offset, abs_offset));

	if(offset < 0){
		morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
	}
	else{
		morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE, element);
	}

	// Display
	imshow(winNames[OPEN_CLOSE], g_dstImage);
}


static void on_ErodeDilate(int, void*)
{
	int offset = g_nErodeDilateNum - g_nMaxIterationNum; // Offset
	int abs_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape,
						Size(abs_offset*2+1, abs_offset*2+1),
						Point(abs_offset, abs_offset));

	if(offset < 0){
		erode(g_srcImage, g_dstImage, element);
	}
	else{
		dilate(g_srcImage, g_dstImage, element);
	}

	// Display
	imshow(winNames[ERODE_DILATE], g_dstImage);
}


static void on_TopBlackHat(int, void*)
{
	int offset = g_nTopBlackHatNum - g_nMaxIterationNum; // Offset
	int abs_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape,
						Size(abs_offset*2+1, abs_offset*2+1),
						Point(abs_offset, abs_offset));

	if(offset < 0){
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
	}
	else{
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	}

	// Display
	imshow(winNames[TOP_BLACK_HAT], g_dstImage);
}
