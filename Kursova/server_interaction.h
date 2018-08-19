#ifndef SERVER_INTERACTION_H
#define SERVER_INTERACTION_H

#include <QDialog>
#include <QTcpSocket>
#include <iostream>
#include <QHostAddress>
#include <QDir>
#include <QBuffer>
#include <QJsonValue>
#include <opencv2/opencv.hpp>
#include <unistd.h>

#include <unistd.h>

namespace Ui {
class Server_Interaction;
}

class Server_Interaction : public QDialog
{
    Q_OBJECT

public:
    explicit Server_Interaction(QWidget *parent = 0);
    ~Server_Interaction();

    std::string sendRequest(QString data);

private slots:


    bool send_video_dir_content(QString directory);

    bool send_photo_dir_content(QString directory);

    void on_progressBar_destroyed();

    void on_pushButton_clicked();

private:
    Ui::Server_Interaction *ui;
};

#endif // SERVER_INTERACTION_H
