// This is the main DLL file.

#include "Panel.h"
#include "Calibrate.h"

Panel::Panel()
{
}

Panel::~Panel()
{
	delete m_pPanel;
}


///////////////////////////////////////////////////////////////////////
///// Helper functions for Computing Hough Line Intersections /////////
///////////////////////////////////////////////////////////////////////
vector<Point2f> lineToPointPair(Vec2f line)
{
	vector<Point2f> points;

	float r = line[0], t = line[1];
	double cos_t = cos(t), sin_t = sin(t);
	double x0 = r*cos_t, y0 = r*sin_t;
	double alpha = 1000;

	points.push_back(Point2f(x0 + alpha*(-sin_t), y0 + alpha*cos_t));
	points.push_back(Point2f(x0 - alpha*(-sin_t), y0 - alpha*cos_t));

	return points;
}

bool acceptLinePair(Vec2f line1, Vec2f line2, float minTheta)
{
	float theta1 = line1[1], theta2 = line2[1];

	if (theta1 < minTheta)
	{
		theta1 += CV_PI; // dealing with 0 and 180 ambiguities...
	}

	if (theta2 < minTheta)
	{
		theta2 += CV_PI; // dealing with 0 and 180 ambiguities...
	}

	return abs(theta1 - theta2) > minTheta;
}

// the long nasty wikipedia line-intersection equation...bleh...
Point2f computeIntersect(Vec2f line1, Vec2f line2)
{
	vector<Point2f> p1 = lineToPointPair(line1);
	vector<Point2f> p2 = lineToPointPair(line2);

	float denom = (p1[0].x - p1[1].x)*(p2[0].y - p2[1].y) - (p1[0].y - p1[1].y)*(p2[0].x - p2[1].x);
	Point2f intersect(((p1[0].x*p1[1].y - p1[0].y*p1[1].x)*(p2[0].x - p2[1].x) -
		(p1[0].x - p1[1].x)*(p2[0].x*p2[1].y - p2[0].y*p2[1].x)) / denom,
		((p1[0].x*p1[1].y - p1[0].y*p1[1].x)*(p2[0].y - p2[1].y) -
		(p1[0].y - p1[1].y)*(p2[0].x*p2[1].y - p2[0].y*p2[1].x)) / denom);

	return intersect;
}

//////////////////////////////////////////////////////////////////////////////
///// End of Helper functions for Computing Hough Line Intersections /////////
//////////////////////////////////////////////////////////////////////////////

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

// On click listener to display the HSV value of the point clicked
static void onMouse(int event, int x, int y, int f, void *ptr)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		Panel *pPanel = static_cast<Panel*>(ptr);
		Point clickPoint(x, y);
		pPanel->ColorAtPoint(clickPoint);
	}
}

