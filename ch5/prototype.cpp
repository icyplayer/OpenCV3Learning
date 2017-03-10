/*
 * prototype.cpp
 *
 *  Created on: 2017年3月9日
 *      Author: icyplayer
 */


#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//
//int divideWith = 10;
//uchar table[256];
//for(int i = 0; i < 256; ++i){
//	table[i] = divideWith * (i/divideWith);
//}
//
//Mat lookUpTable(1, 256, CV_8U);
//uchar *p = lookUpTable.data;
//for(int i = 0; i < times; ++i){
//	LUT(I,lookUpTable, J);
//}
//
//double time0 = static_cast<double>(getTickCount());
//time0 = ((double)getTickCount() - time0) / getTickFrequency();
//cout <<"runtime cost: " <<time0 <<"sec" <<endl;
//
//
//for (int y = 0; y < image.rows; ++y){
//	for(int x = 0; x < image.cols; ++x){
//		for(int c = 0; c < 3; ++c){
//			new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01) * (image.at<Vec3b>(y, x)[c]) + g_nBrightValue);
//		}
//	}
//}
////
