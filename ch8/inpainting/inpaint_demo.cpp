/*
 * inpaint_demo.cpp
 *
 *  Created on: 2017年3月18日
 *      Author: icyplayer
 */


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo/photo.hpp>
#include <iostream>

using namespace cv;
using namespace std;


namespace inpt
{

#define WINDOW_NAME1 "origin"
#define WINDOW_NAME2 "inpainting"

Mat g_srcImage, g_srcImage1, g_inpaintMask;

Point g_prevPt(-1, -1);

// callback fucntion
void on_Mouse(int event, int x, int y, int flags, void*);

};


int main()
{
	using namespace inpt;
	// 1. Read in image
	g_srcImage = imread("image/7.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	g_srcImage1 = g_srcImage.clone();
	g_inpaintMask = Mat::zeros(g_srcImage1.size(), CV_8U);

	// Display original image
	imshow(WINDOW_NAME1, g_srcImage1);

	// 2. Set callback for mouse
	setMouseCallback(WINDOW_NAME1, on_Mouse, 0);

	// 3. Looping
	while(1){
		char c = (char)waitKey(0);
		if( c == 27 || c == 'Q' || c == 'q'){
			break;
		}

		if( c == '2'){ // Roll back to original image
			g_inpaintMask = Scalar::all(0);
			g_srcImage.copyTo(g_srcImage1);
			imshow(WINDOW_NAME1, g_srcImage1);
		} // c=='2'

		if( c == '1' || c == ' '){
			Mat inpaintedImage;
			inpaint(g_srcImage1, g_inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
			// Define params
			imshow(WINDOW_NAME2, inpaintedImage);
		} // c=='1' || c==' '
	} // while(1)

	return 0;
}


namespace inpt
{

void on_Mouse(int event, int x, int y, int flags, void*)
{
	// Mouse not in screen
	if(x < 0 || x >= g_srcImage.cols || y < 0 || y >= g_srcImage.rows){
		return;
	}

	// Left button
	if(event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON)){
		g_prevPt = Point(-1, -1);
	}
	else if(event == EVENT_LBUTTONDOWN){
		g_prevPt = Point(x, y);
	}

	// Drag
	else if(event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)){
		Point pt(x, y);
		if(g_prevPt.x < 0){
			g_prevPt = pt;
		}
		line(g_inpaintMask, g_prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage1, g_prevPt, pt, Scalar::all(255), 5, 8, 0);
		g_prevPt = pt;
		imshow(WINDOW_NAME1, g_srcImage1);
	}
}

};




