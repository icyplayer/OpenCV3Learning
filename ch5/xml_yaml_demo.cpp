/*
 * xml_yaml_demo.cpp
 *
 *  Created on: 2017年3月10日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>

using namespace cv;
using namespace std;

// XML and YAML: write back
int main_write()
{
	// Init
	FileStorage fs("test.yaml", FileStorage::WRITE);

	// File write in
	fs <<"frameCount" <<5;
	time_t rawTime;
	time(&rawTime);
	fs <<"calibrationDate" <<asctime(localtime(&rawTime));

	Mat cameraMatrix = (Mat_<double>(3,3) <<1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	Mat distCoeffs = (Mat_<double>(5,1) <<0.1, 0.01, -0.001, 0, 0);

	fs <<"cameraMatrix" <<cameraMatrix <<"disCoeffs" <<distCoeffs;

	fs <<"features" <<"[";
	for(int i = 0; i < 3; ++i){
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 260;

		fs <<"{:" <<"x" <<x <<"y" <<y <<"lbp" <<"[:";
		for(int j = 0; j < 8; ++j){
			fs <<((lbp >>j) & 1);
		}
		fs <<"]" <<"}";
	}
	fs <<"]";
	fs.release();

	printf("File io finished. Check the generated file under ~/\n");
	getchar();

	return 0;
}


// XML and YAML: read in
int main()
{
#ifdef WINDOWS
	system("color 6F");
#endif

	// Init
	FileStorage fs2("test.yaml", FileStorage::READ);

	// Method 1: FileNode operation
	int frameCount = (int)fs2["frameCount"];

	std::string date;
	// Method 2: FileNode Operator >>
	fs2["calibrationDate"] >>date;

	Mat cameraMatrix2, distCoeffs2;

	fs2["cameraMatrix"] >>cameraMatrix2;
	fs2["disCoeffs"] >>distCoeffs2;
	cout <<"frameCount: " <<frameCount <<endl
		 <<"calibration date: " <<date <<endl
		 <<"camera matrix: " <<cameraMatrix2 <<endl
		 <<"distortion coeffs: " <<distCoeffs2 <<endl;

	FileNode features = fs2["features"];
	FileNodeIterator it = features.begin(), it_end = features.end();
	int idx = 0;
	vector<uchar> lbpVals;
	// Iterate with FileNodeIterator
	for(; it < it_end; ++it, ++idx){
		cout <<"feature #" <<idx <<": ";
		cout <<"x=" <<(int)(*it)["x"] <<", y=" <<(int)(*it)["y"] <<", lbp: (";
		(*it)["lbp"] >>lbpVals;
		for(int i = 0; i < (int)lbpVals.size(); ++i){
			cout <<" " <<(int)lbpVals[i];
		}
		cout <<")" <<endl;
	}
	fs2.release(); // Closes the file and releases all the memory buffers.

	printf("File io finished. Check the generated file under ~/\n");
	getchar();

	return 0;
}

