/*
 * dft_demo.hpp
 *
 *  Created on: 2017年3月10日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 1.
int getOptimalDFTSize(int vecsize);

// 2.
void copyMakeBorder(InputArray src, OutputArray dst, \
	int top, int bottom, int left, int left, int right,
	int borderType, const Scalar& value=Scalar());

// 3. dst(I) = sqrt(x(I)^2 + y(I)^2)
void magnitude(InputArray x, InputArray y, OutputArray magnitude);

// 4. log: Calculates the natural logarithm of every array element.
void log(InputArray src, OutputArray dst);

// 5. Normalization
void normalize(InputArray src, OutputArray dst,
			   double alpha = 1, double beta = 0.0,
			   int norm_type = NORM_L2, int dtype = -1,
			   InputArray mask = noArray());


