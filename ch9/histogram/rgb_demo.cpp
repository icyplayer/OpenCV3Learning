/*
 * rgb_demo.cpp
 *
 *  Created on: 2017年3月20日
 *      Author: icyplayer
 */


// Hue-Saturation histogram

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_rgb()
{
	// 1. Read in image
	Mat srcImage;
	srcImage = imread("image/3.jpg"); // gray
	if(!srcImage.data){
		printf("read srcImage failed.\n");
		return false;
	}
	imshow("origin", srcImage);

	// 2. Define variables
	int bins = 256;
	int hist_size[] = {bins};
	float range[] = {0, 255};
	const float* ranges[] = {range};
	MatND redHist, greenHist, blueHist;

	// 3. Calculate histogram - Red
	int channels_r[] = {0};
	calcHist(&srcImage, 1, channels_r, Mat(), // No mask
			 redHist, 1, hist_size, ranges, true, // Uniformed
			 false);

	// 4. Calculate histogram - Green
	int channels_g[] = {1};
	calcHist(&srcImage, 1, channels_g, Mat(), greenHist, 1, hist_size, ranges, true, false);

	// 5. Calculate histogram - Blue
	int channels_b[] = {2};
	calcHist(&srcImage, 1, channels_b, Mat(), blueHist, 1, hist_size, ranges, true, false);

	// 6. Get maximum and minimum values
	double maxValue_red, maxValue_green, maxValue_blue;
	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
	minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
	int scale = 1;
	int histHeight = 256;
	Mat histImage = Mat::zeros(histHeight, bins*3, CV_8UC3);

	// 7. Draw histogram
	for(int i = 0; i < bins; ++i){
		float binValue_red = redHist.at<float>(i);
		float binValue_green = greenHist.at<float>(i);
		float binValue_blue = blueHist.at<float>(i);

		int intensity_red = cvRound(binValue_red*histHeight/maxValue_red); // Height to be drawn
		int intensity_green = cvRound(binValue_green*histHeight/maxValue_green);
		int intensity_blue = cvRound(binValue_blue*histHeight/maxValue_blue);

		// Draw red dim's histogram
		rectangle(histImage,
				  Point(i*scale, histHeight - 1),
				  Point((i+1)*scale - 1, histHeight - intensity_red),
				  Scalar(255, 0, 0));
		// Draw green dim's histogram
		rectangle(histImage,
				  Point((i+bins)*scale, histHeight - 1),
				  Point((i+bins+1)*scale - 1, histHeight - intensity_green),
				  Scalar(0, 255, 0));
		// Draw blue dim's histogram
		rectangle(histImage,
				  Point((i+bins*2)*scale, histHeight - 1),
				  Point((i+bins*2+1)*scale - 1, histHeight - intensity_blue),
				  Scalar(0, 0, 255));
	}

	// 8. Display original and result image
	imshow("RGB result", histImage);
	waitKey(0);

	return 0;
}

