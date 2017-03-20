/*
 * cornerHarris_demo.cpp
 *
 *  Created on: 2017年3月20日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main_cornerHarris()
{
	Mat srcImage = imread("image/1.jpg", 0);
	imshow("origin", srcImage);

	Mat cornerStrength;
	cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);

	Mat harrisCorner;
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);
	imshow("binary result", harrisCorner);
	waitKey(0);
	return 0;
}

