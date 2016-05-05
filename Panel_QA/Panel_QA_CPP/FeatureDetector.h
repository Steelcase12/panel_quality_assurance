//////////////////////////////////////////////////////////////
// FeatureDetector.h Description:
//  This file contains the code which detects the specified
//  feature in an image. When the feature is found a region
//  of interest (a rectangle) is created for the original
//  image to reduce the amount of noise in the panel 
//  environment. This file also contains the code which finds
//  the pixels to length conversion based on the feature's 
//  actual size specified in Settings.xml.
//////////////////////////////////////////////////////////////
#pragma once
#pragma comment(lib,"user32.lib")
// TODO: Add dialog options for these
// Uncomment this line to debug feature detection
// #define DEBUG_FEATURES 1
// Uncomment this line to debug the sliding window
// #define DEBUG_SLIDING_WINDOW 1

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d.hpp"
#include <iostream>
#include <algorithm>
#include "include.h"

using namespace cv;
using namespace std;

class MyFeatureDetector
{
public:
	MyFeatureDetector();
	~MyFeatureDetector();
	void SlidingWindow(Mat object);
	void FindObject(Mat objectP, Mat scene, int minHessian, Scalar color, int row, int col);
	bool Detect(Mat scene, string obj, Rect &roi, float feature_height_cm, float feature_width_cm, 
		float &conversion, bool exceedsBorder, bool featureRotated, bool showImg = true);
private:
	Mat full_scene, outImg;
	Mat m_Homography;
	float m_FeatureHeightCM;
	float m_FeatureWidthCM;
	float m_conversionRate = 0;
	// Top and Bottom points of new ROI
	int topPoint = 0;
	int bottomPoint = 0;
	int leftPoint = 0;
	int rightPoint = 0;
	// Sliding window parameters
	int n_rows, n_cols;
	// Step of each window
	int row_step, col_step;
	// Variable which tells the detector to use the top
	// of the top feature and the bottom of the bottom
	// feature as the border of the new ROI
	bool m_outerEdges;
	bool m_bFeatureRotated;
};

// Constructor
MyFeatureDetector::MyFeatureDetector() 
{
}

// Destructor
MyFeatureDetector::~MyFeatureDetector()
{
}

