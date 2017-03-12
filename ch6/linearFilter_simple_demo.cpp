/*
 * linearFilter_simple_demo.cpp
 *
 *  Created on: 2017年3月11日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int boxFilter_demo()
{
	// Load image
	Mat image = imread("2.jpg");
	if(!image.data){
		printf("read image failed.\n");
		return false;
	}

	// Create window
	namedWindow("box blur - origin");
	namedWindow("box blur - result");
	namedWindow("box blur - result1");
	namedWindow("box blur - result2");

	// Box Filtering
	/* According to the result shown,
	 * 5*5 kernel is the clearest of the three.
	 */
	Mat out1, out3, out2;
	boxFilter(image, out1, -1, Size(3, 3));
	boxFilter(image, out2, -1, Size(5, 5));
	boxFilter(image, out3, -1, Size(7, 7));

	// Display
	imshow("box blur - origin", image);
	imshow("box blur - result", out1);
	imshow("box blur - result1", out2);
	imshow("box blur - result2", out3);

	waitKey(0);
	return 0;
}

int meanFilter_demo()
{
	// Load image
	Mat image = imread("2.jpg");
	if(!image.data){
		printf("read image failed.\n");
		return false;
	}

	// Create window
	namedWindow("normalized blur - origin");
	namedWindow("normalized blur - result");
	namedWindow("normalized blur - result1");
	namedWindow("normalized blur - result2");

	// Mean Filtering
	/* According to the result shown,
	 * 5*5 kernel is the clearest of the three.
	 */
	Mat out1, out3, out2;
	blur(image, out1, Size(3, 3));
	blur(image, out2, Size(5, 5));
	blur(image, out3, Size(7, 7));

	// Display
	imshow("normalized blur - origin", image);
	imshow("normalized blur - result", out1);
	imshow("normalized blur - result1", out2);
	imshow("normalized blur - result2", out3);

	waitKey(0);
	return 0;
}


int gaussian_demo()
{
	// Load image
	Mat image = imread("2.jpg");
	if(!image.data){
		printf("read image failed.\n");
		return false;
	}

	// Create window
	namedWindow("gaussian blur - origin");
	namedWindow("gaussian blur - result");
	namedWindow("gaussian blur - result1");
	namedWindow("gaussian blur - result2");

	// Gaussian bluring

	Mat out1, out2, out3;
	GaussianBlur(image, out1, Size(3, 3), 0, 0, BORDER_DEFAULT);
	GaussianBlur(image, out2, Size(5, 5), 0, 0);
	GaussianBlur(image, out3, Size(7, 7), 0, 0);

	// Display
	imshow("gaussian blur - origin", image);
	imshow("gaussian blur - result", out1);
	imshow("gaussian blur - result1", out2);
	imshow("gaussian blur - result2", out3);

	waitKey(0);
	return 0;
}

