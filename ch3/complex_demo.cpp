/*
 * complex_demo.cpp
 *
 *  Created on: 2017年3月7日
 *      Author: icyplayer
 */


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


int image_mix()
{
	// Example 1: imread and imshow
	Mat girl1 = imread("girl.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	namedWindow("1 - girl");
	imshow("1 - girl", girl1);

	// Example 2: Image mixing
	Mat dota2 = imread("dota.jpg", CV_LOAD_IMAGE_COLOR);
	Mat logo3 = imread("logo.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("2 - dota");
	imshow("2 - dota", dota2);

	namedWindow("3 - logo");
	imshow("3 - logo", logo3);

	Mat dotaROI;
	// Method 1
	dotaROI = dota2(Rect(800, 350, logo3.cols, logo3.rows));
	fprintf(stdout, "dotaroi:%d, %d; logo:%d, %d\n", dotaROI.rows, dotaROI.cols, logo3.rows, logo3.cols);
	// Method 2
//	dotaROI = dota2(Range(350, 350+logo3.rows), Range(800, 800+logo3.cols));

	// Add logo onto the image
	// 本步骤出错，融合失败，报错
	addWeighted(dotaROI, 0.5, logo3, 0.3, 0.0, dotaROI);
	namedWindow("4 - dota+logo");
	imshow("4 - dota+logo", dota2);

	// Example 3: image output
	imwrite("generated.jpg", dota2);

	waitKey();
	return 0;
}