// Main function for MyFeatureDetector
bool MyFeatureDetector::Detect(Mat scene, string obj, Rect &roi, float feature_height_cm, float feature_width_cm, 
	float &conversion, bool exceedsBorder, bool featureRotated, bool showImg)
{
    // Set the member variables
	// Load images
	full_scene = scene;
	m_FeatureHeightCM = feature_height_cm;
	m_FeatureWidthCM = feature_width_cm;
	m_bFeatureRotated = featureRotated;

	Mat object = imread(obj);
	if (!object.data) {
		std::cout << " --(!) Error reading image " << obj << std::endl;
		// Error
	}
	// Resize image If Necessary
	// Size size(400, 400);
	// resize(object, object, size);

    ////////////////////////////////////////////////////////////////
	// SlidingWindow() is only necessary when detecting 
	//	more than feature in a single image
	// IMPORTANT: Parameters n_rows, row_step, n_cols, & col_step
	//	may need to be adjusted according to the position of 
	//	the features in the image. The current settings assume
	//	there are 2 features: one at the top, and one at the 
	//	bottom of the image
    ////////////////////////////////////////////////////////////////
	outImg = full_scene;
	n_rows = full_scene.cols;
	n_cols = full_scene.rows / 2;
	row_step = n_cols;
	col_step = n_rows;
	SlidingWindow(object);
	// Pass back the conversion rate that we found in FindObject()
	if (m_conversionRate)
		conversion = m_conversionRate;

    ////////////////////////////////////////////////////////////////////
	// When only detecting one feature in an image,
	//	comment out SlidingWindow() above and un-comment
	//	FindObject below
	// IMPORTANT: The third parameter is the threshold value
	//	used by feature decection. It may need to be adjusted 
	//  according to the template used for feature detection 
	//  or the visibility of the feature that is being dectected
    ///////////////////////////////////////////////////////////////////
	// FindObject(object, full_scene, 100, Scalar(255, 0, 0), 0, 0);

    ///////////////////////////////////////////////////////////////////
	// The below lines are for debugging the points that are
	//	derived by feature detection to be used as the top
	//	and bottom boundaries of the ROI return value
    //  Uncomment DEBUG_FEATURES=1 at the top of this file to debug
    //  feature detection parameters.
    ///////////////////////////////////////////////////////////////////
#ifdef DEBUG_FEATURES
	namedWindow("Match", CV_WINDOW_KEEPRATIO);
	line(outImg, Point(0, topPoint), Point(outImg.cols, topPoint), Scalar(255, 0, 0), 4);
	line(outImg, Point(0, bottomPoint), Point(outImg.cols, bottomPoint), Scalar(255, 0, 0), 4);
	line(outImg, Point(leftPoint, 0), Point(leftPoint, outImg.rows), Scalar(255, 0, 0), 4);
	line(outImg, Point(rightPoint, 0), Point(rightPoint, outImg.rows), Scalar(255, 0, 0), 4);
	imshow("Match", outImg);
#endif

    ///////////////////////////////////////////////////////////////
	// The below lines will print out the image after the ROI
	//	(determined by feature detection) is applied. The ROI 
	//  is what is being passed back to the main function
    ///////////////////////////////////////////////////////////////
	if (topPoint || bottomPoint) {
        // If exceedsBorder is true, expand the border to the far left
        //  and far right points of the image
		if (exceedsBorder){
			leftPoint = 0;
			rightPoint = full_scene.cols;
		}
        // If top and bottom features are found
		if (topPoint && bottomPoint){
			// Checks to ensure points don't exceed image border, this causes a crash
			if (topPoint < 0) topPoint = 0;
			if (leftPoint < 0) leftPoint = 0;
			if (bottomPoint > full_scene.rows) bottomPoint = full_scene.rows;
			if (rightPoint > full_scene.cols) rightPoint = full_scene.cols;
			// Set the Region of Interest
			roi = Rect(Point(leftPoint, topPoint), Point(rightPoint, bottomPoint));
			ShowMessage("Top and bottom features found. \nBoundary successfully set.");
		}
		// Only top feature found
		else if (topPoint){
			// Checks to ensure points don't exceed image border, this causes a crash
			if (topPoint < 0) topPoint = 0;
			if (leftPoint < 0) leftPoint = 0;
			// Set the Region of Interest
			roi = Rect(Point(leftPoint, topPoint), Point(full_scene.rows, full_scene.cols));
			ShowMessage("Only top feature found. \nThe boundary is set, but will be more refined if both features are found.");
		}
		// Only bottom feature found
		else if (bottomPoint){
			// Checks to ensure points don't exceed image border, this causes a crash
			if (bottomPoint > full_scene.rows) bottomPoint = full_scene.rows;
			if (rightPoint > full_scene.cols) rightPoint = full_scene.cols;
			// Set the Region of Interest
			roi = Rect(Point(0, 0), Point(rightPoint, bottomPoint));
			ShowMessage("Only bottom feature found. \nThe boundary is set, but will be more refined if both features are found.");
		}
		Mat bound_image;
        // If we found a region of interest, show the new bound image
		if (roi.width)
		{
			bound_image = full_scene(roi);
			if (showImg){
				namedWindow("Bound Image", CV_WINDOW_NORMAL);
				imshow("Bound Image", bound_image);
			}
		}
	}
    // No features found
	else {
		ShowMessage("No features found.");
		return false;
	}

    /////////////////////////////////////////////////////////
	// Use the waitkey() below when a pause is needed for 
	//	debugging. It will ensure the windows created stay
	//	up until a key is pressed.
    /////////////////////////////////////////////////////////
	// waitkey(0);

	return true;
}

