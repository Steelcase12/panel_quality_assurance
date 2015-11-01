// This is the main DLL file.

#include "Panel.h"

Panel::Panel()
{
	// constructor
}

Panel::~Panel()
{
	// destructor
}

void Panel::ShowMessage(string message)
{
	char buff[100];
	sprintf_s(buff, "%s", message.c_str());
	MessageBoxA(NULL, (LPCSTR)buff, (LPCSTR)"Panel_QA_CPP.dll", MB_OK);
}

