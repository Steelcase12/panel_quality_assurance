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

void Panel::DetectColor(string sImgPath)
{
	Mat image, imageGrey;
	double minVal, maxVal;
	Point minLoc, maxLoc;

	// read specified image
	image = imread(sImgPath, IMREAD_COLOR);
	imageGrey = imread(sImgPath, CV_LOAD_IMAGE_GRAYSCALE);

	if (image.empty()) // Check for invalid input
	{
		ShowMessage("Could not open or find the image");
		return;
	}

	// Get the color of the pixel at the middle of the image
	Vec3b color = image.at<Vec3b>(Point(image.cols/2,image.rows/2));
	uchar blue = color.val[0];
	uchar green = color.val[1];
	uchar red = color.val[2];
	// Convert to string
	string colorStr("(" + to_string(red) + "," + to_string(green) + "," + to_string(blue) + ")");
	// Display the color
	ShowMessage("RGB value at point (" + to_string(image.cols / 2) + "," + to_string(image.rows / 2) + "): " + colorStr);
	// ShowImage(sImgPath);
}

void Panel::ShowMessage(string message)
{
	char buff[100];
	sprintf_s(buff, "%s", message.c_str());
	MessageBoxA(NULL, (LPCSTR)buff, (LPCSTR)"Panel_QA_CPP.dll", MB_OK);
}

void Panel::ShowImage(string imgPath)
{
	pPanel = new Panel();
	pPanel->FixPath(imgPath);
	Mat image;
	image = imread(imgPath, IMREAD_COLOR); // Read the file

	if (image.empty()) // Check for invalid input
	{
		ShowMessage("Could not open or find the image");
		return;
	}

	namedWindow("Display window", CV_WINDOW_NORMAL); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window
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
