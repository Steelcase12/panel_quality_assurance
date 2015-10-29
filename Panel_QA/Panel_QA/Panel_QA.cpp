// This is the main DLL file.

#include "stdafx.h"
#include "Panel_QA.h"

namespace Panels
{
	Panel::Panel()
	{
		// constructor
	}

	Panel::~Panel()
	{
		// destructor
	}

	void Panel::ShowMessage(String^ message)
	{
		MessageBox::Show(message, "Panel_QA.dll", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
}

