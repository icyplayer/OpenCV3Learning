/*
 * output_demo.cpp
 *
 *  Created on: 2017年3月8日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int mat_output()
{
	Mat r = Mat(10, 3, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));

	// Style 0: default (OpenCV)
	cout <<"r (Default) = " <<r <<";" <<endl <<endl;

	// Style 1: Matlab
	cout <<"r (Matlab) = " <<format(r, Formatter::FMT_MATLAB) <<";" <<endl;

	// Style 2: Python
	cout <<"r (Python) = " <<format(r, Formatter::FMT_PYTHON) <<";" <<endl;

	// Style 3: Comma seperated values, CSV
	cout <<"r (CSV) = " <<format(r, Formatter::FMT_CSV) <<";" <<endl;

	// Style 4: Numpy
	cout <<"r (Numpy) = " <<format(r, Formatter::FMT_NUMPY) <<";" <<endl;

	// Style 5: C
	cout <<"r (C) = " <<format(r, Formatter::FMT_C) <<";" <<endl;

	return 0;
}


int point_output()
{
	Point2f p(6, 2);
	cout <<"2D p = " <<p <<";" <<endl;
	Point3f p3f(2, 6, 8);
	cout <<"3D p3f = " <<p3f <<";" <<endl;

	// Definition and output of Mat(std::vector)
	vector<float> v;
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	cout <<"shortvec = " <<Mat(v) <<";" <<endl;

	// Define and output std::vector<Pointxx>
	vector<Point2f> points(20);
	for(size_t i = 0; i < points.size(); ++i){
		points[i] = Point2f((float)(i * 5), (float)(i % 7));
	}

	cout <<"points = " <<points <<";" <<endl;
	return 0;
}


