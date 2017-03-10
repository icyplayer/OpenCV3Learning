/*
 * dft_demo.cpp
 *
 *  Created on: 2017年3月10日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cstdio>
using namespace cv;
using namespace std;

/**
 * Instruction:
 * copyMakeBorder(srcImage, dstImage, \
 * 				  0, newRows-oldRows, newCols-oldCols, \
 * 				  BORDER_CONSTANT, Scalar::all(0));
 *
 * [x, x, x;
 *  x, x, x;
 *  x, x, x]
 *  =>
 *  [x, x, x, 0;
 *   x, x, x, 0;
 *   x, x, x, 0;
 *   0, 0, 0, 0]
 *
 * dft
 * in-place dft;
 * result is complex number.
 * We need to convert the complex result into magnitude
 * dst(I) = sqrt(Real(DFT(I))^2 + Imaginary(DFT(I))^2)
 *
 * log
 * logarithmic scale
 * magnitude result is too large to display on your screen.
 * Regard the convert in this way: Real coordinate system => logarithmic coordinate system
 *
 * Exchange quadrant
 * TODO
 * why?
 *
 * Normalize
 * To display easily.
 *
 */


int main_dft()
{
	// 1. Read in original image (gray scale)
	Mat srcImage = imread("mogu.jpg", 0);
	if(!srcImage.data){
		printf("read srcImage1 error!\n");
		return false;
	}
	imshow("origin", srcImage);

	// 2.
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);
	Mat padded;
	copyMakeBorder(srcImage, padded, \
				   0, m-srcImage.rows, 0, n-srcImage.cols, \
				   BORDER_CONSTANT, Scalar::all(0));

	// 3.
	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexI;
	merge(planes, 2, complexI);

	// 4. in-place DFT
	dft(complexI, complexI);

	// 5. complex => log(1 + Magnitude)
	// TODO
	// Split: WHY? What will happens to array planes?
	split(complexI, planes); //	planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
	Mat magnitudeImage = planes[0];

	// 6. Logarithmic scale: log(1+M)
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);

	// 7.
	/**
	 * x & -2 Examples:
	 * 4&-2 = 0x4
	 * 5&-2 = 0x4
	 * 6&-2 = 0x6
	 */
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols&-2, magnitudeImage.rows&-2));
		// Spectrum clipping
	int cx = magnitudeImage.cols/2;
	int cy = magnitudeImage.rows/2;
	/**
	 * ROI region:
	 * q0 | q1
	 * -------
	 * q2 | q3
	 */
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));
	// Exchange quadrant
	Mat tmp;
	// q0 <=> q3
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	// q1 <=> q2
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	// 8. Normalize
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

	// 9. Display result
	imshow("result", magnitudeImage);
	waitKey(0);

	return 0;
}









