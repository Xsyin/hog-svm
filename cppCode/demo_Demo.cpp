/*
 * demo_Demo.cpp
 *
 *  Created on: 2016年7月28日
 *      Author: xsyin
 */
#include <iostream>
#include <jni.h>
#include <jni_md.h>
#include "detect.h"
#include "demo_Demo.h"

using namespace std;

JNIEXPORT jdoubleArray JNICALL Java_demo_Demo_get_1hoop_1position
  (JNIEnv *env, jobject thisObj, jint frame_count, jstring strJNI, jstring svmModel){
  	const char *CStr = env -> GetStringUTFChars(strJNI, NULL);
  	const char *CModel = env -> GetStringUTFChars(svmModel, NULL);
  	if(NULL == CStr){
  		cout<<"convert strJNI to C char failed !"<<endl;
  		return NULL;
  	}
  	if(NULL == CModel){
		cout<<"convert string svmModel to C char failed !"<<endl;
		return NULL;
	}
  	string str_path(CStr);
  	string svm_model(CModel);
  	Rect hoop;

  	BYTE state;
  	state = DetectHoopPosition(str_path, frame_count, hoop);

  	jdouble outCArray[] = {(double)state, hoop.x, hoop.y, hoop.width, hoop.height};

  	jdoubleArray outJNIArray = env -> NewDoubleArray(5);
  	if(NULL == outJNIArray){
  		cout<<"allot DoubleArray failed! "<<endl;
  		return NULL;
  	}
  	env->SetDoubleArrayRegion(outJNIArray, 0, 5, outCArray);
  	return outJNIArray;
}




