/*
 * detect.h
 *
 *  Created on: 2016年7月29日
 *      Author: xsyin
 */

#ifndef CPPCODE_DETECT_H_
#define CPPCODE_DETECT_H_

#include <iostream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>

//define weight vector length, i.e. (size of hog descriptor) + 1
#define VECTOR_LENGTH   1765
//the gap between two frames
#define FRAME_STEP      5
//the start position of a video
#define FRAME_START_POS 0
//Value to specify how much the image size is reduced at each image scale.
#define DETECT_SCALE    1.05
typedef unsigned char BYTE;

using namespace std;
using namespace cv;

BYTE DetectHoopPosition(string, int, Rect&, string model="wsv.dat");
bool getWeightVector(Mat&, string);
void nonMaximumSuppression(const vector<Rect>&, vector<Rect>&, float);
bool findHoop(vector<Rect>&, vector<Rect>&, int, Rect&);

#endif /* CPPCODE_DETECT_H_ */
