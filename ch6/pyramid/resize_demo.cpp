/*
 * resize_demo.cpp
 *
 *  Created on: 2017年3月13日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_resize()
{
	Mat srcImage = imread("girl.jpg");
	Mat tmpImage, dstImage1, dstImage2;
	tmpImage = srcImage;

	imshow("origin", srcImage);

	// resize
	resize(tmpImage, dstImage1, Size(tmpImage.cols/2, tmpImage.rows/2), (0,0), (0,0), 3);
	resize(tmpImage, dstImage2, Size(tmpImage.cols*2, tmpImage.rows*2), (0,0), (0,0), 3);

	imshow("result 1", dstImage1);
	imshow("result 2", dstImage2);

	waitKey(0);
	return 0;
}
