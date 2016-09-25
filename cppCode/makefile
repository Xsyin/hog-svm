CLASS_PATH = ../bin

vpath %.class $(CLASS_PATH)/demo


SvmDetect.so:demo_Demo.cpp demo_Demo.h detect.h \
detect.cpp findHoop.cpp nms.cpp
	g++ -shared -fPIC \
	demo_Demo.cpp demo_Demo.h detect.h detect.cpp findHoop.cpp nms.cpp \
	-o libSvmDetect.so `pkg-config --cflags --libs opencv`

### if you haven't install pkg-config 
#SvmDetect.so:demo_Demo.cpp demo_Demo.h detect.h detect.cpp
#	g++ -shared -fPIC \
#	demo_Demo.cpp demo_Demo.h detect.h detect.cpp \
#	-o libSvmDetect.so \
#	-I/usr/local/include/opencv 
#	-I/usr/local/include \
#	-L/usr/local/lib -lopencv_calib3d \
#	-lopencv_contrib -lopencv_core \
#	-lopencv_features2d -lopencv_flann -lopencv_gpu \
#	-lopencv_highgui -lopencv_imgproc -lopencv_legacy \
#	-lopencv_ml -lopencv_nonfree -lopencv_objdetect \
#	-lopencv_ocl -lopencv_photo -lopencv_stitching \
#	-lopencv_superres -lopencv_ts -lopencv_video \
#	-lopencv_videostab -lrt -lpthread -lm -ldl


demo_Demo.h:Demo.class
	javah -classpath $(CLASS_PATH) demo.Demo

clean:
	rm *.so demo_Demo.h