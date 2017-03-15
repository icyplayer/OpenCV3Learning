/*
 * houghLinesP_demo.cpp
 *
 *  Created on: 2017年3月15日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Magic numbers: 150, 1000, pt1, pt2
int main_houghLinesP()
{
	printf("HoughLinesP, PPHT\n");

	// 1. Load image
	Mat srcImage = imread("img/6.jpg");
	Mat midImage, dstImage;

	// 2. Detect edges
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR); // or CV_GRAY2BGR

	// 3. Hough transform
	vector<Vec4i> lines; // compare to SHT, use Vec4i
	HoughLinesP(midImage, lines, 1, CV_PI/180, 80, 50, 10); // TODO how to verify the r/theta's threshold?

	// 4. Draw lines
	for(size_t i = 0; i < lines.size(); ++i){
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);
	}

	imshow("origin", srcImage);
	imshow("Canny", midImage);
	imshow("result", dstImage);
	waitKey(0);
	return 0;
}

