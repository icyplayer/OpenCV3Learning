/*
 * convexHull_demo.cpp
 *
 *  Created on: 2017年3月16日
 *      Author: icyplayer
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_convexHull()
{
	cout <<"\tPress <ESC>/<Q>/<q> to quit\n"
		 <<"\tPress other key to generate a image and convexHull result"
		 <<endl;
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	while(1){
		char key;
		int count = (unsigned)rng%100 + 3;
		vector<Point> points;

		for(int i = 0; i < count; ++i){
			Point pt;
			pt.x = rng.uniform(image.cols/4, image.cols*3/4);
			pt.y = rng.uniform(image.rows/4, image.rows*3/4);
			points.push_back(pt);
		}

		// Convex hull
		vector<int> hull;
		convexHull(Mat(points), hull, true); // clockwise

		// Draw RNG color points
		image = Scalar::all(0);
		for(int i = 0; i < count; ++i){
			circle(image, points[i], 3,
				   Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)),
				   FILLED, LINE_AA);
		}

		int hullCount = (int)hull.size();
		Point pt0 = points[hull[hullCount - 1]];

		// Draw convex's edges
		for(int i = 0; i < hullCount; ++i){
			Point pt = points[hull[i]];
			line(image, pt0, pt, Scalar(255, 255, 255), 2, LINE_AA);
			pt0 = pt;
		}

		// Display result
		imshow("convex hull", image);
		key = (char)waitKey(0);
		if(key == 27 || key == 'q' || key == 'Q'){
			break;
		}
	}

	return 0;




}


