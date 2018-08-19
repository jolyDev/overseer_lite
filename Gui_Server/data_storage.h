#pragma once
#include <QDir>
#include <iostream>
#include <QBuffer>
#include <QJsonValue>
#include <QWidget>

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
#include <QTcpServer>
#include <QObject>
#include <opencv2/opencv.hpp>

class Data_Storage
{
public:

    Data_Storage();

    QDir curDir;

    cv::VideoWriter video;

    std::string video_name = "";

public slots:

    QString addDir(QString dir);

    QString savePhoto(QString dir);

    bool send_photo_dir_content(QString data);

    bool send_video_dir_content(QString data);

};

