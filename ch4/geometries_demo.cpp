/*
 * geometries_demo.cpp
 *
 *  Created on: 2017年3月9日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "image 1"
#define WINDOW_NAME2 "image 2"
#define WINDOW_WIDTH 600

void DrawEllipse(Mat img, double angle);
void DrawFilledCircle(Mat img, Point center);
void DrawPolygon(Mat img);
void DrawLine(Mat img, Point start, Point end);


int main(void)
{
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rootImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	// Chemical demo
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);

	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2));

	// Combination demo
	DrawPolygon(rootImage);
	rectangle(rootImage,
			  Point(0, 7*WINDOW_WIDTH/8),
			  Point(WINDOW_WIDTH, WINDOW_WIDTH),
			  Scalar(0, 255, 255),
			  8);

	DrawLine(rootImage, Point(0, 15*WINDOW_WIDTH/16),
			Point(WINDOW_WIDTH, 15*WINDOW_WIDTH/16));
	DrawLine(rootImage, Point(WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8),
			Point(WINDOW_WIDTH/4, WINDOW_WIDTH));
	DrawLine(rootImage, Point(WINDOW_WIDTH/2, 7*WINDOW_WIDTH/8),
			Point(WINDOW_WIDTH/2, WINDOW_WIDTH));
	DrawLine(rootImage, Point(3*WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8),
			Point(3*WINDOW_WIDTH/4, WINDOW_WIDTH));

	imshow(WINDOW_NAME1, atomImage);
	moveWindow(WINDOW_NAME1, 0, 200);
	imshow(WINDOW_NAME2, rootImage);
	moveWindow(WINDOW_NAME2, WINDOW_WIDTH, 200);

	waitKey(0);
	return 0;


}


void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;

	ellipse(img,
			Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2),
			Size(WINDOW_WIDTH/4, WINDOW_WIDTH/16),
			angle,
			0,
			360,
			Scalar(255, 129, 0), // Blue
			thickness,
			lineType);
}


void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1; // solid
	int lineType = 8;

	circle(img,
		   center,
		   WINDOW_WIDTH/32,
		   Scalar(0, 0, 255), // Red
		   thickness,
		   lineType);
}


void DrawPolygon(Mat img)
{
	int lineType = 8;

	// Create several points
	Point rootPoints[1][20];
	rootPoints[0][0] = Point(WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8);
	rootPoints[0][1] = Point(3*WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8);
	rootPoints[0][2] = Point(3*WINDOW_WIDTH/4, 13*WINDOW_WIDTH/16);
	rootPoints[0][3] = Point(11*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16);
	rootPoints[0][4] = Point(19*WINDOW_WIDTH/32, 3*WINDOW_WIDTH/8);
	rootPoints[0][5] = Point(3*WINDOW_WIDTH/4, 3*WINDOW_WIDTH/8);

	rootPoints[0][6] = Point(3*WINDOW_WIDTH/4, WINDOW_WIDTH/8);
	rootPoints[0][7] = Point(26*WINDOW_WIDTH/40, WINDOW_WIDTH/8);
	rootPoints[0][8] = Point(26*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
	rootPoints[0][9] = Point(22*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
	rootPoints[0][10] = Point(22*WINDOW_WIDTH/40, WINDOW_WIDTH/8);
	rootPoints[0][11] = Point(18*WINDOW_WIDTH/40, WINDOW_WIDTH/8);

	rootPoints[0][12] = Point(18*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
	rootPoints[0][13] = Point(14*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
	rootPoints[0][14] = Point(14*WINDOW_WIDTH/40, WINDOW_WIDTH/8);
	rootPoints[0][15] = Point(WINDOW_WIDTH/4, WINDOW_WIDTH/8);
	rootPoints[0][16] = Point(WINDOW_WIDTH/4, 3*WINDOW_WIDTH/8);
	rootPoints[0][17] = Point(13*WINDOW_WIDTH/32, 3*WINDOW_WIDTH/8);
	rootPoints[0][18] = Point(5*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16);
	rootPoints[0][19] = Point(WINDOW_WIDTH/4, 13*WINDOW_WIDTH/16);

	const Point* ppt[1] = {rootPoints[0]};
	int npt[] = {20};
	fillPoly(img,
			ppt,
			npt,
			1,
			Scalar(255, 255, 255), // White
			lineType);
}


void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img,
		 start,
		 end,
		 Scalar(0, 0, 0), // Black
		 thickness,
		 lineType);
}
