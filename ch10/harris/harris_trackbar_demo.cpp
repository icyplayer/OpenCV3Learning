/*
 * harris_trackbar_demo.cpp
 *
 *  Created on: 2017年3月20日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;


// harris corner
namespace hc
{

#define WINDOW_NAME1 "program 1"
#define WINDOW_NAME2 "program 2"

Mat g_srcImage, g_srcImage1, g_grayImage;
int thresh = 30;
int max_thresh = 175;

void on_CornerHarris(int, void*);

}

int main()
{
	using namespace hc;
	g_srcImage = imread("image/2.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}

	imshow("origin", g_srcImage);
	g_srcImage1 = g_srcImage.clone(); // deep copy
	cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY); // gray

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	createTrackbar("threshold:", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris);
	on_CornerHarris(0, 0);

	waitKey(0);
	return 0;
}


namespace hc
{

void on_CornerHarris(int, void*)
{
	Mat dstImage, normImage, scaledImage;

	// Init
	dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage1 = g_srcImage.clone(); // why one more time?
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);// Convert normalized image to 8UC

	// Draw
	for(int j = 0; j < normImage.rows; ++j){
		for(int i = 0; i < normImage.cols; ++i){
			if((int)normImage.at<float>(j,i) > (thresh+80)){
				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}

	imshow(WINDOW_NAME1, g_srcImage1);
	imshow(WINDOW_NAME2, scaledImage);
}

}



