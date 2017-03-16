/*
 * affine_transform_demo.cpp
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

#define WINDOW_NAME1 "origin"
#define WINDOW_NAME2 "warp"
#define WINDOW_NAME3 "warp then rotated"

// Should be studied and think deeper in your OpenGL class.

int main()
{
	// 1. Init
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];

	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	// 2. Load images
	srcImage = imread("img/11.jpg");
	if(!srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

	// 3. Set source and destination's triangle
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[0] = Point2f(0, static_cast<float>(srcImage.rows - 1));

	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols *0.0),
                             static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols *0.65),
                             static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols *0.15),
                             static_cast<float>(srcImage.rows*0.6));
	// 4. Get Affine matrix
	warpMat = getAffineTransform(srcTriangle, dstTriangle);

	// 5. Apply matrix on image
	warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());

	// 6. Affine transform then rotate
	Point center = Point(dstImage_warp.cols/2, dstImage_warp.rows/2);
	double angle = -30.0;
	double scale = 0.8;
	rotMat = getRotationMatrix2D(center, angle, scale);
	warpAffine(dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size());

	// 7. Show effect
	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, dstImage_warp);
	imshow(WINDOW_NAME3, dstImage_warp_rotate);

	// 8. Wait to quit
	waitKey(0);
	return 0;
}

