#pragma once

/////////////////////////////////////////////////////////////
// File: Panel_QA.h
// Descripiton:
//  This is the header file for the project which links
//  the C# project with the C++ project. It is 
//  written in C++/CLI. It contains calls to Panel.cpp
//  functions and some string conversions. See Panel.cpp 
//  for function explainations.
////////////////////////////////////////////////////////////

#include "..\Panel_QA_CPP\Panel.h"
#include "..\Panel_QA_CPP\Panel.cpp"

// Test

using namespace System;
using namespace System::Runtime::InteropServices;

namespace MYopencv {
	public ref class MYConversion
	{
	public:
		MYConversion();
		char* myStringToChar(System::String^ str);
	};

	public ref class MYPanel
	{
	public:
		MYPanel();
		~MYPanel();
		void ShowImage(System::String^ imgPath, System::String^ windowTitle);
		void ShowImageWithCalibration(System::String^ imgPath, System::String^ windowTitle);
		void MaskWithColor(System::String^ imgPath, System::String^ color, bool debug);
		void DetectEdges(System::String^ imgPath, bool debug);
		void PixelsToLength(System::String^ imgPath);
		void CalibrateCamera(System::String^ filePath);
		void CalibrateCameraNoOutput(System::String^ filePath);
		void LoadCalibration(System::String^ filePath);
		void CascadeClassify(System::String^ imgPath, System::String^ classifierPath);
		void BatchCalibrate(System::String^ dirPath);		
		void DetectFeatures(System::String^ scenePath, System::String^ objPath, bool exceedsBorder, bool featureRotated);
		void ReadSettings(System::String ^ sFilePath);
	private:
		Panel *panel;
	};
}