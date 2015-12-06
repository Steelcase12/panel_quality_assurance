// This is the main DLL file.

#include "Panel.h"

Panel::Panel()
{
}

Panel::~Panel()
{
	delete pPanel;
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

void Panel::DetectColor(string sImgPath)
{
	pPanel = new Panel;
	// read specified image
	pPanel->m_Image = imread(sImgPath, IMREAD_COLOR);
	Mat HSV;
	cvtColor(pPanel->m_Image, HSV, CV_BGR2HSV);

	if (pPanel->m_Image.empty()) // Check for invalid input
	{
		ShowMessage("Could not open or find the image");
		return;
	}

	imshow(m_WindowName, pPanel->m_Image);

	// Get the color of the pixel at the middle of the image
	Point midPoint(pPanel->m_Image.cols / 2, pPanel->m_Image.rows / 2);
	ColorAtPoint(midPoint);

	setMouseCallback(pPanel->m_WindowName, onMouse, static_cast<void*>(&pPanel));
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
	cvtColor(pPanel->m_Image, HSV, CV_BGR2HSV);
	Vec3b BGRpix, HSVpix;
	BGRpix = pPanel->m_Image.at<Vec3b>(Point(point.x, point.y));
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
	ShowMessage("Point: (" + to_string(m_Image.cols / 2) + "," + to_string(m_Image.rows / 2) +
		") \nRGB Value: " + RGBcolorStr + "\nHSV Value: " + HSVcolorStr + "\nColor: " + pPanel->ColorName(HSVpix));
}
