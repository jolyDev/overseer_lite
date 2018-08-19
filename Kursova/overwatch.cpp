#include "overwatch.h"

Overwatch::Overwatch(QObject *parent)
    : QThread(parent)
{
    start(LowPriority);
}

Overwatch::~Overwatch()
{
    isNeedToCall = false;
    terminate();
    wait();
}

void Overwatch::emitSignal() {
    if (isNeedToCall) {
        emit searchMotion();
        this->msleep(5);
    }
}

bool Overwatch::isMotion(cv::VideoCapture * source) {
        // Take images and convert them to gray
        Mat result, prev_frame, current_frame ,next_frame;// *cam >> frame;
        *source >> prev_frame;
        *source >> current_frame;
        *source >> next_frame;

        cvtColor(current_frame, current_frame, CV_RGB2GRAY);
        cvtColor(prev_frame, prev_frame, CV_RGB2GRAY);
        cvtColor(next_frame, next_frame, CV_RGB2GRAY);

        // d1 and d2 for calculating the differences
        // result, the result of and operation, calculated on d1 and d2

        Mat d1, d2, motion;

        // If more than 'there_is_motion' pixels are changed, we say there is motion
        // and store an image on disk

        int there_is_motion = 5;

        // Maximum deviation of the image, the higher the value, the more motion is allowed

        int max_deviation = 20;

        // Erode kernel
        // Mat kernel_ero = getStructuringElement(MORPH_RECT, Size(2,2));

        // All settings have been set, good
        // Calc differences between the images and do AND-operation
        // threshold image, low differences are ignored (ex. contrast change due to sunlight)

        absdiff(prev_frame, current_frame, d1);
        absdiff(next_frame, current_frame, d2);

        bitwise_and(d1, d2, motion);

        this->motion = d1;

        threshold(motion, motion, 35, 255, CV_THRESH_BINARY);
        // erode(motion, motion, kernel_ero);

        return this->detectMotion(motion, result, max_deviation) >= there_is_motion;
}


Mat Overwatch::getMotion() {
    return this->motion;
}

int Overwatch::detectMotion(const Mat & motion, Mat & result, int max_deviation) {

    // Detect motion in window
    int x_start = 10, x_stop = motion.cols - 1;
    int y_start = 10, y_stop = motion.rows - 10;
    // calculate the standard deviation
    Scalar mean, stddev;
    meanStdDev(motion, mean, stddev);
    // if not to much changes then the motion is real (neglect agressive snow, temporary sunlight)

    int number_of_changes = 0;
    if(stddev[0] < max_deviation)
        // loop over image and detect changes
        for(int j = y_start; j < y_stop; j+=3) // width
            for(int i = x_start; i < x_stop; i+=3) // height
                if(motion.at<uchar>(i, j) == 255)
                    number_of_changes++;
    return number_of_changes;
}

