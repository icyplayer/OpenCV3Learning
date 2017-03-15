/*
 * remapMultiple_demo.cpp
 *
 *  Created on: 2017年3月15日
 *      Author: icyplayer
 */


/*
 * remap_demo.cpp
 *
 *  Created on: 2017年3月15日
 *      Author: icyplayer
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;


#define WINDOW_NAME "remap"


Mat g_srcImage, g_dstImage;
Mat g_map_x, g_map_y;


int update_map(int key);
static void ShowHelpText();


int main()
{
	// Show instructions
	ShowHelpText();

	g_srcImage = imread("img/10.jpg");
	if(!g_srcImage.data){
		printf("read g_srcImage failed.\n");
		return false;
	}
	imshow("origin", g_srcImage);

	// 2. Create images, X/Y remapping
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	g_map_x.create(g_srcImage.size(), CV_32FC1); // CV_(位数）+（数据类型）+（通道数）, C1, one channel
	g_map_y.create(g_srcImage.size(), CV_32FC1);

	namedWindow(WINDOW_NAME, 1);
	imshow(WINDOW_NAME, g_srcImage); // why?


	while(1){
		int key = waitKey(0);
		if((key & 255) == 27 || (char)key == 'q'){ // or key & 255 instead of (char)key
			cout <<"Exit.\n";
			break;
		}

		update_map(key);
		remap(g_srcImage, g_dstImage, g_map_x, g_map_y,
			  INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
		imshow(WINDOW_NAME, g_dstImage);
	}

	return 0;
}


int update_map(int key)
{
	for(int j = 0; j < g_srcImage.rows; ++j){
		for(int i = 0; i < g_srcImage.cols; ++i){
			switch(key){
			case '1':
				if(i > g_srcImage.cols*0.25 && i < g_srcImage.cols*0.75
				   && j > g_srcImage.rows*0.25 && j < g_srcImage.rows*0.75){
					g_map_x.at<float>(j,i) = static_cast<float>(2*(i - g_srcImage.cols*0.25) + 0.5);
					g_map_y.at<float>(j,i) = static_cast<float>(2*(j - g_srcImage.rows*0.25) + 0.5);
				}
				else{
					g_map_x.at<float>(j,i) = 0;
					g_map_y.at<float>(j,i) = 0;
				}
				break;
			case '2':
				g_map_x.at<float>(j,i) = static_cast<float>(i);
				g_map_y.at<float>(j,i) = static_cast<float>(g_srcImage.rows - j);
				break;
			case '3':
				g_map_x.at<float>(j,i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j,i) = static_cast<float>(j);
				break;
			case '4':
				g_map_x.at<float>(j,i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j,i) = static_cast<float>(g_srcImage.rows - j);
				break;
			default:
				break;

			}
		}
	}

	return 1;
}


static void ShowHelpText()
{
	cout <<"\n\n\t\t\tOpenCV ver:"
		 <<CV_VERSION;
	cout <<"\n\n  ----------------------------------------------------------------------------\n";
	cout <<"\n\tHelp: \n\n"
		 <<"\t\t<ESC>/<q>- Exist program\n"
		 <<"\t\t<1> - (x, y) => scaling\n"
		 <<"\t\t<2> - (x, y) => (row-x, y)\n"
		 <<"\t\t<3> - (x, y) => (x, col-y)\n"
		 <<"\t\t<4> - (x, y) => (row-x, col-y)"
		 <<endl;
}
