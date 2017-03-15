/*
 * houghLines_demo.cpp
 *
 *  Created on: 2017年3月15日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

// Magic numbers: 150, 1000, pt1, pt2
int main_houghLines()
{
	printf("HoughLines, SHT, MSHT\n");
	// 1. Load image
	Mat srcImage = imread("img/6.jpg");
	Mat midImage, dstImage;

	// 2. Detect edges
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR); // or CV_GRAY2BGR

	// 3. Hough transform
	vector<Vec2f> lines;
	HoughLines(midImage, lines, 1, CV_PI/180, 150, 0, 0); // 150 is threshold

	// 4. Draw lines
	for(size_t i = 0; i < lines.size(); ++i){
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		// Why?
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));

		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
	}

	imshow("origin", srcImage);
	imshow("Canny", midImage);
	imshow("result", dstImage);
	waitKey(0);
	return 0;
}

