#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <cmath>
#include <limits.h>
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "OSDETECT.h"

#define CAM 0
using namespace std;
using namespace cv;

int main()
{
	VideoCapture videocapture;
	Mat src;
	char OSName[20];
	int16_t count = 0;
	char current_str[100], current_str_win[100];
#if defined I_OS_MAC
	cout << "WORK ON MAC" << end;
	strcpy_s(OSName, "MAC");
#elif defined I_OS_ANDROID
	cout << "WORK ON ANDROID" << endl;
	strcpy_s(OSName, "ANDROID");
#elif defined I_OS_WIN32
	cout << "WORK ON WINDOWS" << endl;
	strcpy_s(OSName, "WINDOWS");
#elif defined I_OS_CYGWIN
	cout << "WORK ON CYGWIN" << endl;
	strcpy_s(OSName, "CYGWIN");
#elif defined I_OS_SOLARIS
	cout << "WORK ON SOLARIS" << endl;
	strcpy_s(OSName, "SOLARIS");
#elif defined I_OS_LINUX
	cout << "WORK ON LINUX" << endl;
	strcpy_s(OSName, "LINUX");
#elif defined I_OS_FREEBSD
	cout << "WORK ON FREEBSD" << endl;
	strcpy_s(OSName, "FREEBSD");
#elif defined I_OS_OPENBSD
	cout << "WORK ON OPENBSD" << endl;
	strcpy_s(OSName, "OPENBSD");
#elif defined I_OS_AIX
	cout << "WORK ON AIX" << endl;
	strcpy_s(OSName, "AIX");
#else
	cout << "unknown os" << endl;
	strcpy_s(OSName,"UNKNOWN");
#endif
#if CAM==0
	videocapture.open(0);
#else 
	videocapture.open(2);
#endif	
	videocapture.read(src);
	sprintf_s(current_str_win,"GRAB PICTURE WITH CAMERA %d", CAM );
	cv::namedWindow(current_str_win);
	const int SRCWIDTH = src.rows, SRCHEIGHT = src.cols;
	cvui::init(current_str_win);
	//cvui::window(src, SRCWIDTH-100, SRCWIDTH-100, 100, 100, "Setting");
	while (!src.empty())
	{
		if (++count > INT16_MAX)
		{
			perror("GRABD PICTURE NUMBER HITS THE CEILING, PLEASE RESTART THE APPLICATION!");
		}
		if (cvui::button(src,  (SRCWIDTH - 200), (SRCHEIGHT - 200), "GRAB"))
		{
			sprintf_s(current_str, "%s_PIC_%d.jpg",OSName,count);
			imwrite(current_str, src);
		}
		cvui::update();
		imshow(current_str_win, src);
		if(waitKey(25)==27)break;
		videocapture.read(src);
	}
	destroyWindow(current_str_win);
	return 0;
}