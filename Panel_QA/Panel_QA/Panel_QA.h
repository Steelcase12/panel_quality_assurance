#pragma once

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
		void ShowMessage(System::String^ message);

	private:
		Panel *panel;
	};
}