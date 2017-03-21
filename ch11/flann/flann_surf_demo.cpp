/*
 * flann_surf_demo.cpp
 *
 *  Created on: 2017年3月21日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>

#include <iostream>

using namespace std;
using namespace cv;


int main_bug_flann_surf()
{
	// 1. Load images and convert gray image
	Mat trainImage = imread("image/2.jpg");
	Mat trainImage_gray;
	imshow("origin", trainImage);
	cvtColor(trainImage, trainImage_gray, CV_BGR2GRAY);

	// 2. Detect SURF keypoints, get train descriptors
	vector<KeyPoint> train_keyPoint;
	Mat trainDescriptor;
	int minHessian = 80;
	SurfFeatureDetector featureDetector(minHessian);
	featureDetector.detect(trainImage_gray, train_keyPoint, trainDescriptor);

	// 3. Create descriptor based on FLANN
	FlannBasedMatcher matcher;
	vector<Mat> train_desc_collection(1, trainDescriptor);
	matcher.add(train_desc_collection);
	matcher.train();

	// 4. Create video object, define frame count
	VideoCapture cap(0);
	unsigned int frameCount = 0;

	// Loop until <q> pressed
	while(char(waitKey(1)) != 'q'){
		// Param setting
		int64 time0 = getTickCount();
		Mat testImage, testImage_gray;
		cap >>testImage;
		if(testImage.empty()){
			continue;
		}

		// Convert to gray
		cvtColor(trainImage, trainImage_gray, CV_BGR2GRAY);

		// Detect S keypoint, get test image's descriptor
		vector<KeyPoint> test_keyPoint;
		Mat testDescriptor;
		featureDetector.detect(testImage_gray, test_keyPoint);
		featureDetector.compute(testImage_gray, test_keyPoint, testDescriptor);

		// Match train and query descriptors
		vector<vector<DMatch> > matches;
		matcher.knnMatch(testDescriptor, matches, 2);

		// Lowe's algorithm
		vector<DMatch> goodMatches;
		for(unsigned int i = 0; i < matches.size(); ++i){
			if(matches[i][0].distance < 0.6*matches[i][1].distance){
				goodMatches.push_back(matches[i][0]);
			}
		}

		Mat dstImage;
		drawMatches(testImage, test_keyPoint, trainImage, train_keyPoint, goodMatches, dstImage);
		imshow("matching result", dstImage);

		// Print fps info
		cout <<"Current frame rate:" <<getTickFrequency() / (getTickCount() - time0) <<endl;
	}

	return 0;
}

