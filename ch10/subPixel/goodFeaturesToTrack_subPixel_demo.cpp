/*
 * goodFeaturesToTrack_subPixel_demo.cpp
 *
 * based on goodFeaturesToTrack_demo.cpp
 *
 *  Created on: 2017年3月21日
 *      Author: icyplayer
 */


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;


// Shi Tomasi corner detection
namespace sp
{

#define WINDOW_NAME "Shi-Tomasi corner detection"

Mat g_srcImage, g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(12345);

void on_GoodFeaturesToTrack(int, void*);

}


int main_shiTomasi()
{
	using namespace sp;
	g_srcImage = imread("image/3.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}

	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("maximum corner number:", WINDOW_NAME, &g_maxCornerNumber,
			       g_maxTrackbarNumber, on_GoodFeaturesToTrack);
	imshow("origin", g_srcImage);
	on_GoodFeaturesToTrack(0, 0);

	waitKey(0);
	return 0;
}


namespace sp
{

void on_GoodFeaturesToTrack(int, void*)
{
	if(g_maxCornerNumber <= 1){
		g_maxCornerNumber = 1;
	}

	// Shi-Tomasi params
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	double k = 0.04;
	Mat srcImage1 = g_srcImage.clone();

	// Shi-Tomasi corner detection
	goodFeaturesToTrack(g_grayImage,
			            corners,
						g_maxCornerNumber,
						qualityLevel,
						minDistance, // Minimum distance between corners
						Mat(), // Area of interest
						blockSize,
						false, // Not using harris corner detection
						k);

	// Output information
	cout <<"Corner number detected: " <<corners.size() <<endl;

	// Draw corners detected
	int r = 4;
	for(unsigned int i = 0; i < corners.size(); ++i){
		circle(srcImage1, corners[i], r,
			   Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)),
			   -1, 8, 0); // -1: 实心圆
	}

	imshow(WINDOW_NAME, srcImage1);
}

}