// Function to display the specified image and add an 
//	on click listener (onMouse())
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
	cvtColor(m_pPanel->m_Image, HSV, CV_BGR2HSV);
	if (color == "blue")
	{
		inRange(HSV, Scalar(105, 100, 30), Scalar(131, 255, 255), Mask);
	}
	else if (color == "red")
	{
		Mat Mask1, Mask2;
		inRange(HSV, Scalar(0, 100, 30), Scalar(10, 255, 255), Mask1);
		inRange(HSV, Scalar(160, 100, 30), Scalar(180, 255, 255), Mask2);
		bitwise_or(Mask1, Mask2, Mask);
	}
	else if (color == "panel")
	{
		int h1Lo = 150, s1Lo = 10, v1Lo = 100;
		int h1Hi = 180, s1Hi = 50, v1Hi = 200;
		int h2Lo = 0, s2Lo = 30, v2Lo = 100;
		int h2Hi = 15, s2Hi = 50, v2Hi = 150;
		namedWindow("InRange Tester", CV_WINDOW_AUTOSIZE);
		cvCreateTrackbar("Hue Lo 1:", "InRange Tester", &h1Lo, 180);
		cvCreateTrackbar("Hue Hi 1:", "InRange Tester", &h1Hi, 180);
		cvCreateTrackbar("Sat Lo 1", "InRange Tester", &s1Lo, 255);
		cvCreateTrackbar("Sat Hi 1", "InRange Tester", &s1Hi, 255);
		cvCreateTrackbar("Val Lo 1", "InRange Tester", &v1Lo, 255);
		cvCreateTrackbar("Val Hi 1", "InRange Tester", &v1Hi, 255);
		cvCreateTrackbar("Hue Lo 2:", "InRange Tester", &h2Lo, 180);
		cvCreateTrackbar("Hue Hi 2:", "InRange Tester", &h2Hi, 180);
		cvCreateTrackbar("Sat Lo 2", "InRange Tester", &s2Lo, 255);
		cvCreateTrackbar("Sat Hi 2", "InRange Tester", &s2Hi, 255);
		cvCreateTrackbar("Val Lo 2", "InRange Tester", &v2Lo, 255);
		cvCreateTrackbar("Val Hi 2", "InRange Tester", &v2Hi, 255);
		Mat Mask1, Mask2;
		while (true)
		{
			inRange(HSV, Scalar(h1Lo, s1Lo, v1Lo), Scalar(h1Hi, s1Hi, v1Hi), Mask1);
			inRange(HSV, Scalar(h2Lo, s2Lo, v2Lo), Scalar(h2Hi, s2Hi, v2Hi), Mask2);
			bitwise_or(Mask1, Mask2, Mask);

			m_pPanel->m_Image.copyTo(Result, Mask);

			imshow("Result", Result);

			if (waitKey(30) == 27)
				break;
		}
		return;
	}
	m_pPanel->m_Image.copyTo(Result, Mask);
	Mat greyOrig;
	cvtColor(Result, greyOrig, CV_BGR2GRAY);
	Mat thresh;
	threshold(greyOrig, thresh, 50.0, 255.0, THRESH_BINARY);
	Mat filtered;
	m_pPanel->m_Image.copyTo(filtered, thresh);

	DetectBlob(filtered);
}

void Panel::DetectEdges(string sImgPath)
{
	m_pPanel = new Panel;
	// read specified image
	m_pPanel->m_Image = imread(sImgPath, IMREAD_COLOR);

	if (m_pPanel->m_Image.empty()) // Check for invalid input
	{
		ShowMessage("Could not open or find the image");
		return;
	}

	// Show the orignal image and detected canny edges
	imshow("Original Image", m_pPanel->m_Image);

	// Canny Edge and Hough Line Detection
	Mat edges = CannyDetection(m_pPanel->m_Image);
}

