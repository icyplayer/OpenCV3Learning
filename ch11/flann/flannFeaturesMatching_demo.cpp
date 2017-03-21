/*
 * flannFeaturesMatching_demo.cpp
 * FLANN: Fast library for Approximate Nearest Neighbors
 *
 *  Created on: 2017年3月21日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main_flannFeaturesMatching()
{
	// 1. Load images
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

	// 2. Define features for SURF detector
	int minHessian = 300; // TODO how to decide the value?
	SURF detector(minHessian);
	vector<KeyPoint> keypoints_1, keypoints_2;
	// Detect SURF interest point with detect function and store in vector
	detector.detect(srcImage1, keypoints_1);
	detector.detect(srcImage2, keypoints_2);

	// 3. Calculate descriptor
	SURF extractor;
	Mat descriptors_1, descriptors_2;
	extractor.compute(srcImage1, keypoints_1, descriptors_1);
	extractor.compute(srcImage2, keypoints_2, descriptors_2);

	// 4. Match features using FLANN
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	// Matching descriptors in 2 images
	matcher.match(descriptors_1, descriptors_2, matches);
	double minDist = 100, maxDist = 0; // Algo topic

	// 5. Fast calculate distance between features, maximum and minimum
	for(int i = 0; i < descriptors_1.rows; ++i){
		double dist = matches[i].distance;
		if(dist < minDist){
			minDist = dist;
		}
		if(dist > maxDist){
			maxDist = dist;
		}
	}
	// Output maximum and minimum distance
	cout <<"> Max dist: " <<maxDist <<endl;
	cout <<"> Min dist: " <<minDist <<endl;

	// 6. Save feature matching result(distance < 2*minDist)
	// Will be done with radiusMatch as well
	vector<DMatch> goodMatches;
	for(int i = 0; i < descriptors_1.rows; ++i){
		if(matches[i].distance < 2*minDist){
			goodMatches.push_back(matches[i]);
		}
	}

	// 7. Draw matching features
	Mat imgMatches;
	drawMatches(srcImage1, keypoints_1, srcImage2, keypoints_2,
			    goodMatches, imgMatches,
				Scalar::all(-1), Scalar::all(-1),
				vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);


	// 8. Output relating info
	/*
	 * DMatch (struct for matching):
	 * - query descriptor index,
	 * - train descriptor index,
	 * - train image index
	 * - distance between descriptors.
	 */
	for(int i =  0; i < goodMatches.size(); ++i){
		printf("> goodMacthes[%d] keypoint1: %d -- keypoint2: %d \n",
				i, goodMatches[i].queryIdx, goodMatches[i].trainIdx);
	}

	// 9. Display result
	imshow("features matched", imgMatches);

	waitKey(0);
	return 0;
}


