// Panel.h
#pragma once
#pragma comment(lib,"user32.lib")
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Panel
{
public:
	Panel();
	~Panel();
	void DetectColor(string imgPath);
	string ColorName(Vec3b HSV);
	void ColorAtPoint(Point point);
private:
	Panel *pPanel;
	void FixPath(string& path);
	bool win0;
	Mat m_Image;
	const char* m_WindowName = "My Image";
};