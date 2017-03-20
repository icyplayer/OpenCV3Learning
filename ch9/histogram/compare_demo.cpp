/*
 * compare_demo.cpp
 *
 *  Created on: 2017年3月20日
 *      Author: icyplayer
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main_compare()
{
	// 1. Declare 3 Mat, base, RGB and HSV
	 Mat srcImage_base, hsvImage_base;
	 Mat srcImage_test1, hsvImage_test1;
	 Mat srcImage_test2, hsvImage_test2;
	 Mat hsvImage_halfDown;

	 // 2. Read in images
	 srcImage_base = imread("image/4-1.jpg", 1);
	 srcImage_test1 = imread("image/4-2.jpg", 1);
	 srcImage_test2 = imread("image/4-3.jpg", 1);
	 // Display
	 imshow("base", srcImage_base);
	 imshow("test 1", srcImage_test1);
	 imshow("test 2", srcImage_test2);

	 // 3. Convert BGR to HSV
	 cvtColor(srcImage_base, hsvImage_base, COLOR_BGR2HSV);
	 cvtColor(srcImage_test1, hsvImage_test1, COLOR_BGR2HSV);
	 cvtColor(srcImage_test2, hsvImage_test2, COLOR_BGR2HSV);

	 // 4. Create hsv image with half base image
	 hsvImage_halfDown = hsvImage_base(Range(hsvImage_base.rows/2, hsvImage_base.rows-1), Range(0, hsvImage_base.cols - 1));

	 // 5. Init params for histogram calculating
	 // hue channel - 50 bins, saturation channel - 32 bins
	 int h_bins = 50; int s_bins = 60;
	 int histSize[] = {h_bins, s_bins};
	 float h_ranges[] = {0, 256};
	 float s_ranges[] = {0, 180};
	 const float* ranges[] = {h_ranges, s_ranges};
	 int channels[] = {0, 1};

	 // 6. Create MatND for histogram
	 MatND baseHist, halfDownHist, testHist1, testHist2;

	 // 7. calculate base, test1, test2, halfDownHist's HSV histogram
	 calcHist(&hsvImage_base, 1, channels, Mat(), baseHist, 2, histSize, ranges, true, false);
	 normalize(baseHist, baseHist, 0, 1, NORM_MINMAX, -1, Mat());

	 calcHist(&hsvImage_halfDown, 1, channels, Mat(), halfDownHist, 2, histSize, ranges, true, false);
	 normalize(halfDownHist, halfDownHist, 0, 1, NORM_MINMAX, -1, Mat());

	 calcHist(&hsvImage_test1, 1, channels, Mat(), testHist1, 2, histSize, ranges, true, false);
	 normalize(testHist1, testHist1, 0, 1, NORM_MINMAX, -1, Mat());

	 calcHist(&hsvImage_test2, 1, channels, Mat(), testHist2, 2, histSize, ranges, true, false);
	 normalize(testHist2, testHist2, 0, 1, NORM_MINMAX, -1, Mat());

	 // 8. Comparison
	 // Method: (1) Correlation; (2) Chi-Square; (3) Intersection; (4) Bhattacharyya
	 for(int i = 0; i < 4; ++i){
		 int compare_method = i;
		 double base_base = compareHist(baseHist, baseHist, compare_method);
		 double base_half = compareHist(baseHist, halfDownHist, compare_method);
		 double base_test1 = compareHist(baseHist, testHist1, compare_method);
		 double base_test2 = compareHist(baseHist, testHist2, compare_method);

		 printf("method[%d] comparison result:\n\n [base - base]:%f, [base - half]:%f, [base - test1]:%f, [base - test2]:%f\n",
				 i, base_base, base_half, base_test1, base_test2);
		 cout <<"----------------------------------------------------------------------------------"
			  <<endl;
	 }

	 printf("Comparison over.\n");
	 waitKey(0);
	 return 0;
}

