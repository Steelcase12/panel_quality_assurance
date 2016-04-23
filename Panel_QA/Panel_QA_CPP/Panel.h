// Panel.h
#pragma once
#pragma comment(lib,"user32.lib")
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

class Panel
{
public:
	Panel();
	~Panel();
	bool ShowImage(string imgPath, string windowTitle, bool showImg = true);
	bool ShowImageWithCalibration(string imgPath, string windowTitle, Mat calibratedImg, bool showImg = true);
	string ColorName(Vec3b HSV);
	void ColorAtPoint(Point point);
	void PointLocation(Point point);
	void MaskWithColor(string imgPath, string color);
	void DetectEdges(string imgPath);
	void DrawOnBoard(string imgPath);
	void Perspective(string imgPath, string selectedItem);
	void Rectification(string imgPath, string selectedItem);
	void CalibrateCamera(string filePath);
	void CalibrateCameraNoOutput(string filePath);
	void CalibrateCameraFisheyeNoOutput(string filePath);
	void CascadeClassify(string imgPath, string classPath);
	void BatchCalibrate(string dirPath);	
	void DetectFeatures(string scenePath, string objPath, bool exceedsBorder, bool outerEdges);
private:
	Panel *m_pPanel;
	Mat m_Image;
	// This is just for testing distance measurement
	vector<Point2f> corners;
	Mat CannyDetection(Mat image, bool showImg = true);
	void FindContours(Mat image);
	void DetectBlob(Mat image);
	const char* m_WindowName = "My Image";
};