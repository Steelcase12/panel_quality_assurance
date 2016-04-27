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
	void MeasureDimensions(string imgPath);
	bool ShowImage(string imgPath, string windowTitle, bool showImg = true);
	bool ShowImageWithCalibration(string imgPath, string windowTitle, Mat calibratedImg, bool showImg = true);
	string ColorName(Vec3b HSV);
	void ColorAtPoint(Point point);
	void PointLocation(Point point);
	void MaskWithColor(string imgPath, string color);
	void DetectEdges(string imgPath);
	void PixelsToLength(string imgPath);
	void CalibrateCamera(string filePath);
	void CalibrateCameraNoOutput(string filePath);
	void LoadCalibration(string filePath);
	void CascadeClassify(string imgPath, string classPath);
	void BatchCalibrate(string dirPath);	
	void DetectFeatures(string scenePath, string objPath, bool exceedsBorder);
	void ReadSettings(string sFilePath);
private:
	Panel *m_pPanel;
	Rect m_roi;
	Mat m_Image;
	Mat m_Homography;
	Mat m_Transmtx;
	int m_low = 105, m_high = 255;
	int m_sigmaX = 10, m_sigmaY = 2;
	int m_cannyLow = 85, m_ratio = 3, m_aperture = 3;
	int m_houghLength = 155;

	// Calibration and Conversion
	int m_boardWidth = 6;
	int m_boardLength = 9;
	double m_cmPerPixel;
	double m_squareSize = 12.1;
	vector<Point2f> corners;

	Mat CannyDetection(Mat image, bool showImg = true);
	void FindContours(Mat image);
	void DetectBlob(Mat image);
	const char* m_WindowName = "My Image";
};