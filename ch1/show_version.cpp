/*
 * show_version.cpp
 *
 *  Created on: 2017年2月27日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
//#include <stdio.h>

using namespace cv;

int main_version(int argc, const char** argv)
{
	printf("Current OpenCV version is %s", CV_VERSION);
	return 0;
}