////////////////////////////////////////////////////////////
// MyFeatureDetector::SlidingWindow Description
//  This function is used to create a sliding window to
//  allow us to find multiple (right now 2) features in a 
//  single image. This function calls FindObject() passing
//  in a portion of the full image and numbers for the row
//  and column which allows FindObject to locate the feature
//  in the full image rather than just a portion of it. 
////////////////////////////////////////////////////////////
void MyFeatureDetector::SlidingWindow(Mat object)
{
	// Un-comment the below line when debugging 
	//	SlidingWindow(). It will show the image with
	//  all of the sliding windows on it.
	Mat drawGrid = full_scene.clone();
	// Cycle row step
	for (int row = 0; row <= full_scene.rows - n_cols; row += row_step)
	{
		// Cycle col step
		for (int col = 0; col <= full_scene.cols - n_rows; col += col_step)
		{
			// Resulting window
			Rect windows(col, row, n_rows, n_cols);

			///////////////////////////////////
			// Begin Feature Detector with ROI
			///////////////////////////////////
			Mat roi = full_scene(windows);
			FindObject(object, roi, 100, Scalar(255, 0, 0), row, col);
			////////////////////////////////////
			// End of Feature Detector with ROI
			////////////////////////////////////

			///////////////////////////////////////
			// Begin Sliding Window Debugging Code
			///////////////////////////////////////
            // Uncomment DEBUG_SLIDING_WINDOW at the top of this file
            //  to visualize the steps used for the sliding window
#ifdef DEBUG_SLIDING_WINDOW
			Mat drawResults = full_scene.clone();

			// Draw only rectangle
			rectangle(drawResults, windows, Scalar(255), 1, 8, 0);
			// Draw grid
			rectangle(drawGrid, windows, Scalar(255), 10, 8, 0);

			// Show rectangle
			namedWindow("Step 2 draw Rectangle", CV_WINDOW_KEEPRATIO);
			imshow("Step 2 draw Rectangle", drawResults);
			waitKey(50);
			imwrite("Step2.jpg", drawResults);


			// Show grid
			namedWindow("Step 3 Show Grid", CV_WINDOW_KEEPRATIO);
			imshow("Step 3 Show Grid", drawGrid);
			waitKey(50);
			imwrite("Step3.jpg", drawGrid);

			// Show roi
			// namedWindow("Step 4 Draw selected Roi", WINDOW_AUTOSIZE);
			// imshow("Step 4 Draw selected Roi", roi);
			// waitKey(100);
			// imwrite("Step4.JPG", roi);*/
#endif

			////////////////////////////////////////
			// End of Sliding Window Debugging Code
			////////////////////////////////////////
		}
	}
}

