/*
 * resize_and_pyramid_demo.cpp
 *
 *  Created on: 2017年3月13日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "window"

int main_resize_pyramid()
{
	Mat g_srcImage, g_dstImage, g_tmpImage;

	g_srcImage = imread("7.jpg");
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, g_srcImage);

	g_tmpImage = g_srcImage;
	g_dstImage = g_srcImage;

	int key = 0;
	while(1){
		key = waitKey(9);
		switch(key){
		// Exists trigger
		case 27: case 'q':
			return 0;
			break;

		// Image zoom in
		case 'a':
			pyrUp(g_tmpImage, g_dstImage, Size(g_tmpImage.cols*2, g_tmpImage.rows*2) );
			printf("<a> pressed: pyrUp: image size*2\n");
			break;
		case 'w': // typedef Size2i Size;
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols*2, g_tmpImage.rows*2) );
			printf("<w> pressed: resize: image size*2\n");
			break;
		case '1':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols*2, g_tmpImage.rows*2) );
			printf("<1> pressed: resize: image size*2\n");
			break;
		case '3':
			pyrUp(g_tmpImage, g_dstImage, Size(g_tmpImage.cols*2, g_tmpImage.rows*2) );
			printf("<3> pressed: pyrUp: image size*2\n");
			break;

		// Image zoom out
		case 'd':
			pyrDown(g_tmpImage, g_dstImage, Size(g_tmpImage.cols/2, g_tmpImage.rows/2) );
			printf("<d> pressed: pyrDown: image size/2\n");
			break;
		case 's':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols/2, g_tmpImage.rows/2) );
			printf("<s> pressed: resize: image size/2\n");
			break;
		case '2':
			resize(g_tmpImage, g_dstImage,
				   Size(g_tmpImage.cols/2, g_tmpImage.rows/2), (0, 0), (0, 0), 2);
			printf("<2> pressed: resize: image size/2\n");
			break;
		case '4':
			pyrDown(g_tmpImage, g_dstImage, Size(g_tmpImage.cols/2, g_tmpImage.rows/2) );
			printf("<4> pressed: pyrDown: image size/2\n");
			break;
		default:
			break;
		}

		// Display result
		imshow("result", g_dstImage);

		g_tmpImage = g_dstImage;
	}

	return 0;
}
