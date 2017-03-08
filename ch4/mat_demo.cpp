/*
 * mat_demo.cpp
 *
 *  Created on: 2017年3月8日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int mat_create_7method()
{
	// Method 1: Mat()
	// CV_[位数][带符号与否][类型前缀]C[通道数]
	// Scalar: a vector
	Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
	cout <<"M = " <<endl <<" " <<M <<endl <<endl;

	// Method 2
	int sz[3] = {2, 2, 2};
	Mat L(3, sz, CV_8UC(1), Scalar::all(0)); // Why can't I use CV_8UC instead of CV_8UC4?
	// cout <<"L = " <<endl <<" " <<L <<endl <<endl; // Why can't cout: << only works for 2D matrix

	// Method 3:
	// core_c.h: cvarrToMat: converts array (CvMat or IplImage) to cv::Mat
	// http://answers.opencv.org/question/23440/any-way-to-convert-iplimage-to-cvmat-in-opencv-300/
	// http://blog.csdn.net/tsyccnh/article/details/39099023
	IplImage* img = cvLoadImage("1.jpg", 1);
	Mat mtx = cvarrToMat(img); // For OpenCV 3.0.0 (in 3.2.0 stable also works)
//	Mat mtx(img, false); // For OpenCV 2.x: Transform IplImage* to Mat
//	cout <<"mtx = " <<endl <<" " <<mtx <<endl <<endl;

	// Method 4: Mat::create()
	Mat M4;
	M4.create(4, 4, CV_8UC(2));
	cout <<"M4 = " <<endl <<" " <<M4 <<endl <<endl;

	// Method 5: Matlab format
	// eye, all one/zero
	Mat E = Mat::eye(4, 4, CV_64F);
	Mat O = Mat::ones(2, 2, CV_32F);
	Mat Z = Mat::zeros(3, 3, CV_8UC1);
	cout <<"E = " <<endl <<" " <<E <<endl <<endl;
	cout <<"O = " <<endl <<" " <<O <<endl <<endl;
	cout <<"Z = " <<endl <<" " <<Z <<endl <<endl;
	// p.s: Mat::eye()
	Mat E2 = Mat::eye(3, 3, CV_8UC1);
	cout <<"E2 = " <<endl <<" " <<E2 <<endl <<endl;

	// Method 6: Split with comma
	Mat C = (Mat_<double>(3,3) <<0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout <<"C = " <<endl <<" " <<C <<endl <<endl;

	// Method 7: create new header for existing Mat
	Mat RowClone = C.row(1).clone();
	cout <<"RowClone = " <<endl <<" " <<RowClone <<endl <<endl;

	return 0;
}


