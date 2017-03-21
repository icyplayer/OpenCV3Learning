/*
 * featuresDetectAndMatch_demo.cpp
 *
 *  Created on: 2017年3月21日
 *      Author: icyplayer
 */


#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/nonfree/nonfree.hpp>

#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
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

	// Define variables and vectors
	int minHessian = 700;
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint> keypoints_1, keypoints_2;

	// Detect SURF interest point with detect function and store in vector
	detector.detect(srcImage1, keypoints_1);
	detector.detect(srcImage2, keypoints_2);

	// Calculate descriptor
	SurfDescriptorExtractor extractor;
	Mat descriptors_1, descriptors_2;
	extractor.compute(srcImage1, keypoints_1, descriptors_1);
	extractor.compute(srcImage2, keypoints_2, descriptors_2);

	// Match features by BF(brute force)
	BruteForceMatcher<L2<float> > matcher;
	vector<DMatch> matches;
	// Matching descriptors in 2 images
	matcher.match(descriptors_1, descriptors_2, matches);

	// Draw matching features
	Mat imgMatches;
	drawMatches(srcImage1, keypoints_1, srcImage2, keypoints_2, matches, imgMatches);

	// Display result
	imshow("features matched", imgMatches);

	waitKey(0);
	return 0;
}


