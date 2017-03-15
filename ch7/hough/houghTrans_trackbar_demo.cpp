/*
 * houghTrans_trackbar_demo.cpp
 *
 *  Created on: 2017年3月15日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage, g_midImage;
vector<Vec4i> g_lines;
int g_nThreshold = 100;

static void on_HoughLines(int, void *);

int main_houghTrans()
{

	g_srcImage = imread("img/8.jpg");
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	imshow("origin", g_srcImage);

	namedWindow("result", 1);
	createTrackbar("value: ", "result", &g_nThreshold, 200, on_HoughLines);
	Canny(g_srcImage, g_midImage, 50, 200, 3);
	cvtColor(g_midImage, g_dstImage, COLOR_GRAY2BGR); // or CV_GRAY2BGR
	on_HoughLines(g_nThreshold, 0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI/180, 80, 50, 10);

	imshow("result", g_dstImage);
	waitKey(0);
	return 0;
}


static void on_HoughLines(int, void *)
{
	Mat dstImage = g_dstImage.clone();
	Mat midImage = g_midImage.clone();

	vector<Vec4i> lines;
	HoughLinesP(midImage, lines, 1, CV_PI/180, g_nThreshold+1, 50, 10);
	for(size_t i = 0; i < lines.size(); ++i){
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 50), 1, LINE_AA);
	}
	imshow("result", dstImage);
}


