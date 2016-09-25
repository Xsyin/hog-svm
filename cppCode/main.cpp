/*
 * main.cpp
 *
 *  Created on: 2016年7月29日
 *      Author: xsyin
 */
#include <iostream>
#include "detect.h"

int main()
{
	Rect hoop;
	DetectHoopPosition("/home/xsyin/videos/02.mov", 10, hoop);
	cout<<hoop<<endl;
}



