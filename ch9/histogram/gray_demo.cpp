/*
 * gray_demo.cpp
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

int main_gray()
{
	// 1. Read in image
	Mat srcImage;
	srcImage = imread("image/2.jpg", 0); // gray
	if(!srcImage.data){
		printf("read srcImage failed.\n");
		return false;
	}
	imshow("origin", srcImage);

	// 2. Define variables
	MatND dstHist;
	int dims = 1; // 需要统计的特征数目
	float hranges[] = {0, 255};
	const float* ranges[] = {hranges};
	int size = 256;
	int channels = 0;

	// 3. Calculate histogram
	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	int scale = 1;
	Mat dstImage(size*scale, size, CV_8U, Scalar(0));

	// 4. Get maximum and minimum values
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	// 5. Draw histogram
	int hpt = saturate_cast<int>(0.9 * size);
	for(int i = 0; i < 256; ++i){
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue * hpt/maxValue);
		rectangle(dstImage, Point(i*scale, size-1), Point((i+1)*scale-1, size-realValue), Scalar(255));
	}

	// 6. Display original and result image
	imshow("result", dstImage);
	waitKey(0);

	return 0;
}

