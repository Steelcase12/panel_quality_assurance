// This is the main DLL file.
#include "stdafx.h"
#include "Panel_QA.h"

using namespace MYopencv;

MYPanel::MYPanel()
{
	panel = new Panel();
}

void MYPanel::ShowMessage(System::String^ message)
{
	MYConversion ^convert = gcnew MYConversion();
	string str = convert->myStringToChar(message);
	panel->ShowMessage((string)str);
}

// ++++++++++++ MYConversion Class ++++++++++++ 
MYConversion::MYConversion() {}

char* MYConversion::myStringToChar(System::String^ str)
{
	IntPtr ptr = Marshal::StringToHGlobalAnsi(str);
	return static_cast<char *>(ptr.ToPointer());
}