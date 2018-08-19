#include "cam_control.h"
#include "opencv2/opencv.hpp"
#include "ui_cam_control.h"


const std::string currentDateTime();

const std::string ProjPath = "/home/artemko/progbase3/progbase3/build-Kursova-Desktop-Debug/";


Cam_control::Cam_control(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::Cam_control),

    camera(0),
    camera_2(1),
    camera_3(2),
    camera_4(3)
{
    // using thread for output video
    myPlayer = new Player();
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),
                              this, SLOT(updatePlayerUI(QImage)));

    // this block garant own thread for overwatch
    QObject::connect(&MotionTimeSleap, SIGNAL(timeout()), this, SLOT(emitOverwatchSignal()));

    MotionTimeSleap.start(cheakTimeIntervals);

    MotiThread = new Overwatch(this);

    QObject::connect(MotiThread, SIGNAL(searchMotion()),
                              this, SLOT(take_a_look()));

    ui->setupUi(this);
    this->setDefaultIcons();
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->removeTab(4);
    ui->tabWidget->removeTab(3);
    ui->tabWidget->removeTab(2);

    camera_on = camera.isOpened();
    camera_2_on = camera_2.isOpened();
    camera_3_on = camera_3.isOpened();
    camera_4_on = camera_4.isOpened();
    central_camera = &camera;
    central_camera_on = camera_on;

     QTimer * timer = new QTimer(this);
     QObject::connect(timer, &QTimer::timeout, this, &Cam_control::updateCamera);
     timer->start(42);

     justThread = new std::thread([this] () {
         cv::Mat frame;

         while (work_until)
             if (this->write_video) {
                 *this->central_camera >> frame;
                 this->video.write(frame);
                 usleep(42000);
             }
     });
}

void Cam_control::emitOverwatchSignal() {
    MotiThread->searchMotion();
}

void Cam_control::setDefaultIcons() {
    ui->record->setIcon(QIcon("Icons/video.png"));
    ui->overwatch->setIcon(QIcon("Icons/eye.png"));
    ui->Emergency->setIcon(QIcon("Icons/alarm.png"));
    ui->overwatch_policy->setIcon(QIcon("Icons/clock.png"));
    ui->MainScreenController->setIcon(QIcon("Icons/play.png"));
    ui->pushButton->setIcon(QIcon("Icons/outbox.png"));
    ui->tabWidget->setTabIcon(0, QIcon("Icons/icon.png"));
    ui->tabWidget->setTabIcon(1, QIcon("Icons/archive.png"));

    ui->label->setPixmap(QPixmap("Icons/no_image.png"));
    ui->label_2->setPixmap(QPixmap("Icons/no_image.png"));
    ui->label_3->setPixmap(QPixmap("Icons/no_image.png"));
    ui->label_4->setPixmap(QPixmap("Icons/no_image.png"));
    ui->label_5->setPixmap(QPixmap("Icons/no_image.png"));
    ui->label_6->setPixmap(QPixmap("Icons/no_image.png"));
    ui->mainScreen->setPixmap(QPixmap("Icons/no_image.png"));

    QDir dir = QDir("photo");
    QStringList list = dir.entryList(QDir::AllDirs, QDir::Time);
    for (auto & s: list)
        if (QString::compare(s, ".") != 0 && QString::compare(s, "..") != 0)
            ui->Folders->addItem(s);
}

void Video_out(cv::VideoCapture * cam, QLabel * label, bool cam_on) {
    if (cam_on) {
        cv::Mat frame;
        *cam >> frame;

        cv::cvtColor(frame, frame, CV_BGR2RGB);

        label->setPixmap(QPixmap::fromImage(QImage(frame.data, frame.cols,
                                                   frame.rows, frame.step, QImage::Format_RGB888)));
    }
}

void Cam_control::updateCamera() {
        Video_out(this->getCam1(), ui->label, camera_on);
        Video_out(this->getCam2(), ui->label_2, camera_2_on);
        Video_out(this->getCam3(), ui->label_3, camera_3_on);
        Video_out(this->getCam4(), ui->label_4, camera_4_on);
        Video_out(this->getCentralCamera(), ui->label_central, central_camera_on);
}


