config notes
=============

## Environment
mac eclipse neon2 with cdt

## Create a new project
new->C++ Project->excutable->empty(with MacOS GCC)

## compiler & linker setting
1. select project, right click and select "Properties"->C/C++ Build->Settings
2. Tool Settings
	- GCC C++ Compiler->Includes: Include paths(-l) add ***/usr/local/opt/opencv3/include/***
	(see brew install opencv3's log)
	***NOTE: '/' on the last should NOT miss***
	- MacOS X C++Linker->Library: Library search path(-L) add ***/usr/local/opt/opencv3/lib/***
	- MacOS X C++Linker->Library: Libraries(-l) add ***opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui***
	***NOTE: opencv_ml may be required somtimes***
	
	
## video
add ***opencv_videoio*** in ***MacOS X C++Linker->Library: Libraries(-l)***
