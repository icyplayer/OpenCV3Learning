/*
 * remap_demo.cpp
 *
 *  Created on: 2017年3月15日
 *      Author: icyplayer
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main_remap()
{
	printf("remap\n");
	// 1. Load image
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	srcImage = imread("img/9.jpg");
	imshow("origin", srcImage);

	// 2. Create images, X/Y remapping
	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1); // CV_(位数）+（数据类型）+（通道数）, C1, one channel
	map_y.create(srcImage.size(), CV_32FC1);

	// 3. Loop each pixels, modify map_x and map_y's value
	// 变换：上下颠倒的镜像
	for(int j = 0; j < srcImage.rows; ++j){
		for(int i = 0; i < srcImage.cols; ++i){
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
		}
	}

	remap(srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	imshow("result", dstImage);
	waitKey(0);
	return 0;
}
