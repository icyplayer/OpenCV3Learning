/*
 * pixel_demo.cpp
 *
 *  Created on: 2017年3月9日
 *      Author: icyplayer
 */


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void colorReduce(Mat &inputImage, Mat &outputImage, int div);

int pixel_access()
{
	// 1. Create and display image
	Mat srcImage = imread("1.jpg");
	imshow("origin", srcImage);

	// 2. Create resulting image based on original image
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

	// 3. Clock starting time
	double time0 = static_cast<double>(getTickCount());

	// 4. Call color reduce function
	colorReduce(srcImage, dstImage, 32);

	// 5. Calculate runtime and output the result
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout <<"runtime: " <<time0 <<"sec" <<endl;

	imshow("result", dstImage);
	waitKey(0);
}


// Method 1: C lang []
void colorReduce1(Mat &inputImage, Mat &outputImage, int div)
{
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols * outputImage.channels();
	for(int i = 0; i < rowNumber; ++i){
		uchar *data = outputImage.ptr<uchar>(i);
		for(int j = 0; j < colNumber; ++j){
			data[j] = (data[j] / div) * div + div/2;
		}
	}
}


// Method 2: iterator fetching
void colorReduce2(Mat &inputImage, Mat &outputImage, int div)
{
	// var init
	outputImage = inputImage.clone();
	// get iterator
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();

	for(; it != itend; ++it){
		(*it)[0] = ((*it)[0]/div)*div + div/2;
		(*it)[1] = ((*it)[1]/div)*div + div/2;
		(*it)[2] = ((*it)[2]/div)*div + div/2;
	}
}

// Method 3: Dynamic calculating
void colorReduce(Mat &inputImage, Mat &outputImage, int div)
{
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;

	for(int i = 0; i < rowNumber; ++i){
		for(int j = 0; j < colNumber; ++j){
			outputImage.at<Vec3b>(i, j)[0] = (outputImage.at<Vec3b>(i, j)[0]/div)*div + div/2;
			outputImage.at<Vec3b>(i, j)[1] = (outputImage.at<Vec3b>(i, j)[1]/div)*div + div/2;
			outputImage.at<Vec3b>(i, j)[2] = (outputImage.at<Vec3b>(i, j)[2]/div)*div + div/2;
		}
	}
}


// TODO
// 示例【24】，回去后仔细阅读（晚间任务）

