/*
 * canny_demo.cpp
 *
 *  Created on: 2017年3月14日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


using namespace cv;
using namespace std;


int main_canny()
{
	Mat srcImage = imread("img/1.jpg");
	Mat srcImage1 = srcImage.clone();

	imshow("Canny - origin", srcImage);

	// rgb => gray => denoise => canny => get mask => copy to origin
	Mat dstImage, edgeImage, grayImage;
	dstImage.create(srcImage1.size(), srcImage1.type());
	cvtColor(srcImage1, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, edgeImage, Size(3, 3));
	Canny(edgeImage, edgeImage, 3, 9, 3);
	dstImage = Scalar::all(0);
	imshow("Canny - edge", edgeImage); // Add by myself

	srcImage1.copyTo(dstImage, edgeImage);
	imshow("Canny - result", dstImage);
	waitKey(0);
	return 0;
}
