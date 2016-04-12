// This is the main DLL file.

#include "include.h"
#include "Panel.h"
#include "Calibrate.h"
#include "iomanip"
#include "sstream"
#include "FeatureDetector.h"
Panel::Panel()
{
}

Panel::~Panel()
{
	delete m_pPanel;
}

// Camera Calibration Constants
Mat mainMap1, mainMap2;
Mat mainCameraMatrix, mainDistCoeffs;

///////////////////////////////////////////////////////////////////////
// Helper Function for Cascade Classifier				       ////////
///////////////////////////////////////////////////////////////////////

void detectAndDisplay(Mat image, string panel_cascade_name)
{
	CascadeClassifier panel_cascade;
	if (!panel_cascade.load(panel_cascade_name)){ printf("--(!)Error loading\n"); return; };

	std::vector<Rect> detectedPanels;
	Mat frame_gray;

	cvtColor(image, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	panel_cascade.detectMultiScale(frame_gray, detectedPanels, 1.1, 20, 0 | CV_HAAR_SCALE_IMAGE, Size(200, 200));

	for (size_t i = 0; i < detectedPanels.size(); i++)
	{
		Point topLeft(detectedPanels[i].x, detectedPanels[i].y);
		Point botRight(detectedPanels[i].x + detectedPanels[i].width, detectedPanels[i].y + detectedPanels[i].height);
		rectangle(image, topLeft, botRight, Scalar(0, 0, 255), 4);
}
	//-- Show what you got
	imshow("Classifier Result", image);
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

///////////////////////////////////////////////////////////////////////
// End of Helper Function for Cascade Classifier			   ////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///// Helper functions for Finding Contours                   /////////
///////////////////////////////////////////////////////////////////////
void morphIt(Mat &img)
{
	cvtColor(img, img, CV_RGB2GRAY);
	threshold(img, img, 50.0, 255.0, THRESH_BINARY);
	erode(img, img, Mat());
	dilate(img, img, Mat());
}

void blurthresh(Mat &img)
	{
	int kblur = 1;
	int threshval = 0;
	//medianBlur(img,img,kblur%2+3+kblur);
	blur(img, img, Size(kblur, kblur), Point(-1, -1), BORDER_DEFAULT);
	// threshold(img, img, threshval, 255, THRESH_BINARY_INV);
	}

void showimgcontours(Mat &threshedimg, Mat &original)
{
	vector<vector<Point> > contours;
	RotatedRect rect;
	vector<Vec4i> hierarchy;
	Point2f rectPoints[4];
	Scalar color = Scalar(255, 0, 0);
	double largest_area = 0;
	int largest_contour_index = 0;
	findContours(threshedimg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	//this will find largest contour
	for (size_t i = 0; i< contours.size(); i++) // iterate through each contour. 
	{
		double a = contourArea(contours[i], false);  //  Find the area of contour
		if (a>largest_area)
	{
			largest_area = a;
			largest_contour_index = i;                //Store the index of largest contour
	}

}
	//search for largest contour has end

	if (contours.size() > 0)
{
		drawContours(original, contours, largest_contour_index, CV_RGB(0, 255, 0), 2, 8, hierarchy);
		//if want to show all contours use below one
		//drawContours(original,contours,-1, CV_RGB(0, 255, 0), 2, 8, hierarchy);

		// Find and add bounding rectangle
		rect = minAreaRect(contours[largest_contour_index]);
		rect.points(rectPoints);
		int j = 0;
		for (j; j < 4; j++)
			line(original, rectPoints[j], rectPoints[(j + 1) % 4], color, 1, 8);
		string strDim = "Min Area Rectangle Dimensions:\n" + 
			to_string(rect.size.height) + " x " + to_string(rect.size.width);
		imshow("Largest Contour", original);
		ShowMessage(strDim);
	}
}

//////////////////////////////////////////////////////////////////////////////
///// End of Helper functions for Finding Contours					 /////////
//////////////////////////////////////////////////////////////////////////////

// On click listener to display the HSV value of the point clicked
static void onMouseColor(int event, int x, int y, int f, void *ptr)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		Panel *pPanel = static_cast<Panel*>(ptr);
		Point clickPoint(x, y);
		pPanel->ColorAtPoint(clickPoint);
	}
}

// On click listener to display the location of the point clicked
static void onMouseLocation(int event, int x, int y, int f, void *ptr)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		Panel *pPanel = static_cast<Panel*>(ptr);
		Point clickPoint(x, y);
		pPanel->PointLocation(clickPoint);
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

	// resize the image to have 1000 width, keeping the aspect ratio
	float r = 750.0f / m_pPanel->m_Image.cols;
	Size dim = Size(750, int(m_pPanel->m_Image.rows * r));
	resize(m_pPanel->m_Image, m_pPanel->m_Image, dim);

	// Find the ROI
	const Rect roi(0,0,650,m_pPanel->m_Image.rows);
	m_pPanel->m_Image(roi);

	// Show the image
	namedWindow(windowTitle, CV_WINDOW_KEEPRATIO);
	imshow(windowTitle, m_pPanel->m_Image);
	// Set mouse callback to show the color of the point clicked
	setMouseCallback(windowTitle, onMouseColor, static_cast<void*>(&m_pPanel));

	return true;
}

