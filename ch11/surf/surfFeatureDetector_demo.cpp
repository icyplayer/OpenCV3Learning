/*
 * featureDetector_demo.cpp
 *
 *  Created on: 2017年3月21日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main_surfFeatureDetector()
{
	Mat srcImage1 = imread("image/1-1.jpg", 1);
	Mat srcImage2 = imread("image/1-2.jpg", 1);
	if(!srcImage1.data){
		printf("read srcImage1 failed.\n");
		return false;
	}
	if(!srcImage2.data){
		printf("read srcImage2 failed.\n");
		return false;
	}

	imshow("origin 1", srcImage1);
	imshow("origin 2", srcImage2);

	// Define variables and vectors
	int minHessian = 400;
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint> keypoints_1, keypoints_2;

	// Detect SURF interest point with detect function and store in vector
	detector.detect(srcImage1, keypoints_1);
	detector.detect(srcImage2, keypoints_2);

	// Draw features
	Mat img_keypoints_1, img_keypoints_2;

	/*
	 * Modified code for manually choosing drawKeypoints's DrawMatchesFlags
	 * based on example given.
	 */
	while(1){
		char key = (char) waitKey(0);
		const char *pc = &key;
		if((int)key == 27 || key == 'q' || key == 'Q'){
			break;
		}
		switch (key){
		case '0': case '1': case '2': case '4':
			drawKeypoints(srcImage1, keypoints_1, img_keypoints_1, Scalar::all(-1), (const int)atoi(pc));
			drawKeypoints(srcImage2, keypoints_2, img_keypoints_2, Scalar::all(-1), (const int)atoi(pc));

			imshow("features detect 1", img_keypoints_1);
			imshow("features detect 2", img_keypoints_2);

			cout <<"DrawMatchesFlags = " <<key <<endl;
			break;
		default:
			break;
		}
	}

	return 0;
}
