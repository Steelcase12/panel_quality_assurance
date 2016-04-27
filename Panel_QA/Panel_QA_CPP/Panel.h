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
	void DetectEdges(string imgPath, bool debug);
	void PixelsToLength(string imgPath);
	void CalibrateCamera(string filePath);
	void CalibrateCameraNoOutput(string filePath);
	void LoadCalibration(string filePath);
	void CascadeClassify(string imgPath, string classPath);
	void BatchCalibrate(string dirPath);	
	void DetectFeatures(string scenePath, string objPath, bool exceedsBorder, bool featureRotated);
	void ReadSettings(string sFilePath);
private:
	Panel *m_pPanel;
	Rect m_roi;
	Mat m_Image;
	float m_conversionRate;
	// Canny Parameter Default Settings
	int m_low = 105;
	int m_sigmaX = 10, m_sigmaY = 2;
	int m_cannyLow = 85, m_ratio = 3;
	int m_houghLength = 155;
	// Feature Detection Settings Defaults
	float m_feature_height = 16.25;
	float m_feature_width = 13.25;
	// Calibration and Conversion
	int m_boardWidth = 6;
	int m_boardLength = 9;
	double m_cmPerPixel;
	double m_squareSize = 12.1;
	vector<Point2f> corners;
	// Private Methods
	Mat CannyDetection(Mat image, bool showImg = true);
	Mat CannyDetectionDebug(Mat image, bool showImg = true);
	void FindContours(Mat image);
	void DetectBlob(Mat image);
	// Default Window Name
	const char* m_WindowName = "My Image";
};