// Function to display the specified image and add an 
//	on click listener (onMouse())
bool Panel::ShowImageWithCalibration(string sImgPath, string windowTitle)
{
	m_pPanel = new Panel;
	// read specified image
	m_pPanel->m_Image = imread(sImgPath, IMREAD_COLOR);

	if (m_pPanel->m_Image.empty()) // Check for invalid input
	{
		ShowMessage("Could not open or find the image");
		return false;
	}

	// resize the image to have 1000 width, keeping the aspect ratio
	//float r = 750.0 / m_pPanel->m_Image.cols;
	//Size dim = Size(750.0, int(m_pPanel->m_Image.rows * r));
	//resize(m_pPanel->m_Image, m_pPanel->m_Image, dim);

	// Find the ROI
	//const Rect roi(0, 0, 650, m_pPanel->m_Image.rows);
	//m_pPanel->m_Image(roi);

	// Calibrate
	Mat rview;
	remap(m_pPanel->m_Image, rview, mainMap1, mainMap2, INTER_LINEAR);

	// Show the image
	namedWindow(windowTitle, CV_WINDOW_KEEPRATIO);
	imshow(windowTitle, rview);

	// Save image
	imwrite("Calibrated_Image.jpg", rview);

	// Set mouse callback to show the color of the point clicked
	setMouseCallback(windowTitle, onMouseColor, static_cast<void*>(&m_pPanel));

	return true;
}

// Must have folder named Calibrated_Folder prexisting in build folder 
void Panel::BatchCalibrate(string sdirPath)
{
	String path(sdirPath + "/*.jpg");
	vector<String> fn;
	int counter = 0;
	stringstream ss;
	string s;

	glob(path, fn, false);
	Mat img;
	Mat rview;
	for (size_t i = 0; i<fn.size(); i++)
	{
		img = imread(fn[i]);
		
		remap(img, rview, mainMap1, mainMap2, INTER_LINEAR);

		ss << setw(3) << setfill('0') << i;
		s = ss.str();

		// Save image
		imwrite("Calibrated_Folder/Checkerboard" + s + ".jpg", rview);
		cout << "Image " << i + 1 << " completed" << endl;

		ss.str("");
	}
	cout << "BATCHED";
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

void Panel::PointLocation(Point point)
{
	Point corner_point;
	corner_point.x = (int)m_pPanel->corners[9].x;
	corner_point.y = (int)m_pPanel->corners[9].y;
	double distance = norm(corner_point - point);
	
	line(m_pPanel->m_Image, point, corner_point, CV_RGB(255, 0, 0), 2);
	
	// .2932 cm/pixels
	cout << "Point1: (" + to_string(point.x) + "," + to_string(point.y) + ") " + 
		"\nPoint2: (" + to_string(corner_point.x) + "," + to_string(corner_point.y) + ") " +
		"\nDistance in pixels: " + to_string(distance) +
		"\nDistance in cm: " + to_string(distance * .2932) +
		"\n\n";

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", m_pPanel->m_Image);
}

void Panel::MaskWithColor(string sImgPath, string color)
{
	Mat HSV, Mask, MaskResult;
	// Show the original image
	if(!ShowImage(sImgPath, "Original"))
		return;
	// Convert the color HSV Format
	cvtColor(m_pPanel->m_Image, HSV, CV_BGR2HSV);
	// The inRange() function will create a mask with 
	// only the pixels of color in the range specified
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
		FindContours(m_pPanel->m_Image);
		/*
		int h1Lo = 0, s1Lo = 55, v1Lo = 115;
		int h1Hi = 20, s1Hi = 120, v1Hi = 210;
		int h2Lo = 0, s2Lo = 0, v2Lo = 0;
		int h2Hi = 0, s2Hi = 0, v2Hi = 0;

		// test code
		//
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
		//

		Mat Mask1, Mask2;
		// while (true)
		{
			inRange(HSV, Scalar(h1Lo, s1Lo, v1Lo), Scalar(h1Hi, s1Hi, v1Hi), Mask1);
			inRange(HSV, Scalar(h2Lo, s2Lo, v2Lo), Scalar(h2Hi, s2Hi, v2Hi), Mask2);
			bitwise_or(Mask1, Mask2, Mask);

			m_pPanel->m_Image.copyTo(MaskResult, Mask);

			// namedWindow("Mask Result", CV_WINDOW_AUTOSIZE);
			// imshow("Mask Result", MaskResult);

			// CannyDetection(Result);

			// if (waitKey(30) == 27)
			//	break;
		}
		*/
	}
	m_pPanel->m_Image.copyTo(MaskResult, Mask);
	/*
	if (color == "panel"){
		morphIt(MaskResult);
		blurthresh(MaskResult);
		// imshow("Morphed and Blurred", MaskResult);
		Mat modified;
		m_pPanel->m_Image.copyTo(modified, MaskResult);
		// imshow("Masked Original", modified);
		FindContours(modified);
	}
	*/

	if (color == "red" || color == "blue")
		DetectBlob(MaskResult);
}

