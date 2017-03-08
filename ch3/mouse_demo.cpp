/*
 * mouse_demo.cpp
 *
 *  Created on: 2017年3月8日
 *      Author: icyplayer
 */

#include <opencv2/opencv.hpp>

using namespace cv;
#define WINDOW_NAME "mouse click demo"

void on_MouseHandle(int event, int x, int y, int flags, void *param);
void DrawRectangle(Mat& img, Rect box);
//void ShowHelpText();

Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(12345); // wtf?


int main(int argc, char** argv)
{
	// Variables setting
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);

	srcImage = Scalar::all(0); // wtf?

	// Callback setting
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void *)&srcImage);

	// Draw when flag g_bDrawingBox == true
	while(1){
		srcImage.copyTo(tempImage);
		if(g_bDrawingBox){
			DrawRectangle(tempImage, g_rectangle);
		}
		imshow(WINDOW_NAME, tempImage);
		if(waitKey(10) == 27){ // Exists while press ESC
			break;
		}
	}

	return 0;
}


// Callback for mouse
void on_MouseHandle(int event, int x, int y, int flags, void *param)
{
	Mat &image = *(Mat *)param;

	switch(event){
	case EVENT_MOUSEMOVE:
		if(g_bDrawingBox){
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
		break;
	case EVENT_LBUTTONDOWN:
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0); // Start point
		break;
	case EVENT_LBUTTONUP:
		g_bDrawingBox = false;
		// width/height < 0 handle
		// 自右下至左上的绘制
		if(g_rectangle.width < 0){
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}
		if(g_rectangle.height < 0){
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		DrawRectangle(image, g_rectangle);
		break;
	default:
		break;
	}
}


void DrawRectangle(Mat& img, Rect box)
{
	// Color will continue changing WHILE drawing one single
	// rectangle, which is unnecessary.
	rectangle(img, box.tl(), box.br(),
			  Scalar(g_rng.uniform(0, 255),
					 g_rng.uniform(0, 255),
					 g_rng.uniform(0, 255))); // Random color
}

