// This is the main DLL file.

#include "Panel.h"

Panel::Panel()
{
}

Panel::~Panel()
{
	delete m_pPanel;
}

void ShowMessage(string message)
{
	char buff[100];
	sprintf_s(buff, "%s", message.c_str());
	MessageBoxA(NULL, (LPCSTR)buff, (LPCSTR)"Panel_QA_CPP.dll", MB_OK);
}

static void onMouse(int event, int x, int y, int f, void *ptr)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		Panel *pPanel = static_cast<Panel*>(ptr);
		Point clickPoint(x, y);
		pPanel->ColorAtPoint(clickPoint);
	}
}

bool Panel::ShowImage(string sImgPath, string windowTitle)
{
	m_pPanel = new Panel;
	// read specified image
	m_pPanel->m_Image = imread(sImgPath, IMREAD_COLOR);

	if (m_pPanel->m_Image.empty()) // Check for invalid input
	{
		ShowMessage("Could not open or find the image");
		return false;
	}

	// Show the image
	imshow(m_WindowName, m_pPanel->m_Image);
	// Set mouse callback to show the color of the point clicked
	setMouseCallback(windowTitle, onMouse, static_cast<void*>(&m_pPanel));

	return true;
}

void strReplace(string& source, string const& find, string const& replace)
{
	for (string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}
}

void Panel::FixPath(string &path)
{
	strReplace(path, "\\" , "\\\\");
}

string Panel::ColorName(Vec3b color)
{
	uchar hue = color.val[0];
	uchar sat = color.val[1];
	uchar val = color.val[2];
	if (sat >= 100 && val >= 30)
	{
		if (hue >= 105 && hue <= 131)
			return "Blue";
		else if (hue <= 20 && (val <= 160 && val >= 55))
			return "Brown";
		else if (hue >= 160 || hue <= 10)
			return "Red";
		else if (hue >= 15 && hue <= 35)
			return "Yellow";
		else if (hue >= 50 && hue <= 70)
			return "Green";
	}
	
	else if (val < 30)
		return "Black";
	else if (val >= 190)
		return "White";

	return "Unknown";
}

void Panel::ColorAtPoint(Point point)
{
	Mat HSV;
	cvtColor(m_pPanel->m_Image, HSV, CV_BGR2HSV);
	Vec3b BGRpix, HSVpix;
	BGRpix = m_pPanel->m_Image.at<Vec3b>(Point(point.x, point.y));
	HSVpix = HSV.at<Vec3b>(Point(point.x, point.y));
	uchar blue, green, red;
	uchar hue, sat, val;
	blue = BGRpix.val[0];
	green = BGRpix.val[1];
	red = BGRpix.val[2];
	hue = HSVpix.val[0];
	sat = HSVpix.val[1];
	val = HSVpix.val[2];
	// Convert to string
	string RGBcolorStr("(" + to_string(red) + "," + to_string(green) + "," + to_string(blue) + ")");
	string HSVcolorStr("(" + to_string(hue) + "," + to_string(sat) + "," + to_string(val) + ")");
	// Display the color strings
	ShowMessage("Point: (" + to_string(point.x) + "," + to_string(point.y) +
		") \nRGB Value: " + RGBcolorStr + "\nHSV Value: " + HSVcolorStr + "\nColor: " + m_pPanel->ColorName(HSVpix));
}

void Panel::MaskWithColor(string sImgPath, string color)
{
	if(!ShowImage(sImgPath, "Original"))
		return;

	// read specified image
	m_pPanel->m_Image = imread(sImgPath, IMREAD_COLOR);
	Mat HSV, Mask, BGR, Result;
	double lowerBound, upperBound;
	cvtColor(m_pPanel->m_Image, HSV, CV_BGR2HSV);
	if (color == "blue")
	{
		lowerBound = 105;
		upperBound = 131;
		inRange(HSV, Scalar(lowerBound, 100, 30), Scalar(upperBound, 255, 255), Mask);
		m_pPanel->m_Image.copyTo(Result, Mask);
	}
	else if (color == "red")
	{
		Mat Mask1, Mask2;
		lowerBound = 0;
		upperBound = 10;
		inRange(HSV, Scalar(lowerBound, 100, 30), Scalar(upperBound, 255, 255), Mask1);
		lowerBound = 160;
		upperBound = 180;
		inRange(HSV, Scalar(lowerBound, 100, 30), Scalar(upperBound, 255, 255), Mask2);
		bitwise_or(Mask1, Mask2, Mask);
		m_pPanel->m_Image.copyTo(Result, Mask);
	}
	// imshow("original", HSV);
	imshow("Mask", Mask);
	imshow("Result", Result);
}
