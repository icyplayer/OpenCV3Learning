/*
 * hs_demo.cpp
 *
 *  Created on: 2017年3月20日
 *      Author: icyplayer
 */


// Hue-Saturation histogram

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_hsv()
{
	// 1. Read in image
	Mat srcImage, hsvImage;
	srcImage = imread("image/1.jpg", 1);
	if(!srcImage.data){
		printf("read srcImage failed.\n");
		return false;
	}
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);

	int hueBinNum = 30;
	int saturationBinNum = 32;
	int histSize[] = {hueBinNum, saturationBinNum};
	float hueRanges[] = {0, 180}; // [0, 180)
	float saturationRanges[] = {0, 256};
	const float* ranges[] = {hueRanges, saturationRanges};
	MatND dstHist;
	int channels[] = {0, 1};

	// 3. Calculate histogram
	calcHist(&hsvImage, 1, channels, Mat(), dstHist, 2, histSize, ranges, true, false);

	// 4. Setting for drawing histogram
	double maxValue = 0;
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);
	int scale = 10;
	Mat histImg = Mat::zeros(saturationBinNum*scale, hueBinNum*10, CV_8UC3);
	// 5. Draw histogram
	for(int hue = 0; hue < hueBinNum; hue++){
		for(int saturation = 0; saturation < saturationBinNum; saturation++){
			float binValue = dstHist.at<float>(hue, saturation);
			int intensity = cvRound(binValue*255/maxValue);
			rectangle(histImg,
					  Point(hue*scale, saturation*scale),
					  Point((hue+1)*scale - 1, (saturation + 1)*scale-1),
					  Scalar::all(intensity),
					  FILLED);
		}
	}

	// 6. Display original and result image
	imshow("origin", srcImage);
	imshow("result", histImg);
	waitKey(0);

	return 0;
}

