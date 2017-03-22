readme.md
======================

```
 Created on: 2017年3月21日
     Author: ipr
```

## Requirement
OpenCV version: 2.4.13     

## bugs
./flann/flann_surf_demo.cpp cannot work.


## OpenCV 2.4.13 reinstall notes
- reinstalled
- $ brew install opencv --with-ffmpeg --with-gstreamer  --with-tbb  --with-vtk   --with-opengl
-  FAILED
- $ brew install opencv --with-ffmpeg --with-gstreamer  --with-vtk
- FAILED
- $ brew install opencv
- SUCCESS
- (some libs was missing in previous installation