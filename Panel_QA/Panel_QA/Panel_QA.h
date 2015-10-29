// Panel_QA.h
using namespace std;
using namespace System::Windows::Forms;
using namespace System;

#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace Panels
{
	public ref class Panel
	{
	private:
	public:
		Panel();
		~Panel();
		void ShowMessage(String^ message);
	};
}