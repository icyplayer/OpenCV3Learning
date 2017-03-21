/*
 * findHomography_demo.cpp
 *
 *  Created on: 2017年3月21日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
//#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{
	// 1. Load images
	Mat srcImage1 = imread("image/3-1.jpg", 1);
	Mat srcImage2 = imread("image/3-2.jpg", 1);
	if(!srcImage1.data){
		printf("read srcImage1 failed.\n");
		return false;
	}
	if(!srcImage2.data){
		printf("read srcImage2 failed.\n");
		return false;
	}

	// 2. Define features for SURF detector
	int minHessian = 400; // TODO how to decide the value?
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint> keypoints_object, keypoints_scene;

	// 3. Detect SURF interest point with detect function and store in vector
	detector.detect(srcImage1, keypoints_object);
	detector.detect(srcImage2, keypoints_scene);

	// 4. Calculate descriptor
	SurfDescriptorExtractor extractor;
	Mat descriptors_object, descriptors_scene;
	extractor.compute(srcImage1, keypoints_object, descriptors_object);
	extractor.compute(srcImage2, keypoints_scene, descriptors_scene);

	// 5. Match features using FLANN
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	// Matching descriptors in 2 images
	matcher.match(descriptors_object, descriptors_scene, matches);
	double minDist = 100, maxDist = 0; // Algo topic

	// 6. Calculate distance between features, maximum and minimum
	for(int i = 0; i < descriptors_object.rows; ++i){
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

	// 7. Save feature matching result(distance < 3*minDist)
	// Will be done with radiusMatch as well
	vector<DMatch> goodMatches;
	for(int i = 0; i < descriptors_object.rows; ++i){
		if(matches[i].distance < 3*minDist){
			goodMatches.push_back(matches[i]);
		}
	}

	// 8. Draw matching features
	Mat imgMatches;
	drawMatches(srcImage1, keypoints_object, srcImage2, keypoints_scene,
			    goodMatches, imgMatches,
				Scalar::all(-1), Scalar::all(-1),
				vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);


	// Define 2 local vector variable
	vector<Point2f> obj;
	vector<Point2f> scene;

	// 9. Output relating info
	/*
	 * DMatch (struct for matching):
	 * - query descriptor index,
	 * - train descriptor index,
	 * - train image index
	 * - distance between descriptors.
	 */
	for(int i =  0; i < goodMatches.size(); ++i){
		obj.push_back(keypoints_object[goodMatches[i].queryIdx].pt);
		scene.push_back(keypoints_scene[goodMatches[i].trainIdx].pt);

	}

	// 10. Calculate perspective matrix
	Mat H = findHomography(obj, scene, CV_RANSAC);
	// Get corner from image to be test
	vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0, 0);
	obj_corners[1] = cvPoint(srcImage1.cols, 0);
	obj_corners[2] = cvPoint(srcImage1.cols, srcImage1.rows);
	obj_corners[3] = cvPoint(0, srcImage1.rows);

	vector<Point2f> scene_corners(4);
	perspectiveTransform(obj_corners, scene_corners, H);

	// Draw lines between qurey and train corners
	line(imgMatches,
		 scene_corners[0] + Point2f(static_cast<float>(srcImage1.cols), 0),
		 scene_corners[1] + Point2f(static_cast<float>(srcImage1.cols), 0),
		 Scalar(255, 0, 123),
		 4);
	line(imgMatches,
		 scene_corners[1] + Point2f(static_cast<float>(srcImage1.cols), 0),
		 scene_corners[2] + Point2f(static_cast<float>(srcImage1.cols), 0),
		 Scalar(255, 0, 123),
		 4);
	line(imgMatches,
		 scene_corners[2] + Point2f(static_cast<float>(srcImage1.cols), 0),
		 scene_corners[3] + Point2f(static_cast<float>(srcImage1.cols), 0),
		 Scalar(255, 0, 123),
		 4);
	line(imgMatches,
		 scene_corners[3] + Point2f(static_cast<float>(srcImage1.cols), 0),
		 scene_corners[0] + Point2f(static_cast<float>(srcImage1.cols), 0),
		 Scalar(255, 0, 123),
		 4);


	// 9. Display result
	imshow("good matches & object detection", imgMatches);

	waitKey(0);
	return 0;
}


