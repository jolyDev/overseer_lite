#pragma once
#include <QSound>
#include <QTabWidget>
#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QTime>
#include <iostream>
#include <string>
#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QThread>
#include <thread>
#include <time.h>
#include <QString>
#include <functional>

#include "overwatch.h"
#include "player.h"
#include "timesetdialog.h"
#include "videoplayer.h"
#include "server_interaction.h"
#include "emergency_dialog.h"

namespace Ui {
class Cam_control;
}

class Cam_control : public QMainWindow
{
    Q_OBJECT

public:
    void updateCamera();
    void setCentralCamera(cv::VideoCapture * cam, bool cam_on);
    explicit Cam_control(QWidget *parent = 0);
    ~Cam_control();

    cv::VideoCapture * getCam1();
    cv::VideoCapture * getCam2();
    cv::VideoCapture * getCam3();
    cv::VideoCapture * getCam4();
    cv::VideoCapture * getCentralCamera();


private slots:

    //  void beginDownload();

    // void doYourStuff();

    void emitOverwatchSignal();

    void updatePlayerUI(QImage img);

    void saveMatToStore();

    bool take_a_look();

    void setDefaultIcons();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_record_clicked();

    void on_overwatch_clicked();

    void on_Emergency_clicked();

    void on_pushButton_2_clicked();

    void on_overwatch_policy_clicked();

    void on_pushButton_3_clicked();

    void on_Entities_clicked(const QModelIndex &index);

    void on_Folders_clicked(const QModelIndex &index);

    void on_MainScreenController_clicked();

    void on_pushButton_clicked();

private:

    Ui::Cam_control *ui;

    cv::VideoCapture camera;
    cv::VideoCapture camera_2;
    cv::VideoCapture camera_3;
    cv::VideoCapture camera_4;

    cv::VideoWriter video;
    cv::VideoCapture * central_camera;
    Player* myPlayer;


    Overwatch * MotiThread;

    QTimer MotionTimeSleap;

    int cheakTimeIntervals = 1000;

    bool camera_on;
    bool camera_2_on;
    bool camera_3_on;
    bool camera_4_on;
    bool central_camera_on;

    bool write_video = false;
    bool changeVideoName;
    bool currentListShowPhoto = true;
    bool work_until = true;

    std::string fileName;

    std::thread * justThread;

    std::thread * threadForUpload;
};
