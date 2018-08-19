#pragma once

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
class Video_Writer : QThread {

    Q_OBJECT

public:

    Video_Writer(cv::VideoCapture * cam, QObject *parent = 0);

    void setFilePath(std::string pathToSave);

    void shouldIwrite(bool continue_write);

    void startWriting();

signals:

     void downloadVideoCut();

private:

    cv::VideoCapture * cam;

    std::string path;

    bool should_writing;

    cv::VideoWriter video;

};