Mat Panel::CannyDetection(Mat image)
{
	Mat greyImage;
	cvtColor(image, greyImage, CV_BGR2GRAY);

	namedWindow("Thresh", CV_WINDOW_AUTOSIZE);
	Mat thresh, blurredThresh, edges, edgesGray;
	int low = 141, high = 255;
	int sigmaX = 2, sigmaY = 2; 
	int cannyLow = 255, cannyHi = 255;
	int houghLength = 116;
	vector<Vec2f> lines;
	/*	This code is for testing different values of various functions
		Uncomment if you want to test different values than the ones given
	*/
	cvCreateTrackbar("Threshhold", "Thresh", &low, 255);
	// cvCreateTrackbar("Value", "Thresh", &high, 255);
	// cvCreateTrackbar("SigmaX", "Thresh", &sigmaX, 500);
	// cvCreateTrackbar("SigmaY", "Thresh", &sigmaY, 500);
	cvCreateTrackbar("Canny Low", "Thresh", &cannyLow, 255);
	cvCreateTrackbar("Canny High", "Thresh", &cannyHi, 255);
	cvCreateTrackbar("Hough Line length", "Thresh", &houghLength, 1000);
	while (true)
	{
		threshold(greyImage, thresh, low, 255, THRESH_BINARY);
		imshow("Threshhold", thresh);

		GaussianBlur(thresh, blurredThresh, Size(7, 7), sigmaX, sigmaY);
		imshow("Blurred", blurredThresh);

		Canny(blurredThresh, edges, cannyLow, cannyHi, 3);
		imshow("Canny Edges", edges);

		HoughLines(edges, lines, 1, CV_PI / 180, houghLength, 0, 0);

		cvtColor(edges, edgesGray, CV_GRAY2BGR);
		for (size_t i = 0; i < lines.size(); i++)
		{
			float rho = lines[i][0], theta = lines[i][1];
			Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(edgesGray, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
		}

		imshow("Hough Lines", edgesGray);

		// compute the intersection from the lines detected...
		vector<Point2f> intersections;
		for (size_t i = 0; i < lines.size(); i++)
		{
			for (size_t j = 0; j < lines.size(); j++)
			{
				Vec2f line1 = lines[i];
				Vec2f line2 = lines[j];
				if (acceptLinePair(line1, line2, CV_PI / 32))
				{
					Point2f intersection = computeIntersect(line1, line2);
					intersections.push_back(intersection);
				}
			}
		}

		if (intersections.size() > 0)
		{
			vector<Point2f>::iterator i;
			for (i = intersections.begin(); i != intersections.end(); ++i)
			{
				cout << "Intersection is " << i->x << ", " << i->y << endl;
				circle(m_pPanel->m_Image, *i, 1, Scalar(0, 255, 0), 3);
			}
		}

		imshow("intersect", m_pPanel->m_Image);

		if (waitKey(30) == 27)
			break;
	}
	return edges;
}

void Panel::DetectBlob(Mat image)
{
	Mat grayImage, dilatedEroded, dilated, blurred;
	cvtColor(image, grayImage, CV_BGR2GRAY);

	// Setup SimpleBlobDetector parameters.
	Ptr<SimpleBlobDetector> detector;
	SimpleBlobDetector::Params params;
	std::vector<KeyPoint> keypoints;
	Mat im_with_keypoints, thresh;

	int low = 60;
	int blobArea = 325;
	int sigmaX = 0, sigmaY = 0;
	/*	This is Test Code
		Uncomment this and the waiteKey() code and add closing bracket after
		break to run this portion of code withs trackbars

	namedWindow("Blob", CV_WINDOW_NORMAL);
	cvCreateTrackbar("Blob Area", "Blob", &blobArea, 2000);
	cvCreateTrackbar("Threshhold", "Blob", &low, 255);
	while (true)
	{
	*/
	dilate(grayImage, dilated, Mat());

	GaussianBlur(dilated, blurred, Size(7, 7), 0, 0);

	threshold(blurred, thresh, low, 255, THRESH_BINARY);

	// Filter by Area.
	params.filterByArea = true;
	params.filterByColor = false;
	params.filterByConvexity = false;
	params.filterByCircularity = false;
	params.filterByInertia = false;
	params.minArea = blobArea;

	// Set up the detector with default parameters.
	detector = SimpleBlobDetector::create(params);

	// Detect blobs.
	detector->detect(thresh, keypoints);

	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
	drawKeypoints(thresh, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Show blobs
	imshow("keypoints", im_with_keypoints);

	// Pass/Fail Message
	if (!keypoints.empty())
		ShowMessage("Tag detected");
	else
		ShowMessage("No tag detected");
		/*
		if (waitKey(30) == 27)
			break;
			}
		*/
}

void Panel::CalibrateCamera(string sFilePath)
{
	help();

	//! [file_read]
	Settings s;
	const string inputSettingsFile = sFilePath;
	FileStorage fs(inputSettingsFile, FileStorage::READ); // Read the settings
	if (!fs.isOpened())
	{
		cout << "Could not open the configuration file: \"" << inputSettingsFile << "\"" << endl;
//		return -1;
	}
	fs["Settings"] >> s;
	fs.release();                                         // close Settings file
	//! [file_read]

	//FileStorage fout("settings.yml", FileStorage::WRITE); // write config as YAML
	//fout << "Settings" << s;

	if (!s.goodInput)
	{
		cout << "Invalid input detected. Application stopping. " << endl;
//		return -1;
	}

	vector<vector<Point2f> > imagePoints;
	Mat cameraMatrix, distCoeffs;
	Size imageSize;
	int mode = s.inputType == Settings::IMAGE_LIST ? CAPTURING : DETECTION;
	clock_t prevTimestamp = 0;
	const Scalar RED(0, 0, 255), GREEN(0, 255, 0);
	const char ESC_KEY = 27;

	//! [get_input]
	for (;;)
	{
		Mat view;
		bool blinkOutput = false;

		view = s.nextImage();

		//-----  If no more image, or got enough, then stop calibration and show result -------------
		if (mode == CAPTURING && imagePoints.size() >= (size_t)s.nrFrames)
		{
			if (runCalibrationAndSave(s, imageSize, cameraMatrix, distCoeffs, imagePoints))
				mode = CALIBRATED;
			else
				mode = DETECTION;
		}
		if (view.empty())          // If there are no more images stop the loop
		{
			// if calibration threshold was not reached yet, calibrate now
			if (mode != CALIBRATED && !imagePoints.empty())
				runCalibrationAndSave(s, imageSize, cameraMatrix, distCoeffs, imagePoints);
			break;
		}
		//! [get_input]

		imageSize = view.size();  // Format input image.
		if (s.flipVertical)    flip(view, view, 0);

		//! [find_pattern]
		vector<Point2f> pointBuf;

		bool found;
		switch (s.calibrationPattern) // Find feature points on the input format
		{
		case Settings::CHESSBOARD:
			found = findChessboardCorners(view, s.boardSize, pointBuf,
				CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);
			break;
		case Settings::CIRCLES_GRID:
			found = findCirclesGrid(view, s.boardSize, pointBuf);
			break;
		case Settings::ASYMMETRIC_CIRCLES_GRID:
			found = findCirclesGrid(view, s.boardSize, pointBuf, CALIB_CB_ASYMMETRIC_GRID);
			break;
		default:
			found = false;
			break;
		}
		//! [find_pattern]
		//! [pattern_found]
		if (found)                // If done with success,
		{
			// improve the found corners' coordinate accuracy for chessboard
			if (s.calibrationPattern == Settings::CHESSBOARD)
			{
				Mat viewGray;
				cvtColor(view, viewGray, COLOR_BGR2GRAY);
				cornerSubPix(viewGray, pointBuf, Size(11, 11),
					Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
			}

			if (mode == CAPTURING &&  // For camera only take new samples after delay time
				(!s.inputCapture.isOpened() || clock() - prevTimestamp > s.delay*1e-3*CLOCKS_PER_SEC))
			{
				imagePoints.push_back(pointBuf);
				prevTimestamp = clock();
				blinkOutput = s.inputCapture.isOpened();
			}

			// Draw the corners.
			drawChessboardCorners(view, s.boardSize, Mat(pointBuf), found);
		}
		//! [pattern_found]
		//----------------------------- Output Text ------------------------------------------------
		//! [output_text]
		string msg = (mode == CAPTURING) ? "100/100" :
			mode == CALIBRATED ? "Calibrated" : "Press 'g' to start";
		int baseLine = 0;
		Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
		Point textOrigin(view.cols - 2 * textSize.width - 10, view.rows - 2 * baseLine - 10);

		if (mode == CAPTURING)
		{
			if (s.showUndistorsed)
				msg = format("%d/%d Undist", (int)imagePoints.size(), s.nrFrames);
			else
				msg = format("%d/%d", (int)imagePoints.size(), s.nrFrames);
		}

		putText(view, msg, textOrigin, 1, 1, mode == CALIBRATED ? GREEN : RED);

		if (blinkOutput)
			bitwise_not(view, view);
		//! [output_text]
		//------------------------- Video capture  output  undistorted ------------------------------
		//! [output_undistorted]
		if (mode == CALIBRATED && s.showUndistorsed)
		{
			Mat temp = view.clone();
			undistort(temp, view, cameraMatrix, distCoeffs);
		}
		//! [output_undistorted]
		//------------------------------ Show image and check for input commands -------------------
		//! [await_input]
		imshow("Image View", view);
		char key = (char)waitKey(s.inputCapture.isOpened() ? 50 : s.delay);

		if (key == ESC_KEY)
			break;

		if (key == 'u' && mode == CALIBRATED)
			s.showUndistorsed = !s.showUndistorsed;

		if (s.inputCapture.isOpened() && key == 'g')
		{
			mode = CAPTURING;
			imagePoints.clear();
		}
		//! [await_input]
	}

	// -----------------------Show the undistorted image for the image list ------------------------
	//! [show_results]
	if (s.inputType == Settings::IMAGE_LIST && s.showUndistorsed)
	{
		Mat view, rview, map1, map2;
		initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
			getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
			imageSize, CV_16SC2, map1, map2);

		for (size_t i = 0; i < s.imageList.size(); i++)
		{
			view = imread(s.imageList[i], 1);
			if (view.empty())
				continue;
			remap(view, rview, map1, map2, INTER_LINEAR);
			imshow("Image View", rview);
			char c = (char)waitKey();
			if (c == ESC_KEY || c == 'q' || c == 'Q')
				break;
		}
	}
	//! [show_results]

//	return 0;

}


