include "cameramove.h"

////CS480
////Project 1
////Motion Tracking with OpenCV
////Lucas, Laurin, and Tom
////10/21/15

////TUTORIALS
///*
//http://www.pyimagesearch.com/2015/05/25/basic-motion-detection-and-tracking-with-python-and-opencv/
//http://docs.opencv.org/doc/tutorials/imgproc/shapedescriptors/bounding_rects_circles/bounding_rects_circles.html
//https://dl.dropboxusercontent.com/u/28096936/tuts/motionTrackingTut/finalCode/motionTracking.cpp
//*/

//CameraMove::CameraMove()
//{

//    //Lucas' Target code

//    //some boolean variables for added functionality
//    bool objectDetected = false;
//    //these two can be toggled by pressing 'd' or 't'
//    bool debugMode = false;
//    bool trackingEnabled = false;
//    //pause and resume code
//    bool pause = false;
//    //set up the matrices that we will need
//    //the two frames we will be comparing
//    Mat frame1, frame2;
//    //their grayscale images (needed for absdiff() function)
//    Mat grayImage1, grayImage2;
//    //resulting difference image
//    Mat differenceImage;
//    //thresholded difference image (for use in findContours() function)
//    Mat thresholdImage;
//    //video capture object.
//    //VideoCapture capture;
//    cv::VideoCapture stream1(0);
//    if (!stream1.isOpened()) {
//        cout << "Cannot open camera." << endl;
//    }

//    while (1) {

//        //read first frame
//        stream1.read(frame1);
//        //convert frame1 to gray scale for frame differencing
//        cvtColor(frame1, grayImage1, COLOR_BGR2GRAY);
//        //copy second frame
//        stream1.read(frame2);
//        //convert frame2 to gray scale for frame differencing
//        cvtColor(frame2, grayImage2, COLOR_BGR2GRAY);
//        //perform frame differencing with the sequential images. This will output an "intensity image"
//        //do not confuse this with a threshold image, we will need to perform thresholding afterwards.
//        absdiff(grayImage1, grayImage2, differenceImage);
//        //threshold intensity image at a given sensitivity value
//        threshold(differenceImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);
//        if (debugMode == true) {
//            //show the difference image and threshold image
//            imshow("Difference Image", differenceImage);
//            imshow("Threshold Image", thresholdImage);
//        }
//        else {
//            //if not in debug mode, destroy the windows
//            destroyWindow("Difference Image");
//            destroyWindow("Threshold Image");
//        }
//        //blur() to smooth the image, remove noise
//        blur(thresholdImage, thresholdImage, cv::Size(BLUR_SIZE, BLUR_SIZE));
//        //threshold again to obtain binary image from blur output
//        threshold(thresholdImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);
//        //verifies that image is 8 bit for findcontours()
//        thresholdImage.convertTo(thresholdImage, CV_8U);
//        if (debugMode == true) {
//            //show the threshold image after it's been "blurred"
//            imshow("Final Threshold Image", thresholdImage);
//        }
//        else {
//            destroyWindow("Final Threshold Image");
//        }

//        //if tracking enabled, search for contours in our thresholded image
//        if (trackingEnabled) {
//            //Collects a number of sample averages specified by SMOOTHING_SAMPLE and sticks them in the samplePoints global vector
//            collectSamples(thresholdImage, frame1);
//        }
//        //when samplePoints vector reaches the size specified by SMOOTHING_SAMPLE, updates the current point and clears samplePoints
//        if (samplePoints.size() == SMOOTHING_SAMPLE) {
//            destination = pathSmoothing(frame1);
//            samplePoints.clear();
//        }

//        if (trackingEnabled) {
//            targetPoints.push_back(current);
//            vector<Point> temp;
//            int counter = 0;

//            //Draw Past motion of target//
//            //if vector target only has one point, skip over it
//            if (targetPoints.size() > 1) {
//                if (TRAILS >= targetPoints.size()) {
//                    counter = targetPoints.size();
//                    //target size hasn't gotten that many trails yet
//                    //Loop through past points and draw last 3 lines of motion
//                    for (int i = 0; i + 1<counter - 1; i++) {
//                        line(frame1, targetPoints[i], targetPoints[i + 1], (0, 0, i*10), 2);
//                    }
//                }
//                else {
//                    counter = TRAILS;

//                    //Loop through past points and draw last lines of motion
//                    for (int i = 0; i + 1<counter; i++) {
//                        line(frame1, targetPoints[targetPoints.size() - 1 - i], targetPoints[targetPoints.size() - 2 - i], (0, 0, 255-i*20), 2);
//                        targetPoints[i] = targetPoints[i + 1];
//                    }
//                }
//            }
//        }


//        //limits the speed of movement of the target crosshair. We can tweak SPEED_OF_MOVEMENT to accurately reflect the actual position of the laser in project 2
//        //so that we can draw an obscuring circle over the laser
//        current = speedGovernor(current, destination, SPEED_OF_MOVEMENT);
//        Point predictLine = speedGovernor(current, destination, 100);

