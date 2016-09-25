/*
 * detect.cpp
 *
 *  Created on: 2016年7月29日
 *      Author: xsyin
 */
#include <iostream>
#include<fstream>
#include "detect.h"

using namespace std;
using namespace cv;

/**
 *  get weight vector from data file
 *  @param cv::Mat vector matrix
 *  @param std::string data file path
 *
 *  @return state of get
 */
bool getWeightVector(Mat& mat, string model)
{
    ifstream fs(model.data());
    if (!fs.is_open())
        return false;
    float wsv[VECTOR_LENGTH];
    int i=0;
    while(!fs.eof())
    {
        fs>>wsv[i];
        i++;
    }
    fs.close();

    mat = Mat(VECTOR_LENGTH, 1, CV_32F, wsv).clone();
    return true;
}

/**
 *  Detect hoop position in the video
 *  @param video path
 *  @param frame number
 *  @param hoop region
 *
 *  @return state of detect
 */
BYTE DetectHoopPosition(string video, int frameNum, cv::Rect& hoop, string model)
{
    //用来标记是否存在检测结果以及结果够不够好
    //  1           表示模型数据文件错误
    //  2           表示视频文件载入错误
    //  4           表示没有检测到
    //  8           表示检测到了但是效果不好
    //  24 =16+8    表示检测到了，而且效果不错
    BYTE state = 0;

    Mat weightVector ;
    if (!getWeightVector(weightVector, model))
    {
        cout<<"vector file error!!"<<endl;
        state |= 1;
        return state;
    }

    VideoCapture capture;
    capture.open(video);
    if(!capture.isOpened())
    {
        cout<<"read video failed"<<endl;
        state |= 2;
        return state;
    }
    vector<Rect> allRects;
    int frameCount = capture.get(CV_CAP_PROP_FRAME_COUNT);
    int pos = FRAME_START_POS;
    capture.set(CV_CAP_PROP_POS_FRAMES, pos);
    for (int i=0; i < frameNum ; i++)
    {
        Mat frame;
        capture>>frame;
        // 1. 定义HOG对象
        HOGDescriptor hog(Size(40, 40), Size(10, 10), Size(5, 5), Size(5, 5), 9);

        // 2. 设置SVM分类器
        hog.setSVMDetector(weightVector);   // 采用已经训练好的行人检测分类器

        // 3. 在测试图像上检测行人区域
        vector<Rect> regions;
        hog.detectMultiScale(frame, regions, 0, Size(5,5), Size(0,0), DETECT_SCALE);
        allRects.insert(allRects.end(), regions.begin(), regions.end());
        if (pos < frameCount - FRAME_STEP)
            pos += FRAME_STEP;
        else
            break;
    }
    capture.release();
//    cout<<"======all Rects===="<<endl;
//    for (int i=0; i<allRects.size() ;i++ )
//            cout<<allRects[i]<<endl;
    if (allRects.empty())
        return (state | 4);
    else
        state |= 8;

// 处理所有得到的识别框
    vector<Rect> nmsRects;
    nonMaximumSuppression(allRects, nmsRects, 0.3f);
//    cout<<"=====after nms Rects====="<<endl;
//    for (int i=0; i<nmsRects.size() ;i++ )
//            cout<<nmsRects[i]<<endl;

    if (findHoop(allRects, nmsRects, frameNum, hoop))
        state |= 16;
//    cout<<"=======final hoop pos======="<<endl;
//    cout<<hoop<<endl;

    return state;
}


