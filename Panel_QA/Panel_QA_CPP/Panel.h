// Panel.h
#pragma once
#pragma comment(lib,"user32.lib")
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class Panel
{
public:
	Panel();
	~Panel();
	bool ShowImage(string imgPath, string windowTitle);
	string ColorName(Vec3b HSV);
	void ColorAtPoint(Point point);
	void MaskWithColor(string imgPath, string color);
	void DetectEdges(string imgPath);
	void CalibrateCamera(string filePath);
private:
	Panel *m_pPanel;
	void FixPath(string& path);
	Mat CannyDetection();
	Mat m_Image;
	const char* m_WindowName = "My Image";
};