/*
 * dft_demo.cpp
 *
 *  Created on: 2017年3月10日
 *      Author: icyplayer
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*
void convolveDFT(InputArray A, InputArray B, OutputArray C)
{
	// 1. Innitialize output matrix
	C.create(abs(A.rows - B.rows)+1, abs(A.cols - B.cols)+1, A.type());
	Size dftSize;

	// 2. Calculate DFT convert size
	dftSize.width = getOptimalDFTSize(int(A.cols + B.cols - 1));// Return the best size for FFT
	dftSize.height = getOptimalDFTSize(int(A.rows + B.rows - 1)); // Mat.rows/Mat.cols is const int

	// 3. Allocate temporary buffer and set zero
	Mat tempA(dftSize, A.type(), Scalar::all(0));
	Mat tempB(dftSize, B.type(), Scalar::all(0));

	// 4. Copy A/B to tempA/tempB's upper left
	Mat roiA(tempA, Rect(0, 0, A.cols, A.rows));
	A.copyTo(roiA);// Why copy?
	Mat roiB(tempB, Rect(0, 0, B.cols, B.rows));
	B.copyTo(roiB);

	// 5. Fast Fourier Transform（FFT）
	dft(tempA, tempA, 0, int(A.rows));
	dft(tempB, tempB, 0, int(B.rows));

	// 6. Multiply the spectrums;
    // core.hpp: the function handles packed spectrum representations well
	mulSpectrums(tempA, tempB, tempA, DFT_COMPLEX_OUTPUT);// complex or real(which shoult it be?)

    // 7. Transform the product back from the frequency domain.
    // Even though all the result rows will be non-zero,
    // you need only the first C.rows of them, and thus you
    // pass nonzeroRows == C.rows
	dft(tempA, tempA, int(DFT_INVERSE + DFT_SCALE), int(C.rows));

	// 8. Copy result to C
	tempA(Rect(0, 0, C.cols, C.rows)).copyTo(C);
}



*/
