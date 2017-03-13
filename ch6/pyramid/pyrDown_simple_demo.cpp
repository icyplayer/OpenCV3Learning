/*
 * pyrDown_simple_demo.cpp
 *
 *  Created on: 2017年3月13日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_pryDown()
{
	Mat srcImage = imread("girl.jpg");
	Mat tmpImage, dstImage;
	tmpImage = srcImage;
	imshow("origin", srcImage);

	// Pyramid down
	pyrDown(tmpImage, dstImage, Size(tmpImage.cols/2, tmpImage.rows/2));

	// Display result
	imshow("result", dstImage);

	waitKey(0);
	return 0;
}
