/*
 * floodFill_trackbar_demo.cpp
 *
 *  Created on: 2017年3月13日
 *      Author: icyplayer
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;

int g_nFillMode = 1;
int g_nLowDifference = 20, g_nUpDifference = 20;
int g_nConnectivity = 4;
int g_bIsColor = true;
bool g_bUseMask = false;
int g_nNewMaskVal = 255;


static void onMouse(int event, int x, int y, int, void *)
{
	if(event != EVENT_LBUTTONDOWN){
		return;
	}

	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;

	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;

	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);

	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;
	int area;

	if(g_bUseMask){
		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp,
						 Scalar(LowDifference, LowDifference, LowDifference),
						 Scalar(UpDifference, UpDifference), flags);
		imshow("mask", g_maskImage);
	}
	else{
		area = floodFill(dst, seed, newVal, &ccomp,
						 Scalar(LowDifference, LowDifference, LowDifference),
						 Scalar(UpDifference, UpDifference, UpDifference), flags);
	}

	imshow("result", dst);
	cout <<area <<" pixels redrawn\n";
}



int main_floodFill_tracbar(int argc, char **argv)
{
	// 1. Load original image
	g_srcImage = imread("bookstore.jpg");
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	g_maskImage.create(g_srcImage.rows+2, g_srcImage.cols+2, CV_8UC1);
	namedWindow("result", 1);

	// 2. Create trackbar
	createTrackbar("max(lower difference)", "result", &g_nLowDifference, 255, 0);
	createTrackbar("max(upper difference)", "result", &g_nUpDifference, 255, 0);

	// 3. Mouse callback
	setMouseCallback("result", onMouse, 0);

	while(1){
		imshow("result", g_bIsColor ? g_dstImage : g_grayImage);

		int c = waitKey(0);
		if((c & 255) == 27){ // <EXC> pressed
			cout <<"Exit...\n";
			break;
		}

		switch((char)c) {
		case '1':
			if(g_bIsColor){
				cout <<"<1> pressed: switch color/gray mode, color=>gray\n";
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);
				g_bIsColor = false;
			}
			else{
				cout <<"<1> pressed: switch color/gray mode, color=>gray\n";
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;
			}
			break;
		case '2': // Display/Hide mask window
			if(g_bUseMask){
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else{
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}
			break;
		case '3':
			cout <<"<3> pressed, back to original image\n";
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;
		case '4':
			cout <<"<4> pressed, use [TODO] flood fill\n";
			g_nFillMode = 0;
			break;
		case '5':
			cout <<"<5> pressed, use [TODO] flood fill\n";
			g_nFillMode = 1;
			break;
		case '6':
			cout <<"<6> pressed, use [TODO] flood fill\n";
			g_nFillMode = 2;
			break;
		case '7':
			cout <<"<7> pressed, use [TODO] 4-bit connectivity\n";
			g_nConnectivity = 4;
			break;
		case '8':
			cout <<"<8> pressed, use [TODO] 8-bit connectivity\n";
			g_nConnectivity = 8;
			break;
		default:
			break;
		}
	}

	return 0;
}







