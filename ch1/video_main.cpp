//============================================================================
// Name        : main.cpp
// Author      : icyplayer
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : OpenCV3编程入门，第一章练习程序
//============================================================================

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

// example from opencv official doc
int main_camera2(int, char**)
{
    Mat frame;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID + apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

// 调用摄像头+边缘检测
int main_camera_canny( )
{
	//【1】从摄像头读入视频
	VideoCapture capture(0);
	Mat edges;
	//【2】循环显示每一帧
	while(1)
	{
		Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
		capture >>frame;  //读取当前帧
		cvtColor(frame, edges, COLOR_BGR2GRAY);

		// Blur
		blur(edges, edges, Size(7,7));

		// Canny
		Canny(edges, edges, 0, 30, 3);

		// display
		imshow("被Canny后视频", edges);  //显示当前帧
		if(waitKey(30) >= 0){
			break;  //延时30ms
		}
	}
	return 0;
}


// failed
int main_play()
{
	VideoCapture capture;
	capture.open("1.avi");
	if(!capture.isOpened()){
		cout <<"Failed to open!" <<endl;
		return -1;
	}

	while(1)
	{
		Mat frame;
		capture >>frame;
		if(frame.empty()){
			break;
		}
		imshow("video reading", frame);
		waitKey(30);
	}

	return 0;
}
