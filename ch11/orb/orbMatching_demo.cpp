/*
 * orbMatching_demo.cpp
 *
 *  Created on: 2017年3月21日
 *      Author: icyplayer
 *  reinstalled
 *  $ brew install opencv --with-ffmpeg --with-gstreamer  --with-tbb  --with-vtk   --with-opengl
 *   FAILED
 *  $ brew install opencv --with-ffmpeg --with-gstreamer  --with-vtk
 *  FAILED
 *  $ brew install opencv
 *  SUCCESS
 *  (some libs was missing in previous installation
 *  and then we can
 */


#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
//#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{
	// 1. Load images
	Mat srcImage = imread("image/4.jpg", 1);
	Mat grayImage;
	if(!srcImage.data){
		printf("read srcImage failed.\n");
		return false;
	}
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	// 1. Define params
	OrbFeatureDetector featureDetector;
	vector<KeyPoint> keyPoints;
	Mat descriptors;

	// 2. Detect keypoints with detect() and store in vector
	featureDetector.detect(grayImage, keyPoints);

	// 3. Calculate descriptro
	OrbDescriptorExtractor featureExtractor;
	featureDetector.compute(grayImage, keyPoints, descriptors);

	// 4. Match features based on FLANN
	flann::Index flannIndex(descriptors, flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);

	// 5. Init video capture objects
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 360);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 900);
	unsigned int frameCount = 0;// fps

	// 6. Loop until <ESC> pressed
	while((char)waitKey(1) != 27){
		double time0 = static_cast<double>(getTickCount()); // Mark start time
		Mat captureImage, captureImage_gray;// Mat for video capture
		cap >>captureImage;
		if(captureImage.empty()){
			continue;
		}

		// Convert captured video to gray
		cvtColor(captureImage, captureImage_gray, CV_BGR2GRAY);

		// 7. Detect SIFT keypoints and capture descriptors in test image
		vector<KeyPoint> captureKeyPoints;
		Mat captureDescription;
		// 8. Detect keypoints with detect() and store in vector
		featureDetector.detect(captureImage_gray, captureKeyPoints);

		// 9. Calculate descriptors
		featureExtractor.compute(captureImage_gray, captureKeyPoints, captureDescription);

		// 10. Match and test descriptors, get nearest
		Mat matchIndex(captureDescription.rows, 2, CV_32SC1);
		Mat matchDistance(captureDescription.rows, 2, CV_32FC1);
		flannIndex.knnSearch(captureDescription,
						     matchIndex,
							 matchDistance,
							 2,
							 flann::SearchParams()); // Call KNN algorithm

		// 11. Select best match by Lowe's algorithm
		vector<DMatch> goodMatches;
		for(int i = 0; i < matchDistance.rows; ++i){
			if(matchDistance.at<float>(i, 0) < 0.6*matchDistance.at<float>(i, 1)){
				DMatch dmatches(i, matchIndex.at<float>(i, 0), matchDistance.at<float>(i, 0));
				goodMatches.push_back(dmatches);
			}
		}

		// 12. Draw and display matches
		Mat resultImage;
		drawMatches(captureImage, captureKeyPoints, srcImage, keyPoints, goodMatches, resultImage);
		imshow("matching", resultImage);

		// 13. Output fps
		cout <<"> fps = " <<getTickFrequency()/(getTickCount() - time0) <<endl;
	}

	return 0;
}



