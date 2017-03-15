/*
 * houghCircles_demo.cpp
 *
 *  Created on: 2017年3月15日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main_houghCircle2();

// Magic numbers: 150, 1000, pt1, pt2
int main_houghCircle()
{
	printf("HoughCircles\n");

	// 1. Load image
	Mat srcImage = imread("img/7.jpg");
	Mat midImage;
	imshow("origin", srcImage);

	// 2. Detect edges
	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);
	GaussianBlur(midImage, midImage, Size(9,9), 2, 2);

	// 3. Hough circle transform
	vector<Vec3f> circles; // compare to SHT, use Vec4i
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);

	// 4. Draw circles
	for(size_t i = 0; i < circles.size(); ++i){
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

	imshow("result", srcImage);

	main_houghCircle2();
	waitKey(0);
	return 0;
}


// original and result picture stored in different Mat
// This additional function shows the subttle differences between Mat::create and Mat::copyTo
int main_houghCircle2()
{
	printf("HoughCircles\n");

	// 1. Load image
	Mat srcImage = imread("img/7.jpg");
	Mat midImage, dstImage;
	imshow("origin1", srcImage);
	srcImage.copyTo(dstImage);
	// dstImage.create(srcImage.rows, srcImage.cols, srcImage.type()); // Cannot match well!

	// 2. Detect edges
	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);
	GaussianBlur(midImage, midImage, Size(9,9), 2, 2);

	// 3. Hough circle transform
	vector<Vec3f> circles; // compare to SHT, use Vec4i
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);

	// 4. Draw circles
	for(size_t i = 0; i < circles.size(); ++i){
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(dstImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(dstImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

	imshow("result2", dstImage);
	waitKey(0);
	return 0;
}



