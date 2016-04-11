#pragma once
#pragma comment(lib,"user32.lib")
#include "iomanip"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

// Helper function to display a message box
void ShowMessage(string message)
{
	char buff[100];
	sprintf_s(buff, "%s", message.c_str());
	MessageBoxA(NULL, (LPCSTR)buff, (LPCSTR)"Panel_QA_CPP.dll", MB_OK);
}

// Helper function to replace characters in a string
void strReplace(string& source, string const& find, string const& replace)
{
	for (string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}
}

void FixPath(string &path)
{
	strReplace(path, "\\", "\\\\");
}