////////////////////////////////////////////////////////////
// MyFeatureDetector::FindObject Description:
//  This is the function which finds the feature in an 
//  image using BRISK feature detector and BRISK feature
//  extractor. The parameters are object (the feature), 
//  scene (the full image), minHessian (a parameter used 
//  with feature detection), color (used for the boxes 
//  drawn around the features during debugging, row
//  (indicating the sliding window row), and column 
//  (indicating the sliding window column).
////////////////////////////////////////////////////////////
void MyFeatureDetector::FindObject(Mat object, Mat scene, int minHessian, Scalar color, int row, int col)
{
	//vector of keypoints	
	vector<cv::KeyPoint> keypointsO;
	vector<cv::KeyPoint> keypointsS;
	// cout << "Looking for object...\n";
	// Start the timer for performance tracking
	double duration;
	duration = static_cast<double>(cv::getTickCount());

	///////////////////////////////////////////////////////////////
	// FEATURE DETECTORS
	///////////////////////////////////////////////////////////////
	// These are feature detectors which we experimented with.
	//	BRISK seemed to detect more corners and more acurately
	//	so we stuck with it. Keep in mind, SurfFeatureDetector
	//  is patented so it is not free to use without permission!
	///////////////////////////////////////////////////////////////
	// Ptr<FastFeatureDetector> detector = FastFeatureDetector::create();
	// Ptr<ORB> detector = ORB::create();
	// Ptr<SurfFeatureDetector> detector = SurfFeatureDetector::create(minHessian);
	// Ptr<MSER> detector = MSER::create();
	Ptr<BRISK> detector = BRISK::create(minHessian);

	////////////////////////////////////////////////////////////////
	// DESCRIPTION EXTRACTORS
	////////////////////////////////////////////////////////////////
	// These are feature descriptors which we experimented with.
	//	BRISK seemed to detect more corners and more acurately
	//	so we stuck with it. Keep in mind, SurfDescriptionExtractor
	//  is patented so it is not free to use without permission!
	////////////////////////////////////////////////////////////////
	// Ptr<FREAK> extractor = FREAK::create();
	// Ptr<ORB> extractor = ORB::create();
	// Ptr<MSER> extractor = MSER::create();
	// Ptr<SurfDescriptorExtractor> extractor = SurfDescriptorExtractor::create();
	Ptr<BRISK> extractor = BRISK::create();

	///////////////////////////////////////////////////////////////
	// FEATURE MATCHERS
	///////////////////////////////////////////////////////////////
	// These are feature matchers which we experimented with.
	//	Certain matchers only work with certain feature detectors
	//  and description extractors. So if you change detectors or
	//  descriptors, make sure you use the appropriate matcher.
	///////////////////////////////////////////////////////////////
	// FlannBasedMatcher matcher;  
	BFMatcher matcher(NORM_HAMMING);

	// Step 1: Detect Keypoints
	detector->detect(object, keypointsO);
	detector->detect(scene, keypointsS);

	//-- Step 2: Calculate descriptors (feature vectors)
	Mat descriptors_object, descriptors_scene;
	extractor->compute(object, keypointsO, descriptors_object);
	extractor->compute(scene, keypointsS, descriptors_scene);

	//-- Step 3: Matching descriptor vectors using Brute Force matcher
	std::vector< DMatch > matches1, matches2;
	matcher.match(descriptors_object, descriptors_scene, matches1);
	matcher.match(descriptors_scene, descriptors_object, matches2);

	vector< DMatch > good_matches;

	//////////////////////////////////////////////////////////////
	// MATCH FILTERING
	//////////////////////////////////////////////////////////////
	// We experimented with a couple different ways of 
	//  filtering out bad matches from the good. One way
	//  is the Ratio Test which is done by determining
	//  the shortest distance between matches and leaving the 
	//  ones that are very close to each other. This worked okay 
	//  in some situations, but not as good in others. That code 
	//  is commented out below. 
	// The method we decided to go with is called Cross-Checking.
	//  This is done by checking the matches from scene to object
	//  then checking from object to scene. The matches that are in
	//  both are considered as good.
	////////////////////////////////////////////////////////////////

	// Ratio Test 
	/*
	double max_dist = 0; double min_dist = 150;
	double dist;
	// Quick calculation of min and max distances between keypoints
	for(int i=0; i<descriptors_object.rows; i++)
	{
	if (matches1.size()){
	dist = matches1[i].distance;
	if (dist < min_dist) min_dist = dist;
	if (dist > max_dist) max_dist = dist;
	}
	}
	cout << "-- Max Dist: " << max_dist << endl;
	cout << "-- Min Dist: " << min_dist << endl;

	for(int i = 0; i < descriptors_object.rows; i++)
	{
	if (matches1.size())
	if (matches1[i].distance < 2 * min_dist)
	good_matches.push_back(matches1[i]);
	}*/

	// Cross-checking
	for (size_t i = 0; i < matches1.size(); i++)
	{
		DMatch forward = matches1[i];
		DMatch backward = matches2[forward.trainIdx];
		if (backward.trainIdx == forward.queryIdx)
			good_matches.push_back(forward);
	}

    // These lines can be used for debugging the features found
	/*
	drawMatches(object,keypointsO,scene,keypointsS,good_matches,outImg,Scalar::all(-1), Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	drawKeypoints(object,keypointsO,object,Scalar(0,0,255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	namedWindow("BRISK");
	imshow("BRISK",object);
	*/

	//-- Localize the object

	if (good_matches.size() >= 5)
	{
		// cout << "OBJECT FOUND!" << endl;
		std::vector<Point2f> obj;
		std::vector<Point2f> scene_vec;

		for (unsigned int i = 0; i < good_matches.size(); i++)
		{
			//-- Get the keypoints from the good matches
			obj.push_back(keypointsO[good_matches[i].queryIdx].pt);
			scene_vec.push_back(keypointsS[good_matches[i].trainIdx].pt);
		}

		// TODO: Pass this image back to Panel.cpp to perspective
		//  transform every image 
        //  NOTE: This Homography is never actually used because 
        //  we couldn't get it to work properly
		m_Homography = findHomography(obj, scene_vec, CV_RANSAC);

		//-- Get the corners from the image_1 ( the object to be "detected" )
		std::vector<Point2f> obj_corners(4);
		obj_corners[0] = cvPoint(0, 0);
		obj_corners[1] = cvPoint(object.cols, 0);
		obj_corners[2] = cvPoint(object.cols, object.rows);
		obj_corners[3] = cvPoint(0, object.rows);
		std::vector<Point2f> scene_corners(4);

		// TODO: Use this function in Panel.cpp with the homography that we find
		if (!m_Homography.empty())
			perspectiveTransform(obj_corners, scene_corners, m_Homography);
        ////////////////////////////////////////////////////////////////////////
        // row == 0 means to use the top feature
        // So we are using the top feature to find the length conversion rate
        ////////////////////////////////////////////////////////////////////////
		if (row == 0)
		{
			// Get pixels to lenth conversion
			float height = (float)norm(scene_corners[1] - scene_corners[2]);
			float width = (float)norm(scene_corners[0] - scene_corners[1]);
			float ratio = m_FeatureWidthCM / m_FeatureHeightCM;
			// Conversion in Pixels/Centimeter
			// The height and width of the feature in cm's
			// are set in the settings file
			if (m_bFeatureRotated)
				m_conversionRate = height / m_FeatureHeightCM;
			else
				m_conversionRate = width / m_FeatureWidthCM;
		}

		//-- Draw lines between the corners (the mapped object in the scene - image_2 )
#ifdef DEBUG_FEATURES
		line(outImg, Point((int)scene_corners[0].x + col, (int)scene_corners[0].y + row),
			Point((int)scene_corners[1].x + col, (int)scene_corners[1].y + row), Scalar(255, 255, 0), 2); //TOP line
		line(outImg, Point((int)scene_corners[1].x + col, (int)scene_corners[1].y + row),
			Point((int)scene_corners[2].x + col, (int)scene_corners[2].y + row), color, 2);
		line(outImg, Point((int)scene_corners[2].x + col, (int)scene_corners[2].y + row),
			Point((int)scene_corners[3].x + col, (int)scene_corners[3].y + row), color, 2);
		line(outImg, Point((int)scene_corners[3].x + col, (int)scene_corners[3].y + row),
			Point((int)scene_corners[0].x + col, (int)scene_corners[0].y + row), color, 2);
#endif

		///////////////////////////////////////////////////////
		// This portion of the code is the math used
		//  for finding the corners of the feature detected
		///////////////////////////////////////////////////////

		// This is the top of the Sliding Window
		if (row == 0){
			// Find the lowest value for topPoint
			int temp1 = (scene_corners[0].y < scene_corners[1].y) ? (int)scene_corners[0].y : (int)scene_corners[1].y;
			int temp2 = (scene_corners[2].y < temp1) ? (int)scene_corners[2].y : temp1;
			topPoint = (scene_corners[3].y < temp2) ? (int)scene_corners[3].y : temp2;
			// Find the lowest value for leftPoint
			int temp3 = (scene_corners[0].x < scene_corners[1].x) ? (int)scene_corners[0].x : (int)scene_corners[1].x;
			int temp4 = (scene_corners[2].x < temp3) ? (int)scene_corners[2].x : temp3;
			leftPoint = (scene_corners[3].x < temp4) ? (int)scene_corners[3].x : temp4;
			leftPoint += col;
		}
		// This is the bottom of the Sliding Window
		else{
			// Find the highest value for bottomPoint
			int temp1 = (scene_corners[0].y > scene_corners[1].y) ? (int)scene_corners[0].y : (int)scene_corners[1].y;
			int temp2 = (scene_corners[2].y > temp1) ? (int)scene_corners[2].y : temp1;
			bottomPoint = (scene_corners[3].y > temp2) ? (int)scene_corners[3].y : temp2;
			bottomPoint += row;
			// Find the highest value for rightPoint
			int temp3 = (scene_corners[0].x > scene_corners[1].x) ? (int)scene_corners[0].x : (int)scene_corners[1].x;
			int temp4 = (scene_corners[2].x > temp3) ? (int)scene_corners[2].x : temp3;
			rightPoint = (scene_corners[3].x > temp4) ? (int)scene_corners[3].x : temp4;
			rightPoint += col;
		}
	}
	// else 
	//	cout << "OBJECT NOT FOUND!" << endl;

    // Performance evaluation if needed
	duration = static_cast<double>(cv::getTickCount()) - duration;
	duration = (duration / cv::getTickFrequency());

	//cout <<  << endl;
	// cout << "Good matches found: " << good_matches.size() << endl;
	// cout << "Algorithm duration: " << duration << " seconds" << endl << "--------------------------------------" << endl;

	// drawing the results
#ifdef DEBUG_FEATURES
	namedWindow("matches", CV_WINDOW_KEEPRATIO);
	Mat img_matches;
	drawMatches(object, keypointsO, full_scene, keypointsS, good_matches, img_matches);
	imshow("matches", img_matches);
	waitKey(100);
#endif
}