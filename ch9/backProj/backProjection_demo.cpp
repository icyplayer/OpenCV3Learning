/*
 * backProjection_demo.cpp
 *
 *  Created on: 2017年3月20日
 *      Author: icyplayer
 */



#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


namespace bp
{

#define WINDOW_NAME1 "origin"

Mat g_srcImage, g_hsvImage, g_hueImage;
int g_bins = 30;

void on_BinChange(int, void *);

};


int main_backProjection()
{
	using namespace bp;
	// 1. Read in image and convert to HSV space
	g_srcImage = imread("image/5.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	// Convert to gray image and denoise
	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);

	// 2. Split Hue channel
	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = {0, 0};
	mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

	// 3. Create trackbar to input bin numbers
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	// g_bins is the KEY param
	createTrackbar("hue group interval", WINDOW_NAME1, &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);

	// 4. Show result
	imshow(WINDOW_NAME1, g_srcImage);

	// 5. Wait for key pressed
	waitKey(0);
	return 0;
}


namespace bp
{

void on_BinChange(int, void *)
{
	MatND hist;
	int histSize = MAX(g_bins, 2);
	float hue_range[] = {0, 180};
	const float* ranges = {hue_range};

	// Calculate histogram and normalize
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	// Caculate back projection
	MatND backproj;
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);

	// Show back projection
	imshow("back projection", backproj);

	int w = 400, h = 400;
	int bin_w = cvRound((double)w/histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	// Draw histogram
	for(int i = 0; i < g_bins; ++i){
		rectangle(histImg,
				  Point(i*bin_w, h),
				  Point((i+1)*bin_w, h - cvRound(hist.at<float>(i)*h/255.0)),
				  Scalar(100, 123, 255), -1);
	}

	imshow("histogram", histImg);
}

};

