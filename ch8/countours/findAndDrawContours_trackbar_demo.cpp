/*
 * findAndDrawContours_trackbar_demo.cpp
 *
 *  Created on: 2017年3月16日
 *      Author: icyplayer
 */


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


namespace contour{

#define WINDOW_NAME1 "origin"
#define WINDOW_NAME2 "contours"

Mat g_srcImage, g_grayImage;

// Canny threshold
int g_nThresh = 80;
int g_nThresh_max = 255;

// Contour retrieval modes
int g_nRetrieval = 1;
int g_nRetrieval_max = RETR_TREE;

// Contour approximation algorithm
int g_nApproxAlgo = CHAIN_APPROX_SIMPLE;
int g_nApproxAlgo_max = CHAIN_APPROX_TC89_KCOS;

// Color
RNG g_rng(12345);

Mat g_cannyMat_output;

vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

// callback fucntion
void on_ThreshChange(int, void*);
};


int main_contour_trackbar()
{
	using namespace contour;
	g_srcImage = imread("image/2.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	// Convert to gray image and denoise
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	// Create window and display original image
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	// Create trackbar
	createTrackbar("canny threshold", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
	createTrackbar("retrieval mode", WINDOW_NAME1, &g_nRetrieval, g_nRetrieval_max, on_ThreshChange);
	createTrackbar("algorithm", WINDOW_NAME1, &g_nApproxAlgo, g_nApproxAlgo_max, on_ThreshChange); // Contour approximation algorithm

	on_ThreshChange(0, 0);
	waitKey(0);
	return 0;
}


namespace contour
{

void on_ThreshChange(int, void*)
{
	// Canny edge detect
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh*2, 3);

	// Find contours
	try{
		// Add retrieval mode and approximate algorithm control.
		findContours(g_cannyMat_output, g_vContours, g_vHierarchy,
					 g_nRetrieval, g_nApproxAlgo, Point(0, 0));
	}
	catch(exception &e){
		cerr <<e.what() <<endl;
	}

	// Draw contours
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for(int i = 0; i < g_vContours.size(); ++i){
		Scalar color = Scalar(g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}

	imshow(WINDOW_NAME2, drawing);
}

};
