/*
 * channel_demo.cpp
 *
 *  Created on: 2017年3月9日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool MultiChannelBlending();

int main()
{
#ifdef WINDOWS
	system("color 9F");
#endif

	if(MultiChannelBlending()){
		cout <<endl <<"split then merge success!" <<endl;
	}

	// XD
	// after split/merge, refer to cv::mixChannels
	waitKey(0);
	return 0;
}


bool MultiChannelBlending()
{
	vector<Mat> channels;
	Mat imageBlueChannel;
	Mat imageGreenChannel;
	Mat imageRedChannel;

	Mat srcImage;

	srcImage = imread("dota_pa.jpg", 1);
	Mat logoImage = imread("dota_logo.jpg", 0);
	if(!srcImage.data){
		printf("read srcImage failed.\n");
		return false;
	}
	if(!logoImage.data){
		printf("read logoImage failed.\n");
		return false;
	}



	// 1. Blue channel blending
	split(srcImage, channels);
	imageBlueChannel = channels.at(0); // return a reference
	addWeighted(imageBlueChannel(Rect(250, 250, logoImage.cols, logoImage.rows)),
				1.0,
				logoImage,
				0.5,
				0.0,
				imageBlueChannel(Rect(250, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);
	namedWindow("1 - blue channle");
	imshow("1 - blue channle", srcImage);

	// 2. Green channel blending
	srcImage = imread("dota_pa.jpg", 1);
	if(!srcImage.data){
		printf("read srcImage failed.\n");
		return false;
	}
	split(srcImage, channels);
	imageGreenChannel = channels.at(1);
	addWeighted(imageGreenChannel(Rect(250, 250, logoImage.cols, logoImage.rows)),
				1.0,
				logoImage,
				0.5,
				0.0,
				imageGreenChannel(Rect(250, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);
	namedWindow("2 - green channle");
	imshow("2 - green channle", srcImage);


	// 3. Red channel blending
	srcImage = imread("dota_pa.jpg", 1);
	if(!srcImage.data){
		printf("read srcImage failed.\n");
		return false;
	}
	split(srcImage, channels);
	imageRedChannel = channels.at(2);
	addWeighted(imageRedChannel(Rect(250, 250, logoImage.cols, logoImage.rows)),
				1.0,
				logoImage,
				0.5,
				0.0,
				imageRedChannel(Rect(250, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);
	// namedWindow and imshow's input string is for different use
	namedWindow("3 - red channle");
	imshow("3 - red channle", srcImage);

	return true;
}


