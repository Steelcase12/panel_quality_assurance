/////////////////////////////////////////////////////////////////
// File: Panel.cpp
// Descripiton:
//  This is the main header file for the C++ project. It 
//  contains the function prototypes for all of the Panel image
//  processing funcitons and the declarations of all of Panel's
//  private member variables. See Panel.cpp for function
//  descriptions. 
////////////////////////////////////////////////////////////////
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
	void MaskWithColor(string imgPath, string color, bool debug = false);
	void DetectEdges(string imgPath, bool debug);
	void PixelsToLength(string imgPath);
	void CalibrateCamera(string filePath);
	void CalibrateCameraNoOutput(string filePath);
	void LoadCalibration(string filePath);
	void CascadeClassify(string imgPath, string classPath);
	void BatchCalibrate(string dirPath);	
	void DetectFeatures(string scenePath, string objPath, bool exceedsBorder, bool featureRotated);
	void ReadSettings(string sFilePath, bool showSuccess = false);
	void ColorAtPoint(Point point);
	void PointLocation(Point point);
private:
	Panel *m_pPanel;
	Mat m_Image;
	string ColorName(Vec3b HSV);
	// Default Window Name
	const char* m_WindowName = "My Image";
	// Canny Parameter Default Settings
	int m_lowCannyThreshold = 105;
	int m_sigmaX = 10, m_sigmaY = 2;
	int m_cannyLow = 85, m_ratio = 3;
	int m_houghLength = 155;
	// Feature Detection Settings
	float m_feature_height = 16.25;
	float m_feature_width = 13.25;
	Rect m_roi;
	float m_conversionRate;
	// Tag Detection Settings
	int m_lowTagThreshold = 60;
	int m_blobArea = 325;
	// Camera Calibration
	Mat m_mainMap1, m_mainMap2;
	Mat m_mainCameraMatrix, m_mainDistCoeffs;
	//Pixel Conversion with Checkerboard
	int m_boardWidth = 6;
	int m_boardLength = 9;
	double m_cmPerPixel;
	double m_squareSize = 12.1;
	vector<Point2f> corners;
	// Private Methods
	Mat CannyDetection(Mat image, bool showImg = true);
	Mat CannyDetectionDebug(Mat image, bool showImg = true);
	void FindContours(Mat image);
	void DetectBlob(Mat image, bool debug = false);
	void ReadFeatureSettings(string sFilePath, bool showSuccess = false);
	void GetKeyPoints(Mat image, std::vector<KeyPoint> &keypoints, bool debug);
};