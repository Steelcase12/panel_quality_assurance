#include "FeatureDetector.h"

MyFeatureDetector::MyFeatureDetector(string scene, string obj) {

	// Load images
	full_scene = imread(scene);
	if (!full_scene.data) {
		std::cout << " --(!) Error reading image " << scene << std::endl;
		// Error
	}

	Mat object = imread(obj);
	if (!object.data) {
		std::cout << " --(!) Error reading image " << obj << std::endl;
		// Error
	}
	// Resize image If Necessary
	// Size size(400, 400);
	// resize(object, object, size);

	// SlidingWindow() is only necessary when detecting 
	//	more than feature in a single image
	// IMPORTANT: Parameters n_rows, row_step, n_cols, & col_step
	//	may need to be adjusted according to the position of 
	//	the features in the image. The current settings assume
	//	there are 2 features: one at the top, and one at the 
	//	bottom of the image
	outImg = full_scene;
	n_rows = full_scene.cols;
	row_step = n_rows / 2;
	n_cols = full_scene.rows / 3;
	col_step = n_cols / 2;
	SlidingWindow(object);

	// When only detecting one feature in an image,
	//	comment out SlidingWindow() above and un-comment
	//	FindObject below
	// IMPORTANT: The third parameter is the threshold value
	//	used by feature decection. It may need to be adjusted 
	//  according to the template used for feature detection 
	//  or the visibility of the feature that is being dectected
	// FindObject(object, full_scene, 100, Scalar(255, 0, 0));

	// The below lines are for debugging the points that are
	//	derived by feature detection to be used as the top 
	//	and bottom boundaries of the ROI return value
	/*namedWindow("Match", CV_WINDOW_KEEPRATIO);
	line(outImg, Point(0, topPoint), Point(outImg.cols, topPoint), Scalar(255, 0, 0), 4);
	line(outImg, Point(0, bottomPoint), Point(outImg.cols, bottomPoint), Scalar(255, 0, 0), 4);
	imshow("Match", outImg);*/

	// The below lines will print out the image after the ROI
	//	(determined by feature detection) is applied. The ROI 
	//  is what is being passed back to the main function
	Rect roi(Point(0, topPoint), Point(full_scene.cols, bottomPoint));
	Mat bound_image = full_scene(roi);
	namedWindow("Bound Image", CV_WINDOW_AUTOSIZE);
	imshow("Bound Image", bound_image);

	// Use the waitkey below when a pause is needed for 
	//	debugging. It will ensure the windows created stay
	//	up until a key is pressed.
	// waitkey(0);
}

MyFeatureDetector::~MyFeatureDetector()
{

}

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

			// Mat drawResults = full_scene.clone();

			/* Draw only rectangle
			rectangle(drawResults, windows, Scalar(255), 1, 8, 0);
			// Draw grid
			// rectangle(drawGrid, windows, Scalar(255), 1, 8, 0);

			/* Show rectangle
			namedWindow("Step 2 draw Rectangle", WINDOW_AUTOSIZE);
			imshow("Step 2 draw Rectangle", drawResults);
			waitKey(50);
			imwrite("Step2.jpg", drawResults);

			/* Show grid
			namedWindow("Step 3 Show Grid", WINDOW_AUTOSIZE);
			imshow("Step 3 Show Grid", drawGrid);
			waitKey(50);
			imwrite("Step3.jpg", drawGrid);
			*/

			// Show roi
			// namedWindow("Step 4 Draw selected Roi", WINDOW_AUTOSIZE);
			// imshow("Step 4 Draw selected Roi", roi);
			// waitKey(100);
			// imwrite("Step4.JPG", roi);

			////////////////////////////////////////
			// End of Sliding Window Debugging Code
			////////////////////////////////////////
		}
	}
}

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

	/*
	drawMatches(objectP,keypointsO,sceneP,keypointsS,matches,outImg,Scalar::all(-1), Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	drawKeypoints(objectP,keypointsO,objectP,Scalar(0,0,255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	namedWindow("SURF");
	imshow("SURF",objectP);
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

		Mat H = findHomography(obj, scene_vec, CV_RANSAC);

		//-- Get the corners from the image_1 ( the object to be "detected" )
		std::vector<Point2f> obj_corners(4);
		obj_corners[0] = cvPoint(0, 0);
		obj_corners[1] = cvPoint(object.cols, 0);
		obj_corners[2] = cvPoint(object.cols, object.rows);
		obj_corners[3] = cvPoint(0, object.rows);
		std::vector<Point2f> scene_corners(4);

		if (!H.empty())
			perspectiveTransform(obj_corners, scene_corners, H);

		//-- Draw lines between the corners (the mapped object in the scene - image_2 )

		line(outImg, Point((int)scene_corners[0].x + col, (int)scene_corners[0].y + row),
			Point((int)scene_corners[1].x + col, (int)scene_corners[1].y + row), Scalar(255, 255, 0), 2); //TOP line
		line(outImg, Point((int)scene_corners[1].x + col, (int)scene_corners[1].y + row),
			Point((int)scene_corners[2].x + col, (int)scene_corners[2].y + row), color, 2);
		line(outImg, Point((int)scene_corners[2].x + col, (int)scene_corners[2].y + row),
			Point((int)scene_corners[3].x + col, (int)scene_corners[3].y + row), color, 2);
		line(outImg, Point((int)scene_corners[3].x + col, (int)scene_corners[3].y + row),
			Point((int)scene_corners[0].x + col, (int)scene_corners[0].y + row), color, 2);

		if (topPoint == NULL)
			if (scene_corners[2].y < scene_corners[3].y)
				topPoint = (int)scene_corners[2].y + row;
			else
				topPoint = (int)scene_corners[3].y + row;
		else
			if (scene_corners[0].y < scene_corners[1].y)
				bottomPoint = (int)scene_corners[0].y + row;
			else
				bottomPoint = (int)scene_corners[1].y + row;
	}
	// else 
	//	cout << "OBJECT NOT FOUND!" << endl;

	duration = static_cast<double>(cv::getTickCount()) - duration;
	duration = (duration / cv::getTickFrequency());

	//cout <<  << endl;
	// cout << "Good matches found: " << good_matches.size() << endl;
	// cout << "Algorithm duration: " << duration << " seconds" << endl << "--------------------------------------" << endl;

	// drawing the results
	// namedWindow("matches", CV_WINDOW_KEEPRATIO);
	// Mat img_matches;
	// drawMatches(object, keypointsO, full_scene, keypointsS, good_matches, img_matches);
	// imshow("matches", img_matches);
	// waitKey(100);
}