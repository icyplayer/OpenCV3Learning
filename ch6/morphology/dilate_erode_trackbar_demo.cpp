/*
 * dilate_erode_trackbar_demo.cpp
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

// Global variables
Mat g_srcImage, g_dstImage;
int g_nTrackbarNumber = 0; // 0:erode, 1:dilate
int g_nStructElementSize = 3;

// Static function
void Process();
void on_TrackbarNumberChange(int, void*);
void on_ElementSizeChange(int, void*);


int main_erode_and_dilate()
{
	// 1. Load image
	g_srcImage = imread("cats.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}

	// 2. Display original image
	namedWindow("origin", 1); // WINDOW_AUTOSIZE = 1
	imshow("origin", g_srcImage);

	// 3. Erode
	namedWindow("result", 1);
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1), Point(g_nStructElementSize, g_nStructElementSize));
	erode(g_srcImage, g_dstImage, element);
	imshow("result", g_dstImage);

	// 4. Create trackbar
	createTrackbar("eroce/dilate", "result", &g_nTrackbarNumber, 1, on_TrackbarNumberChange);
	createTrackbar("kernel:", "result", &g_nStructElementSize, 21, on_ElementSizeChange);

	// 5. Print instructions
	cout <<"\tScroll trackbar to watch effect\n\n"
			<<"\tPress <q> to exist" <<endl;

	// 6. Exists trigger
	while(char(waitKey(1)) != 'q'){}
	return 0;
}


// 2 variable in ONE window, controlled by 2 trackbar
void Process()
{
	// Process kernel
	Mat element = getStructuringElement(MORPH_RECT,
						Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),
						Point(g_nStructElementSize, g_nStructElementSize));
	// Erode/Dilate
	if(g_nTrackbarNumber == 0){
		erode(g_srcImage, g_dstImage, element);
	}
	else{
		dilate(g_srcImage, g_dstImage, element);
	}

	imshow("result", g_dstImage);
}


void on_TrackbarNumberChange(int, void*)
{
	Process();
}


void on_ElementSizeChange(int, void*)
{
	Process();
}


