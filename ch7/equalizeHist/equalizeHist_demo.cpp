/*
 * equalizeHist_demo.cpp
 *
 *  Created on: 2017年3月16日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_equalizeHist()
{
	Mat srcImage, dstImage;
	srcImage = imread("img/12.jpg");
	if(!srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}

	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	imshow("origin", srcImage);

	equalizeHist(srcImage, dstImage);
	imshow("result", dstImage);

	waitKey(0);
	return 0;
}