void Cam_control::updatePlayerUI(QImage img) {
    if (!img.isNull())
        ui->mainScreen->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size()
                                           ,Qt::KeepAspectRatio, Qt::FastTransformation));
}


void Cam_control::setCentralCamera(cv::VideoCapture * cam, bool cam_on) {
    central_camera = cam;
    central_camera_on = cam_on;
}



cv::VideoCapture * Cam_control::getCentralCamera() { return central_camera; }

Cam_control::~Cam_control() {
    work_until  = false;
    usleep(100000);
    delete ui;
 }

std::string curentMongth() {
    QDate date = QDate::currentDate();
    std::cout << date.toString().toStdString();
    return date.toString().toStdString();
}

void Cam_control::on_record_clicked() {

    if (write_video)
        ui->record->setIcon(QIcon("Icons/video.png"));
    else  {
        ui->record->setIcon(QIcon("Icons/video-red.png"));
        if(!QDir(QString::fromStdString(curentMongth())).exists())
            QDir().mkdir(QString::fromStdString("video/" + curentMongth()));
        fileName = "video/" + curentMongth() + "/"
                + QTime::currentTime().toString().toStdString() + " out.avi";

        video = cv::VideoWriter(fileName, CV_FOURCC('M','J','P','G'),10,
                                cv::Size(central_camera->get(CV_CAP_PROP_FRAME_WIDTH),
                                         central_camera->get(CV_CAP_PROP_FRAME_HEIGHT)),true);
    }
    write_video = !write_video;
}

void Cam_control::on_overwatch_clicked()
{
    if (MotiThread->isNeedToCall) {

        ui->overwatch->setIcon(QIcon("Icons/eye.png"));

        take_a_look();
    } else
        ui->overwatch->setIcon(QIcon("Icons/eye-red.png"));
    // overwatch = !overwatch;
    MotiThread->isNeedToCall = !MotiThread->isNeedToCall;
}

bool Cam_control::take_a_look() {
    if (MotiThread->isNeedToCall) {

        if (MotiThread->isMotion(central_camera)) {
            std::cout << " | *** |  Motion detected" << std::endl;
            cv::Mat frame = MotiThread->getMotion();
            ui->label_5->setPixmap(QPixmap::fromImage(QImage(frame.data, frame.cols,
                                                             frame.rows, frame.step, QImage::Format_Grayscale8)));
            cv::erode(frame, frame, cv::getStructuringElement(MORPH_RECT, Size(2,2)));
            ui->label_6->setPixmap(QPixmap::fromImage(QImage(frame.data, frame.cols,
                                                             frame.rows, frame.step, QImage::Format_Grayscale8)));

            this->saveMatToStore();
            return true;
        }
    }
    return false;
}

void Cam_control::saveMatToStore() {

    if(!QDir(QString::fromStdString("photo/" + curentMongth())).exists())
        QDir().mkdir(QString::fromStdString("photo/" + curentMongth()));
    cv::Mat mat;
    *central_camera >> mat;
    cv::imwrite("photo/" + curentMongth() + "/" + QTime::currentTime().toString().toStdString() + ".jpg", mat);
    cv::cvtColor(mat, mat, CV_BGR2RGB);
    ui->label_5->setPixmap(QPixmap::fromImage(QImage(mat.data, mat.cols,
                                               mat.rows, mat.step, QImage::Format_RGB888)));
}

void Cam_control::on_Emergency_clicked()
{
    Emergency_Dialog password;
    write_video = true;
    MotiThread->isNeedToCall = true;
    this->ui->centralWidget->hide();
    password.exec();
}

void clearListWidget(QListWidget * l) {
    for (int i = l->count() - 1; i >= 0 ; i--)
        l->takeItem(i);
}

