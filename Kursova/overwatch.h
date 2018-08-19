#pragma once

#include <iostream>
#include <fstream>
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <time.h>
#include <dirent.h>
#include <QThread>
#include <sstream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
using namespace cv;

class Overwatch : public QThread {

        Q_OBJECT

private:

    int detectMotion(const Mat & motion, Mat & result,
                     int max_deviation);

    Mat motion;

signals:

     void searchMotion();

public:

     bool isNeedToCall = false;

    Overwatch(QObject *parent = 0);

    ~Overwatch();

    bool isMotion(cv::VideoCapture * source);

    void emitSignal();

    Mat getMotion();
};
