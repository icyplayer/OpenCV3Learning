/*
 * fiveFilters_trackbar_demo.cpp
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

#define IDX_BOX 		 	0
#define IDX_MEAN 		 	1
#define IDX_GAUSSIAN 	 	2
#define IDX_MEDIAN 		 	3
#define IDX_BILATERAL 		4

// Global variables
Mat g_srcImage;
Mat g_dstImage[5];
int g_nFilterValue[5] = {6, 10, 6, 10, 10};
string g_nWinNames[5] = {"box filter", "mean filter", "gaussian blur", "median blur", "bilateral filter"};

// Static function
static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);
static void on_MedianBlur(int, void*);
static void on_BilateralFilter(int, void*);

void (*callbacks[5])(int, void*) = {on_BoxFilter, on_MeanBlur, on_GaussianBlur, on_MedianBlur, on_BilateralFilter};

int main()
{
	// Load image
	g_srcImage = imread("3.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	// Copy image
	for(int i = 0; i < 5; ++i){
		g_dstImage[i] = g_srcImage.clone();
	}

	// Display original image
	namedWindow("gaussian blur - origin", 1); // WINDOW_AUTOSIZE = 1
	imshow("gaussian blur - origin", g_srcImage);

	// Bind and call 5 filters' callback
	for(int i = 0; i < 5; ++i){
		namedWindow(g_nWinNames[i], 1);
		createTrackbar("kernel:", g_nWinNames[i], &g_nFilterValue[i], 50, *callbacks[i]);
		(*callbacks[i])(g_nFilterValue[i], 0);
	}

	cout <<"\tScroll trackbar to watch effect\n\n"
			<<"\tPress <q> to exist" <<endl;

	while(char(waitKey(1)) != 'q'){}
	return 0;
}


static void on_BoxFilter(int, void*)
{
	boxFilter(g_srcImage, g_dstImage[IDX_BOX], -1,
			Size(g_nFilterValue[IDX_BOX]+1, g_nFilterValue[IDX_BOX]+1));
	imshow(g_nWinNames[IDX_BOX], g_dstImage[IDX_BOX]);
}


static void on_MeanBlur(int, void*)
{
	blur(g_srcImage, g_dstImage[IDX_MEAN],
			Size(g_nFilterValue[IDX_MEAN]+1, g_nFilterValue[IDX_MEAN]+1), Point(-1, -1));
	imshow(g_nWinNames[IDX_MEAN], g_dstImage[IDX_MEAN]);
}


static void on_GaussianBlur(int, void*)
{
	GaussianBlur(g_srcImage, g_dstImage[IDX_GAUSSIAN],
			Size(g_nFilterValue[IDX_GAUSSIAN]*2+1, g_nFilterValue[IDX_GAUSSIAN]*2+1), 0, 0);
	imshow(g_nWinNames[IDX_GAUSSIAN], g_dstImage[IDX_GAUSSIAN]);
}


static void on_MedianBlur(int, void*)
{
	medianBlur(g_srcImage, g_dstImage[IDX_MEDIAN], g_nFilterValue[IDX_MEDIAN]*2+1);
	imshow(g_nWinNames[IDX_MEDIAN], g_dstImage[IDX_MEDIAN]);
}


static void on_BilateralFilter(int, void*)
{
	bilateralFilter(g_srcImage, g_dstImage[IDX_BILATERAL], g_nFilterValue[IDX_BILATERAL],
			g_nFilterValue[IDX_BILATERAL]*2, g_nFilterValue[IDX_BILATERAL]/2);
	imshow(g_nWinNames[IDX_BILATERAL], g_dstImage[IDX_BILATERAL]);
}


