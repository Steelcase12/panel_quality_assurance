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

void MYPanel::DetectColor(System::String^ imgPath)
{
	MYConversion ^convert = gcnew MYConversion();
	string strImgPath = convert->myStringToChar(imgPath);
	panel->DetectColor((string)strImgPath);
}

void MYPanel::ShowMessage(System::String^ message)
{
	MYConversion ^convert = gcnew MYConversion();
	string str = convert->myStringToChar(message);
	panel->ShowMessage((string)str);
}

void MYPanel::ShowImage(System::String^ imgPath)
{
	MYConversion ^convert = gcnew MYConversion();
	string str = convert->myStringToChar(imgPath);
	panel->ShowImage((string)str);
}

// ++++++++++++ MYConversion Class ++++++++++++ 
MYConversion::MYConversion() {}

char* MYConversion::myStringToChar(System::String^ str)
{
	IntPtr ptr = Marshal::StringToHGlobalAnsi(str);
	return static_cast<char *>(ptr.ToPointer());
}