void Panel::DetectEdges(string sImgPath)
{
	if (!ShowImage(sImgPath, "Original"))
		return;

	// Canny Edge and Hough Line Detection
	Mat edges = CannyDetection(m_pPanel->m_Image);
}

Mat Panel::CannyDetection(Mat image)
{
	Mat greyImage;
	cvtColor(image, greyImage, CV_BGR2GRAY);

	Mat thresh, blurredThresh, edges, edgesGray;
	int low = 105, high = 255;
	int sigmaX = 10, sigmaY = 2; 
	int cannyLow = 85, ratio = 3, aperture = 3;
	int houghLength = 164;
	vector<Vec2f> lines;
	/*	This code is for testing different values of various functions
		Uncomment if you want to test different values than the ones given

	namedWindow("Sliders", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("Threshhold", "Sliders", &low, 255);
	//cvCreateTrackbar("High", "Sliders", &high, 255);
	cvCreateTrackbar("SigmaX", "Sliders", &sigmaX, 500);
	cvCreateTrackbar("SigmaY", "Sliders", &sigmaY, 500);
	cvCreateTrackbar("Low Threshold", "Sliders", &cannyLow, 100);
	cvCreateTrackbar("Ratio", "Sliders", &ratio, 5);
	cvCreateTrackbar("Hough Line length", "Sliders", &houghLength, 200);

	while (true)
	{	*/
		threshold(greyImage, thresh, low, 255, THRESH_BINARY);
		// namedWindow("Threshhold", CV_WINDOW_AUTOSIZE);
		// imshow("Threshhold", thresh);

		Mat dilated;
		dilate(thresh, dilated, Mat());
		// namedWindow("Dilated", CV_WINDOW_AUTOSIZE);
		// imshow("Dilated", dilated);

		GaussianBlur(thresh, blurredThresh, Size(7, 7), sigmaX, sigmaY);
		// namedWindow("Blurred", CV_WINDOW_AUTOSIZE);
		// imshow("Blurred", blurredThresh);

		Canny(blurredThresh, edges, cannyLow, cannyLow*ratio, 3);
		// namedWindow("Canny Edges", CV_WINDOW_AUTOSIZE);
		// imshow("Canny Edges", edges);

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
				circle(image, *i, 1, Scalar(0, 255, 0), 3);
			}
		}

		imshow("Intersections", image);
		/*
		if (waitKey(30) == 27)
			break;
	}*/
	return edges;
}

