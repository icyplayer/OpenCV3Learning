/*
 * roi_demo.cpp
 *
 *  Created on: 2017年3月9日
 *      Author: icyplayer
 */


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// image superposing
bool ROI_AddImage()
{
	Mat srcImage1 = imread("dota_pa.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if(!srcImage1.data){
		printf("read srcImage1 error!\n");
		return false;
	}
	if(!logoImage.data){
		printf("read logoImage error!\n");
		return false;
	}

	Mat imageROI = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));

	Mat mask = imread("dota_logo.jpg", 0);
	logoImage.copyTo(imageROI, mask);
	namedWindow("1 - roi image superposing");
	imshow("1 - roi image superposing", srcImage1);

	return false;
}

// g(x) = (1-a)f0(x) + af1(x)
bool LinearBlending()
{
	// 0. init var
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	// 1. read in images(the 2 must have the same size and same type)
	srcImage2 = imread("mogu.jpg");
	srcImage3 = imread("rain.jpg");
	if(!srcImage2.data){
		printf("read stcImage2 failed.\n");
		return false;
	}
	if(!srcImage3.data){
		printf("read stcImage3 failed.\n");
		return false;
	}

	// 2. Linear blending
	betaValue = 1.0 - alphaValue;
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	// 3. Create and show original image
	namedWindow("2 - linear blending(origin)", 1);
	imshow("2 - linear blending", srcImage2);

	namedWindow("3 - linear blending(origin)", 1);
	imshow("3 - linear blending", dstImage);

	return true;
}


bool ROI_LinearBlending()
{
	// 1. Read in image
	Mat srcImage4 = imread("dota_pa.jpg", 1);
	Mat logoImage = imread("dota_logo.jpg");
	if(!srcImage4.data){
		printf("read srcImage4 failed.\n");
		return false;
	}
	if(!logoImage.data){
		printf("read logoImage failed.\n");
		return false;
	}

	// 2. Define a Mat and set its ROI
	Mat imageROI;
	imageROI = srcImage4(Rect(200, 250, logoImage.cols, logoImage.rows));

	// 3. Superposing logo
	addWeighted(imageROI, 0.5, logoImage, 0.3, 0.0, imageROI);

	// 4. Display result
	namedWindow("4 - ROI linear blending");
	imshow("4 - ROI linear blending", srcImage4);

	return true;
}

int main_roi_demo()
{

//	system("color 5E"); // sh: color: command not found in mac OS X
	if(ROI_AddImage() && LinearBlending() && ROI_LinearBlending()){
		cout <<endl <<"successfully generated." <<endl;
	}

	waitKey(0);
	return 0;
}