//        //draw the target
//        drawTarget(current, frame1);
//        line(frame1, current, predictLine, Scalar(0, 255, 0), 2);

//        imshow("Frame1", frame1);

//        //hotkey code from tutorial at (https://dl.dropboxusercontent.com/u/28096936/tuts/motionTrackingTut/finalCode/motionTracking.cpp)
//        switch (waitKey(10)) {
//        case 27: //'esc' key has been pressed, exit program.
//            return 0;
//        case 116: //'t' has been pressed. this will toggle tracking
//            trackingEnabled = !trackingEnabled;
//            if (trackingEnabled == false) cout << "Tracking disabled." << endl;
//            else cout << "Tracking enabled." << endl;
//            break;
//        case 100: //'d' has been pressed. this will debug mode
//            debugMode = !debugMode;
//            if (debugMode == false) cout << "Debug mode disabled." << endl;
//            else cout << "Debug mode enabled." << endl;
//            break;
//        case 112: //'p' has been pressed. this will pause/resume the code.
//            pause = !pause;
//            if (pause == true) {
//                cout << "Code paused, press 'p' again to resume" << endl;
//                while (pause == true) {
//                    //stay in this loop until
//                    switch (waitKey()) {
//                    case 112:
//                        //change pause back to false
//                        pause = false;
//                        cout << "Code resumed." << endl;
//                        break;
//                    }
//                }
//            }

//        }
//    }
//}

////function takes the populated samplePoints vector, gets the average of all points in that vector, and returns the averaged point
//Point CameraMove::pathSmoothing(Mat &cameraFeed) {
//    Point temp;
//    int x = 0;
//    int y = 0;
//    for (int i = 0; i < SMOOTHING_SAMPLE; i++) {
//        x += samplePoints[i].x;
//        y += samplePoints[i].y;
//    }
//    temp.x = x / SMOOTHING_SAMPLE;
//    temp.y = y / SMOOTHING_SAMPLE;
//    return temp;
//}

////draws the line trail
//void drawTrail() {
//}
////draws the target at given point
//void CameraMove::drawTarget(Point target, Mat &cameraFeed) {
//    int x = target.x;
//    int y = target.y;
//    line(cameraFeed, Point(x, y + 25), Point(x, y - 25), Scalar(0, 0, 0), 2);
//    line(cameraFeed, Point(x + 25, y), Point(x - 25, y), Scalar(0, 0, 0), 2);
//    putText(cameraFeed, "(" + to_string(x) + "," + to_string(y) + ")", Point(x - 38, y - 35), 1, 1, Scalar(0, 0, 255), 2);
//}

////uses some trigonometry magic to update the position of the current point based on a limited speed given by SPEED_OF_MOVEMENT
//Point CameraMove::speedGovernor(Point current, Point destination, double dist) {
//    double x_dist = destination.x - current.x;
//    double y_dist = destination.y - current.y;
//    double distance = sqrt(pow((x_dist), 2) + pow((y_dist), 2));
//    double angle = atan2(y_dist, x_dist);
//    if (distance > dist) {
//        distance = dist;
//        x_dist = distance*(cos(angle));
//        y_dist = distance*(sin(angle));
//    }
//    current.x = current.x + x_dist;
//    current.y = current.y + y_dist;
//    return current;
//}

//void CameraMove::collectSamples(Mat thresholdImage, Mat &cameraFeed) {
//    bool objectDetected = false;
//    Mat temp;
//    thresholdImage.copyTo(temp);
//    vector< vector<Point> > contours;
//    vector<Vec4i> hierarchy;

//    //find contours of processed image (areas of motion)
//    findContours(temp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS);// retrieves external contours

//    vector<Moments> contour_moments(contours.size());
//    vector<Point> mass_centers(contours.size());

//    //gets centroids of contours
//    for (int i = 0; i < contours.size(); i++) {
//        contour_moments[i] = moments(contours[i], false);
//        mass_centers[i] = Point(contour_moments[i].m10 / contour_moments[i].m00, contour_moments[i].m01 / contour_moments[i].m00);
//    }

//    if (contours.size()>0)objectDetected = true;
//    else objectDetected = false;

//    //only finds averages of centroids if contours exist - prevents target from being set to 0,0 if no contours
//    if (objectDetected) {
//        double xpos = 0;
//        double ypos = 0;
//        for (int i = 0; i < contours.size(); i++) {
//            xpos += mass_centers[i].x;
//            ypos += mass_centers[i].y;
//        }
//        //find the average of the centroids of all contours. This could be improved by using K-means or some other kind of clustering algorithm
//        if (!(abs(xpos) > CAM_RES_X || abs(ypos) > CAM_RES_Y)) {
//            targ.x = xpos / contours.size(), targ.y = ypos / contours.size();
//        }
//        cout << targ << endl;
//    }

//    samplePoints.push_back(targ);

//    //simple drawing showing a visualisation of target
//    drawContours(cameraFeed, contours, -1, Scalar(255, 255, 255), 1);
//}
