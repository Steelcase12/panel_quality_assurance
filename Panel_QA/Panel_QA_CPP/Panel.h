// Panel.h
#pragma once
#pragma comment(lib,"user32.lib")
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Panel
{
public:
	Panel();
	~Panel();
	void ShowMessage(string message);
private:
	bool win0;
};