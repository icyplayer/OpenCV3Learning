/*
 * watershed_demo.cpp
 *
 *  Created on: 2017年3月18日
 *      Author: icyplayer
 */


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;



namespace wt{

#define WINDOW_NAME "[window 1]"

Mat g_srcImage, g_maskImage;

// callback fucntion
void on_Mouse(int event, int x, int y, int flags, void*);

};

Point prevPt(-1, -1);


int main()
{
	using namespace wt;
	// 1. Read in image
	g_srcImage = imread("image/6.jpg", 1);
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}

	// Display original image
	imshow(WINDOW_NAME, g_srcImage);
	// Init mask and gray image
	Mat srcImage, grayImage;
	g_srcImage.copyTo(srcImage); // Why need this copy?
	cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY);
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR); // What's this?
	g_maskImage = Scalar::all(0);

	// 2. Set callback for mouse
	setMouseCallback(WINDOW_NAME, on_Mouse, 0);

	// 3. Looping
	while(1){
		char c = (char)waitKey(0);
		if( c == 27){
			break;
		}

		if( c == '2'){ // Roll back to original image
			g_maskImage = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow("image", g_srcImage);
		} // c=='2'

		if( c == '1' || c == ' '){
			// Define params
			int i, j, compCount = 0;
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;

			// Find contours
			findContours(g_maskImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
			// "empty" exception handle
			if(contours.empty()){
				continue;
			}

			// Copy mask
			Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = Scalar::all(0);

			// Draw contours
			for(int index = 0; index >= 0; index = hierarchy[index][0], ++compCount){
				drawContours(maskImage, contours, index,
							 Scalar::all(compCount+1), -1, 8, hierarchy, INT_MAX);
			}/* for(int index = 0; index >= 0; index = hierarchy[index][0], ++compCount) */

			if(compCount == 0){
				continue;
			} /* if(compCount == 0) */

			// Generate random color
			vector<Vec3b> colorTab;
			for(i = 0; i < compCount; ++i){
				colorTab.push_back(	Vec3b( (uchar)theRNG().uniform(0, 255),
										   (uchar)theRNG().uniform(0, 255),
										   (uchar)theRNG().uniform(0, 255) ) );
			}/* for(i = 0; i < compCount; ++i) */

			// Calculate and output time cost
			double dTime = (double)getTickCount();
			watershed(srcImage, maskImage);
			dTime = (double)getTickCount() - dTime;
			printf("\ttime cost:%gms\n", dTime*100./getTickFrequency());

			// Loop and store watershed image into Mat
			Mat watershedImage(maskImage.size(), CV_8UC3);
			for(i = 0; i < maskImage.rows; ++i){
				for(j = 0; j < maskImage.cols; ++j){
					int index = maskImage.at<int>(i, j);
					if(index == -1){
						watershedImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
					}
					else if(index <= 0 || index > compCount){
						watershedImage.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
					}
					else{
						watershedImage.at<Vec3b>(i, j) = colorTab[index - 1];
					}
				}
			} /* for(i = 0; i < maskImage.rows; ++i) */

			// Mix gray image and watershed image
			watershedImage = watershedImage * 0.5 + grayImage * 0.5;
			imshow("watershed transform", watershedImage);
		} // c=='1' || c==' '
	} // while(1)

	return 0;
}


namespace wt
{

void on_Mouse(int event, int x, int y, int flags, void*)
{
	// Mouse not in screen
	if(x < 0 || x >= g_srcImage.cols || y < 0 || y >= g_srcImage.rows){
		return;
	}

	// Left button
	if(event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON)){
		prevPt = Point(-1, -1);
	}
	else if(event == EVENT_LBUTTONDOWN){
		prevPt = Point(x, y);
	}

	// Drag
	else if(event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)){
		Point pt(x, y);
		if(prevPt.x < 0){
			prevPt = pt;
		}
		line(g_maskImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow(WINDOW_NAME, g_srcImage);
	}
}

};


