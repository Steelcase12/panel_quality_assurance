// This is the main DLL file.

#include "stdafx.h"
#include "Panel_QA.h"

Panel::Panel()
{
	// constructor
}

Panel::~Panel()
{
	// destructor
}

void Panel::PrintMessage(string message)
{
	printf("%s", message);
}