void Cam_control::on_pushButton_2_clicked()
{
    currentListShowPhoto = true;
    clearListWidget(ui->Entities);
    clearListWidget(ui->Folders);
    QDir dir = QDir("photo");
    QStringList list = dir.entryList(QDir::AllDirs,QDir::Time);
    for (auto & s: list)
        if (QString::compare(s, ".") != 0 && QString::compare(s, "..") != 0)
            ui->Folders->addItem(s);
}

void Cam_control::on_overwatch_policy_clicked()
{
    TimeSetDialog di;
    di.exec();
    MotionTimeSleap.setInterval(di.getValue());
}

void Cam_control::on_Entities_clicked(const QModelIndex &index) {
    QString filename = ui->Folders->item(ui->Folders->currentRow())->text() + "/"
            + ui->Entities->item(ui->Entities->currentRow())->text();

    if (currentListShowPhoto) {

        ui->prev_prev->setPixmap(ui->prev->grab());
        ui->prev_prev_name->setText(ui->prev_name->text());

        ui->prev->setPixmap(ui->mainScreen->grab());
        ui->prev_name->setText(ui->mainScreenName->text());

        ui->mainScreen->setPixmap(QPixmap("photo/" + filename));
        ui->mainScreenName->setText(ui->Entities->item(ui->Entities->currentRow())->text());
    }
    else
        if (!myPlayer->loadVideo("video/" + filename.toStdString())) {
            ui->mainScreenName->setText(ui->Entities->item(ui->Entities->currentRow())->text());
        }
}

void Cam_control::on_pushButton_3_clicked()
{
    currentListShowPhoto = false;
    clearListWidget(ui->Entities);
    clearListWidget(ui->Folders);
    QDir dir = QDir("video");
    QStringList list = dir.entryList(QDir::AllDirs,QDir::Time);
    for (auto & s: list)
        if (QString::compare(s, ".") != 0 && QString::compare(s, "..") != 0)
            ui->Folders->addItem(s);
}


void Cam_control::on_pushButton_5_clicked()
{
    if (camera_on)
        setCentralCamera(&camera, camera_on);
}

void Cam_control::on_pushButton_6_clicked()
{
    if (camera_2_on)
        setCentralCamera(&camera_2, camera_2_on);
}

void Cam_control::on_pushButton_7_clicked()
{
    if (camera_3_on)
        setCentralCamera(&camera_3, camera_on);
}

void Cam_control::on_pushButton_8_clicked()
{
    if (camera_4_on)
        setCentralCamera(&camera_4, camera_on);
}

cv::VideoCapture * Cam_control::getCam1() {
    return &this->camera;
}

cv::VideoCapture * Cam_control::getCam2() {
    return &this->camera_2;
}

cv::VideoCapture * Cam_control::getCam3() {
    return &this->camera_3;
}

cv::VideoCapture * Cam_control::getCam4() {
    return &this->camera;
}

void Cam_control::on_Folders_clicked(const QModelIndex &index) {
    clearListWidget(ui->Entities);
    QString filename = ui->Folders->item(ui->Folders->currentRow())->text();
    QDir dir = QDir("photo/" + filename);
    if (!currentListShowPhoto)
        dir = QDir("video/" + filename);
    QStringList list = dir.entryList();
    for (auto & s: list)
        if (QString::compare(s, ".") != 0 && QString::compare(s, "..") != 0)
            ui->Entities->addItem(s);
}

void Cam_control::on_MainScreenController_clicked()
{
    if (myPlayer->isStopped()) {
        myPlayer->Play();
        ui->MainScreenController->setIcon(QIcon("Icons/play.png"));
        ui->MainScreenController->setText("Pause");
    }else {
        myPlayer->Stop();
        ui->MainScreenController->setIcon(QIcon("Icons/pause.png"));
        ui->MainScreenController->setText("Play");
    }
}

void flow() {
    Server_Interaction ser;
    ser.exec();
}

void Cam_control::on_pushButton_clicked() {
    // threadForUpload = new std::thread(&flow);
    flow();
    // ser.show();
}
