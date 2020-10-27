#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <limits.h>
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "OSDETECT.h"

#define CAM 2
using namespace std;
using namespace cv;

int main()
{
	VideoCapture videocapture;
	Mat src;
	Mat checkBG = Mat(100,150,CV_8UC3,Scalar(255,255,255));
	char OSName[20];
	int16_t count = 0;
	char current_str[100], current_str_win[100];
	string checkWindow = "ChecBox";
#if defined I_OS_MAC
	cout << "WORK ON MAC" << end;
	strcpy(OSName, "MAC");
#elif defined I_OS_ANDROID
	cout << "WORK ON ANDROID" << endl;
	strcpy(OSName, "ANDROID");
#elif defined I_OS_WIN32
	cout << "WORK ON WINDOWS" << endl;
	strcpy(OSName, "WINDOWS");
#elif defined I_OS_CYGWIN
	cout << "WORK ON CYGWIN" << endl;
	strcp(OSName, "CYGWIN");
#elif defined I_OS_SOLARIS
	cout << "WORK ON SOLARIS" << endl;
	strcpy(OSName, "SOLARIS");
#elif defined I_OS_LINUX
	cout << "WORK ON LINUX" << endl;
	strcpy(OSName, "LINUX");
#elif defined I_OS_FREEBSD
	cout << "WORK ON FREEBSD" << endl;
	strcpy(OSName, "FREEBSD");
#elif defined I_OS_OPENBSD
	cout << "WORK ON OPENBSD" << endl;
	strcpy(OSName, "OPENBSD");
#elif defined I_OS_AIX
	cout << "WORK ON AIX" << endl;
	strcpy(OSName, "AIX");
#else
	cout << "unknown os" << endl;
	strcpy(OSName,"UNKNOWN");
#endif
#if CAM == 0
	videocapture.open(0);
#else 
	videocapture.open(CAM);
#endif	
	videocapture.read(src);
	sprintf_s(current_str_win,"GRAB PICTURE WITH CAMERA %d", CAM );

	cv::namedWindow(current_str_win);
    cv::namedWindow(checkWindow);

    const int SRCWIDTH = src.rows, SRCHEIGHT = src.cols;
	cvui::init(checkWindow);

	while (!src.empty())
	{
		if (count > INT16_MAX)
		{
			perror("GRABD PICTURE NUMBER HITS THE CEILING, PLEASE RESTART THE APPLICATION!");
		}
		if (cvui::button(checkBG,  10, 20, "GRAB Image"))
		{
			sprintf(current_str, "%s_PIC_%d.jpg",OSName,count++);
			imwrite(current_str, src);
		}
        if (cvui::button(checkBG,  10, 60, "GRAB Video"))
        {
            sprintf(current_str, "%s_Video_%d.avi",OSName,count++);
            VideoWriter videowriter(current_str,CV_FOURCC('X', 'V', 'I', 'D'),60,Size(640,480));
            {
                videowriter.write(src);
                cv::imshow(current_str_win,src);
                videocapture.read(src);
            }while((waitKey(20) != 27)&&!src.empty())
            break;
        }
		cvui::update();
		imshow(current_str_win, src);
        imshow(checkWindow, checkBG);
		if(waitKey(25)==27)break;
		videocapture.read(src);
	}
	destroyWindow(current_str_win);
    destroyWindow(checkWindow);
	return 0;
}