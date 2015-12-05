// This is the main DLL file.

#include "Panel.h"

Panel::Panel()
{
	// constructor
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
	Mat image = *(static_cast<Mat*>(ptr));
	Mat HSV;
	cvtColor(image, HSV, CV_BGR2HSV);
	if (event == EVENT_LBUTTONDOWN)
	{
		uchar blue, green, red;
		int hue, sat, val;
		Vec3b RGBpix, HSVpix;
		RGBpix = image.at<Vec3b>(y, x);
		HSVpix = HSV.at<Vec3b>(y, x);
		blue = RGBpix.val[0];
		green = RGBpix.val[1];
		red = RGBpix.val[2];
		hue = HSVpix.val[0];
		sat = HSVpix.val[1];
		val = HSVpix.val[2];
		string RGBStr("RGB: (" + to_string(red) + "," + to_string(green) + "," + to_string(blue) + ")");
		string HSVStr("HSV: (" + to_string(hue) + "," + to_string(sat) + "," + to_string(val) + ")");

		ShowMessage("Point (" + to_string(x) + "," + to_string(y) + ")\n" + RGBStr + "\n" + HSVStr);
	}
}

void Panel::DetectColor(string sImgPath)
{
	// read specified image
	m_Image = imread(sImgPath, IMREAD_COLOR);

	if (m_Image.empty()) // Check for invalid input
	{
		ShowMessage("Could not open or find the image");
		return;
	}

	imshow(m_WindowName, m_Image);

	// Get the color of the pixel at the middle of the image
	Vec3b color = m_Image.at<Vec3b>(Point(m_Image.cols / 2, m_Image.rows / 2));
	uchar blue = color.val[0];
	uchar green = color.val[1];
	uchar red = color.val[2];
	// Convert to string
	string colorStr("(" + to_string(red) + "," + to_string(green) + "," + to_string(blue) + ")");
	// Display the color
	ShowMessage("Mid point: (" + to_string(m_Image.cols / 2) + "," + to_string(m_Image.rows / 2) + ") \nRGB Value: " + colorStr);
	m_bDrag = FALSE;
	setMouseCallback(m_WindowName, onMouse, static_cast<void*>(&m_Image));
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