void Panel::FindContours(Mat image)
{
	int low = 140;
	Mat grayImage;
	cvtColor(image, grayImage, CV_BGR2GRAY);
	// Mat dilated;
	// dilate(grayImage, dilated, Mat());
	Mat blurred;
	GaussianBlur(grayImage, blurred, Size(7, 7), 0, 0);
	Mat thresh;
	threshold(blurred, thresh, low, 255, THRESH_BINARY);
	namedWindow("Threshold", CV_WINDOW_KEEPRATIO);
	imshow("Threshold", thresh);
	showimgcontours(thresh, image);
	// namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	// imshow("Contours", thresh);
	namedWindow("Largest Contour", CV_WINDOW_KEEPRATIO);
	imshow("Largest Contour", image);
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
	params.minArea = (float)blobArea;

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

void Panel::CascadeClassify(string sImgPath, string sClassPath)
{
	if (!ShowImage(sImgPath, "Original"))
		return;

	detectAndDisplay(m_pPanel->m_Image, sClassPath);
}

void Panel::DetectFeatures(string scenePath, string objPath, bool exceedsBorder)
{
	if (!ShowImage(scenePath, "Scene"))
		return;

	MyFeatureDetector detector;
	Mat boundImg;
	if (!detector.Detect(scenePath, objPath, boundImg, exceedsBorder))
		return;

	// FindContours(boundImg);
	// Canny Edge and Hough Line Detection
	Mat edges = CannyDetection(boundImg);
}

void Panel::DrawOnBoard(string sImgPath)
{
	m_pPanel = new Panel;

	m_pPanel->m_Image = imread(sImgPath);
	
	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", m_pPanel->m_Image);

	setMouseCallback("Original", onMouseLocation, static_cast<void*>(&m_pPanel));

	bool found = false;

	found = findChessboardCorners(m_pPanel->m_Image, Size(9, 6), m_pPanel->corners,
		CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

	if (found){	Point corner1;
		corner1.x = (int)m_pPanel->corners[0].x;
		corner1.y = (int)m_pPanel->corners[0].y;
	
		Point corner2;
		corner2.x = (int)m_pPanel->corners[4].x;
		corner2.y = (int)m_pPanel->corners[4].y;

		line(m_pPanel->m_Image, corner1, corner2, CV_RGB(0, 0, 255), 2);

		Mat imgGray;
		cvtColor(m_pPanel->m_Image, imgGray, COLOR_BGR2GRAY);
		cornerSubPix(imgGray, m_pPanel->corners, Size(11, 11), Size(-1, -1),
			TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
		cout << "Corner 1: " << corner1 << endl;
		cout << "Corner 2: " << corner2 << endl;
		cout << "Subtraction: " << corner2 - corner1 << endl;
		cout << "Distance in pixels: " << norm(corner2 - corner1) << endl;
		cout << "Distance in cm " << norm(corner2 - corner1) * .2932 << endl << endl;
	}
	else{
		cout << "Checkerboard not found" << endl;
	}

}

void Panel::Perspective(string sImgPath, string sSelectedItem)
{
	m_pPanel = new Panel;
	
	cout << sSelectedItem << endl;

	m_pPanel->m_Image = imread(sImgPath);

	Point2f corner1;
	Point2f corner2;
	Point2f corner3;
	Point2f corner4;

	double width = 0;
	double length = 0;
	double ratio = 0; 

	if (sSelectedItem == "Checkerboard #10"){
		bool found = false;

		found = findChessboardCorners(m_pPanel->m_Image, Size(9, 6), m_pPanel->corners,
			CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

		Mat imgGray;
		cvtColor(m_pPanel->m_Image, imgGray, COLOR_BGR2GRAY);
		cornerSubPix(imgGray, m_pPanel->corners, Size(11, 11), Size(-1, -1),
			TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

		corner1.x = m_pPanel->corners[8].x;
		corner1.y = m_pPanel->corners[8].y;

		corner2.x = m_pPanel->corners[53].x;
		corner2.y = m_pPanel->corners[53].y;

		corner3.x = m_pPanel->corners[45].x;
		corner3.y = m_pPanel->corners[45].y;

		corner4.x = m_pPanel->corners[0].x;
		corner4.y = m_pPanel->corners[0].y;

		// Draw rectangle around checkerboard

		line(m_pPanel->m_Image, corner1, corner2, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner2, corner3, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner3, corner4, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner4, corner1, CV_RGB(0, 0, 255), 2);

		//circle(m_pPanel->m_Image, corner1, 10, CV_RGB(0, 0, 255), 2);
		//circle(m_pPanel->m_Image, corner2, 10, CV_RGB(0, 255, 0), 2);
		//circle(m_pPanel->m_Image, corner3, 10, CV_RGB(255, 0, 0), 2);
		//circle(m_pPanel->m_Image, corner4, 10, CV_RGB(100, 100, 100), 2);

		ratio = 8.0 / 5.0;
		width = norm(corner2 - corner1);
		length = ratio * width;

	}
	else if (sSelectedItem == "Checkerboard #6"){
		bool found = false;

		found = findChessboardCorners(m_pPanel->m_Image, Size(9, 6), m_pPanel->corners,
			CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

		Mat imgGray;
		cvtColor(m_pPanel->m_Image, imgGray, COLOR_BGR2GRAY);
		cornerSubPix(imgGray, m_pPanel->corners, Size(11, 11), Size(-1, -1),
			TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

		corner1.x = m_pPanel->corners[8].x;
		corner1.y = m_pPanel->corners[8].y;

		corner2.x = m_pPanel->corners[53].x;
		corner2.y = m_pPanel->corners[53].y;

		corner3.x = m_pPanel->corners[45].x;
		corner3.y = m_pPanel->corners[45].y;

		corner4.x = m_pPanel->corners[0].x;
		corner4.y = m_pPanel->corners[0].y;

		// Draw rectangle around checkerboard

		line(m_pPanel->m_Image, corner1, corner2, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner2, corner3, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner3, corner4, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner4, corner1, CV_RGB(0, 0, 255), 2);

		ratio = 8.0 / 5.0;
		width = norm(corner2 - corner1);
		length = ratio * width;
	}
	else if (sSelectedItem == "Panel #3"){
		corner1 = Point2f(1035, 475);
		corner2 = Point2f(1227, 392);
		corner3 = Point2f(1558, 788);
		corner4 = Point2f(1342, 904);

		// Draw rectangle around panel

		line(m_pPanel->m_Image, corner1, corner2, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner2, corner3, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner3, corner4, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner4, corner1, CV_RGB(0, 0, 255), 2);

		width = norm(corner3 - corner4);
		length = norm(corner2 - corner3);
	}

	vector<Point2f> panel_pts;
	vector<Point2f> rect_pts;
	panel_pts.push_back(corner1);
	panel_pts.push_back(corner2);
	panel_pts.push_back(corner3);
	panel_pts.push_back(corner4);
	rect_pts.push_back(Point2f(corner1.x, corner1.y));
	rect_pts.push_back(Point2f(corner1.x + (float)width, corner1.y));
	rect_pts.push_back(Point2f(corner1.x + (float)width, corner1.y + (float)length));
	rect_pts.push_back(Point2f(corner1.x, corner1.y + (float)length));
	
	// Draw new rectangle
	//line(m_pPanel->m_Image, rect_pts[0], rect_pts[1], CV_RGB(255, 0, 0), 2);
	//line(m_pPanel->m_Image, rect_pts[1], rect_pts[2], CV_RGB(255, 0, 0), 2);
	//line(m_pPanel->m_Image, rect_pts[2], rect_pts[3], CV_RGB(255, 0, 0), 2);
	//line(m_pPanel->m_Image, rect_pts[3], rect_pts[0], CV_RGB(255, 0, 0), 2);

	// Perspective Transorm
	Mat transmtx = getPerspectiveTransform(panel_pts, rect_pts);
	int offsetSize = 500;
	Mat transformed = Mat::zeros(m_pPanel->m_Image.cols + offsetSize, m_pPanel->m_Image.rows + offsetSize, CV_8UC3);
	warpPerspective(m_pPanel->m_Image, transformed, transmtx, transformed.size());

	Mat subImg(transformed, Rect((int)corner1.x, (int)corner1.y, (int)width, (int)length));

	namedWindow("Original", WINDOW_NORMAL);
	imshow("Original", m_pPanel->m_Image);
	namedWindow("Warped", WINDOW_AUTOSIZE);
	imshow("Warped", transformed);
	namedWindow("SubImage", WINDOW_AUTOSIZE);
	imshow("SubImage", subImg);

//	imwrite("PersCorrCheck10.jpg", subImg);
}

void Panel::Rectification(string sImgPath, string sSelectedItem)
{
	m_pPanel = new Panel;

	cout << sSelectedItem << endl;

	m_pPanel->m_Image = imread(sImgPath);

	Point2f corner1;
	Point2f corner2;
	Point2f corner3;
	Point2f corner4;

	double width = 0;
	double length = 0;
	double ratio = 0;

	// Not fixed for rectification
	if (sSelectedItem == "Checkerboard #10"){
		bool found = false;

		found = findChessboardCorners(m_pPanel->m_Image, Size(9, 6), m_pPanel->corners,
			CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

		Mat imgGray;
		cvtColor(m_pPanel->m_Image, imgGray, COLOR_BGR2GRAY);
		cornerSubPix(imgGray, m_pPanel->corners, Size(11, 11), Size(-1, -1),
			TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

		corner1.x = m_pPanel->corners[8].x;
		corner1.y = m_pPanel->corners[8].y;

		corner2.x = m_pPanel->corners[53].x;
		corner2.y = m_pPanel->corners[53].y;

		corner3.x = m_pPanel->corners[45].x;
		corner3.y = m_pPanel->corners[45].y;

		corner4.x = m_pPanel->corners[0].x;
		corner4.y = m_pPanel->corners[0].y;

		// Draw rectangle around checkerboard

		line(m_pPanel->m_Image, corner1, corner2, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner2, corner3, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner3, corner4, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner4, corner1, CV_RGB(0, 0, 255), 2);

		//circle(m_pPanel->m_Image, corner1, 10, CV_RGB(0, 0, 255), 2);
		//circle(m_pPanel->m_Image, corner2, 10, CV_RGB(0, 255, 0), 2);
		//circle(m_pPanel->m_Image, corner3, 10, CV_RGB(255, 0, 0), 2);
		//circle(m_pPanel->m_Image, corner4, 10, CV_RGB(100, 100, 100), 2);

		ratio = 8.0 / 5.0;
		width = norm(corner2 - corner1);
		length = ratio * width;

	}
	else if (sSelectedItem == "Checkerboard #6"){
		bool found = false;

		found = findChessboardCorners(m_pPanel->m_Image, Size(9, 6), m_pPanel->corners,
			CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

		Mat imgGray;
		cvtColor(m_pPanel->m_Image, imgGray, COLOR_BGR2GRAY);
		cornerSubPix(imgGray, m_pPanel->corners, Size(11, 11), Size(-1, -1),
			TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

		corner1.x = m_pPanel->corners[45].x;
		corner1.y = m_pPanel->corners[45].y;

		corner2.x = m_pPanel->corners[53].x;
		corner2.y = m_pPanel->corners[53].y;

		corner3.x = m_pPanel->corners[0].x;
		corner3.y = m_pPanel->corners[0].y;

		corner4.x = m_pPanel->corners[8].x;
		corner4.y = m_pPanel->corners[8].y;

		// Draw rectangle around checkerboard

		line(m_pPanel->m_Image, corner1, corner2, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner2, corner4, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner4, corner3, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner3, corner1, CV_RGB(0, 0, 255), 2);

		ratio = 8.0 / 5.0;
		width = norm(corner3 - corner1);
		length = ratio * width;
	}
	// Not fixed for rectification
	else if (sSelectedItem == "Panel #3"){
		corner1 = Point2f(1035, 475);
		corner2 = Point2f(1227, 392);
		corner3 = Point2f(1558, 788);
		corner4 = Point2f(1342, 904);

		// Draw rectangle around panel

		line(m_pPanel->m_Image, corner1, corner2, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner2, corner3, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner3, corner4, CV_RGB(0, 0, 255), 2);
		line(m_pPanel->m_Image, corner4, corner1, CV_RGB(0, 0, 255), 2);

		width = norm(corner2 - corner1);
		length = norm(corner2 - corner3);
	}

	vector<Point2f> panel_pts;
	vector<Point2f> rect_pts;
	panel_pts.push_back(corner1);
	panel_pts.push_back(corner2);
	panel_pts.push_back(corner3);
	panel_pts.push_back(corner4);
	rect_pts.push_back(Point2f(0, 0));
	rect_pts.push_back(Point2f(length, 0));
	rect_pts.push_back(Point2f(0, width));
	rect_pts.push_back(Point2f(length, width));

	// Draw new rectangle
	//line(m_pPanel->m_Image, rect_pts[0], rect_pts[1], CV_RGB(255, 0, 0), 2);
	//line(m_pPanel->m_Image, rect_pts[1], rect_pts[2], CV_RGB(255, 0, 0), 2);
	//line(m_pPanel->m_Image, rect_pts[2], rect_pts[3], CV_RGB(255, 0, 0), 2);
	//line(m_pPanel->m_Image, rect_pts[3], rect_pts[0], CV_RGB(255, 0, 0), 2);

	// Perspective Transorm
	Mat transmtx = getPerspectiveTransform(panel_pts, rect_pts);
	int offsetSize = 500;
	Mat transformed = Mat::zeros(m_pPanel->m_Image.cols + offsetSize, m_pPanel->m_Image.rows + offsetSize, CV_8UC3);
	warpPerspective(m_pPanel->m_Image, transformed, transmtx, transformed.size());

//	Mat subImg(transformed, Rect(corner1.x, corner1.y, width, length));

	namedWindow("Original", WINDOW_NORMAL);
	imshow("Original", m_pPanel->m_Image);
	namedWindow("Warped", WINDOW_AUTOSIZE);
	imshow("Warped", transformed);
//	namedWindow("SubImage", WINDOW_AUTOSIZE);
//	imshow("SubImage", subImg);

//	imwrite("PersCorrCheck10.jpg", subImg);
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
	int counter = 1;

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
		
		namedWindow("Image View" + to_string(counter), WINDOW_NORMAL);
		resizeWindow("Image View" + to_string(counter), 640, 480);
		imshow("Image View" + to_string(counter), view);
		char key = (char)waitKey(s.inputCapture.isOpened() ? 50 : s.delay);

		cout << "Image " << to_string(counter) << " Completed" << endl;
		counter++;

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

		mainMap1 = map1;
		mainMap2 = map2;

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

void Panel::CalibrateCameraNoOutput(string sFilePath)
{
	help();

	cout << "No Picture Output" << endl;

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
	int counter = 1;

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
		
/*		//------------------------------ Show image and check for input commands -------------------
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
*/
		cout << "Image " << to_string(counter) << " Completed" << endl;
		counter++;
	}

/*	// -----------------------Show the undistorted image for the image list ------------------------
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
*/
	// -----------------------Calculate Maps ------------------------

	Mat view, rview, map1, map2;

	initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
		getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
		imageSize, CV_16SC2, map1, map2);

	mainMap1 = map1;
	mainMap2 = map2;

	// Just for testing DrawOnBoard

	mainCameraMatrix = cameraMatrix;
	mainDistCoeffs = distCoeffs;
	//	return 0;

}

void Panel::CalibrateCameraFisheyeNoOutput(string sFilePath)
{
	help();

	cout << "NO OUTPUT" << endl;

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
			if (runCalibrationFisheyeAndSave(s, imageSize, cameraMatrix, distCoeffs, imagePoints))
				mode = CALIBRATED;
			else
				mode = DETECTION;
		}
		if (view.empty())          // If there are no more images stop the loop
		{
			// if calibration threshold was not reached yet, calibrate now
			if (mode != CALIBRATED && !imagePoints.empty())
				runCalibrationFisheyeAndSave(s, imageSize, cameraMatrix, distCoeffs, imagePoints);
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
			fisheye::undistortImage(temp, view, cameraMatrix, distCoeffs);
		}
		//! [output_undistorted]

		/*		//------------------------------ Show image and check for input commands -------------------
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
		*/
	}

	/*	// -----------------------Show the undistorted image for the image list ------------------------
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
	*/
	// -----------------------Calculate Maps ------------------------

	Mat R, P, view, rview, map1, map2;

	fisheye::estimateNewCameraMatrixForUndistortRectify(cameraMatrix, distCoeffs, imageSize, Mat(), P);

	R.convertTo(R, CV_64F);

	fisheye::initUndistortRectifyMap(cameraMatrix, distCoeffs, R, P,
		imageSize, CV_16SC2, map1, map2);

	mainMap1 = map1;
	mainMap2 = map2;


	//	return 0;

}

