// This is the main DLL file.
#include "stdafx.h"
#include "Panel_QA.h"

using namespace MYopencv;

MYPanel::MYPanel()
{
	panel = new Panel();
}

MYPanel::~MYPanel()
{
	delete panel;
}

void MYPanel::ShowImage(System::String^ imgPath, System::String^ windowTitle)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	string strWindowTitle = convert->myStringToChar(windowTitle);
	panel->ShowImage((string)strImgPath, (string)strWindowTitle);
}

void MYPanel::MaskWithColor(System::String^ imgPath, System::String^ color)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	string strColor = convert->myStringToChar(color);
	panel->MaskWithColor((string)strImgPath, (string)strColor);
}

void MYPanel::DetectEdges(System::String^ imgPath)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	panel->DetectEdges((string)strImgPath);
}

// ++++++++++++ MYConversion Class ++++++++++++ 
MYConversion::MYConversion() {}

char* MYConversion::myStringToChar(System::String^ str)
{
	IntPtr ptr = Marshal::StringToHGlobalAnsi(str);
	return static_cast<char *>(ptr.ToPointer());
}