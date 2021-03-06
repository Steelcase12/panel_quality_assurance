/////////////////////////////////////////////////////////////
// File: Panel_QA.cpp
// Descripiton:
//  This is the source file for the project which links
//  the C# project with the C++ project. It is 
//  written in C++/CLI. It contains calls to Panel.cpp
//  functions and some string conversions. See Panel.cpp 
//  for function explainations.
////////////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "Panel_QA.h"

using namespace MYopencv;

MYPanel::MYPanel()
{
	panel = new Panel();
}

MYPanel::~MYPanel()
{
	// delete panel;
}

void MYPanel::ShowImage(System::String^ imgPath, System::String^ windowTitle)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	string strWindowTitle = convert->myStringToChar(windowTitle);
	panel->ShowImage((string)strImgPath, (string)strWindowTitle);
}

void MYPanel::ShowImageWithCalibration(System::String^ imgPath, System::String^ windowTitle)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	string strWindowTitle = convert->myStringToChar(windowTitle);
	panel->ShowImageWithCalibration((string)strImgPath, (string)strWindowTitle, Mat());
}

void MYPanel::MaskWithColor(System::String^ imgPath, System::String^ color, bool debug)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	string strColor = convert->myStringToChar(color);
	panel->MaskWithColor((string)strImgPath, (string)strColor, debug);
}

void MYPanel::DetectEdges(System::String^ imgPath, bool debug)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	panel->DetectEdges((string)strImgPath, debug);
}

void MYPanel::CalibrateCamera(System::String^ imgPath)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	panel->CalibrateCamera((string)strImgPath);
}

void MYPanel::CalibrateCameraNoOutput(System::String^ imgPath)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	panel->CalibrateCameraNoOutput((string)strImgPath);
}

void MYPanel::LoadCalibration(System::String^ imgPath)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	panel->LoadCalibration((string)strImgPath);
}

void MYPanel::PixelsToLength(System::String^ imgPath)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	panel->PixelsToLength((string)strImgPath);
}

void MYPanel::BatchCalibrate(System::String^ dirPath)
{
	MYConversion ^convert = gcnew MYConversion();
	string strDirPath = convert->myStringToChar(dirPath);
	panel->BatchCalibrate(strDirPath);
}

void MYPanel::CascadeClassify(System::String^ imgPath, System::String^ classPath)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	string strClassPath = convert->myStringToChar(classPath);
	panel->CascadeClassify(strImgPath, strClassPath);
}

void MYPanel::DetectFeatures(System::String^ scenePath, System::String^ objPath, bool exceedsBorder, bool featureRotated)
{
	MYConversion ^convert = gcnew MYConversion();
	string strScenePath = convert->myStringToChar(scenePath);
	string strObjPath = convert->myStringToChar(objPath);
	panel->DetectFeatures(strScenePath, strObjPath, exceedsBorder, featureRotated);
}

void MYPanel::ReadSettings(System::String^ sFilePath)
{
	MYConversion ^convert = gcnew MYConversion();
	string strScenePath = convert->myStringToChar(sFilePath);
	panel->ReadSettings(strScenePath, true);
}

// ++++++++++++ MYConversion Class ++++++++++++ 
MYConversion::MYConversion() {}

char* MYConversion::myStringToChar(System::String^ str)
{
	IntPtr ptr = Marshal::StringToHGlobalAnsi(str);
	return static_cast<char *>(ptr.ToPointer());
}