/*
 * imshow_demo.cpp
 *
 *  Created on: 2017年3月7日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

void createAlphaMat(Mat &mat)
{
//	CV_Assert(mat.channels() == 4);
	for(int i = 0; i < mat.rows; ++i){
		for(int j = 0; j < mat.cols; ++j){
			Vec4b &bgra = mat.at<Vec4b>(i, j);
			bgra[0] = UCHAR_MAX; // Blue
			bgra[1] = saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX); // Green
			bgra[2] = saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX); // Red
			bgra[3] = saturate_cast<uchar>(0.5 * (bgra[1] + bgra[2])); // Alpha
		}
	}
}

// to test, main_imwrite-> main
int main_imwrite()
{
	// Create Mat with alpha channel
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	vector<int> compression_params;
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);	// ?
	compression_params.push_back(9);	// ?
	try{
		imwrite("alpha.png", mat, compression_params);
		imshow("alpha.png generated", mat);
		fprintf(stdout, "alpha.png saved under ~/");
		waitKey(0);
	}
	catch(runtime_error &ex){
		fprintf(stderr, "png converting encounter error: %s\n", ex.what());
		return 1;
	}

	return 0;
}
