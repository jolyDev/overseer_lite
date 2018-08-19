#include "server_interaction.h"
#include "ui_server_interaction.h"

const int waitForConnection = 30000;

using namespace std;
Server_Interaction::Server_Interaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server_Interaction)
{
    ui->setupUi(this);
    ui->address->setText("127.0.0.1:3001");
}

Server_Interaction::~Server_Interaction()
{
    delete ui;
}

void Server_Interaction::on_progressBar_destroyed()
{

}

QJsonValue jsonValFromPixmap(const QPixmap &p) {
  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);
  p.save(&buffer, "JPG");
  auto const encoded = buffer.data().toBase64();
  return {QLatin1String(encoded)};
}



bool Server_Interaction::send_photo_dir_content(QString directory) {
    QString dir = "photo/" + directory;
    QDir saveDir = QDir(dir);
    QStringList list = saveDir.entryList();
    int i = list.size() - 2;
    ui->progressBar_2->setMaximum(i - 1); i = 0;
    for (auto & s: list)
        if (QString::compare(s, ".") != 0 && QString::compare(s, "..") != 0) {
            ui->label->setPixmap(QPixmap(dir + QString("/") + s));
            ui->progressBar_2->setValue(i); i++;
            ui->label_4->setText(s);
           // usleep(500000);
            this->sendRequest("foto" + dir + "/" + s + "/" + jsonValFromPixmap(QPixmap(dir + QString("/") + s)).toString());
        }

    ui->progressBar_2->setValue(1000);
    return true;
}


bool Server_Interaction::send_video_dir_content(QString directory) {
    cv::VideoCapture capture;

    QString dir = "video/" + directory;
    QDir saveDir = QDir("video/" + directory);
    QStringList list = saveDir.entryList();
    int i = list.size() - 2;
    ui->progressBar_2->setValue(-1); i = 0;
    for (auto & s: list)
        if (QString::compare(s, ".") != 0 && QString::compare(s, "..") != 0) {

            capture.open("video/" + directory.toStdString() + "/" + s.toStdString());

            cv::Mat frame;
            QPixmap toSend;
            while (capture.grab()) {
                capture >> frame;
                cv::cvtColor(frame, frame, CV_BGR2RGB);
                toSend = QPixmap::fromImage(QImage((unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_RGB888));
                ui->label->setPixmap(toSend);
                ui->label_4->setText(s);
                this->sendRequest("medi" + dir + "/" + s + "/" + jsonValFromPixmap(toSend).toString());
            }
        }
}

void Server_Interaction::on_pushButton_clicked()
{
    QDir dir = QDir("photo");
    QStringList list = dir.entryList(QDir::AllDirs,QDir::Time);

    int i = list.size() - 2;
    ui->progressBar->setMaximum(i); i = 0;
    for (auto & s: list)
        if (QString::compare(s, ".") != 0 && QString::compare(s, "..") != 0) {
            this->sendRequest("dir photo/" + s);
            ui->progressBar->setValue(i); i++;
            ui->label_3->setText(s);
            send_photo_dir_content(s);
    }

    ui->progressBar->setValue(0);

    dir = QDir("video");
    list = dir.entryList(QDir::AllDirs,QDir::Time);
    ui->progressBar->setMaximum(list.size() - 2); i = 0;
    for (auto & s: list)
        if (QString::compare(s, ".") != 0 && QString::compare(s, "..") != 0) {
            this->sendRequest("dir video/" + s);
            ui->progressBar->setValue(i); i++;
            ui->label_3->setText(s);
            send_video_dir_content(s);
        }

    ui->progressBar->setValue(ui->progressBar->maximum()); i++;
    ui->progressBar_2->setValue(ui->progressBar_2->maximum());
}

string Server_Interaction::sendRequest(QString data) {
    int u = QString::fromStdString(ui->address->text().toStdString()).lastIndexOf(":");
    if (u == -1)
            return "-1";
    std::string tempStr = ui->address->text().mid(0, u).toStdString();
    std::string tempStr2 = ui->address->text().mid(u + 1, ui->address->text().length()).toStdString();
        QHostAddress serverAddress(QString::fromStdString(tempStr));
        std::cout << tempStr << std::endl;
        int PORT = (QString::fromStdString(tempStr2)).toInt();
        std::cout << PORT << std::endl;
        QTcpSocket client(this); // parent
        cout  << "connecting to server at port " << PORT << endl;
        client.connectToHost(serverAddress, PORT);
        client.waitForConnected(waitForConnection);
        if (client.state() != QAbstractSocket::SocketState::ConnectedState) {
            cout  << "connection error" << endl;
            return "Connection failure";
        }
        cout  << "connected to server " << endl;
        QString requestStr = data + "~@$";
        client.write(requestStr.toUtf8());
        client.flush();

        if (!client.waitForReadyRead(waitForConnection)) {
            cout  << "read err " << endl;
            // @todo
        }
        //
        QByteArray response = client.readAll();
        //
        client.disconnectFromHost();
        cout  << "disconnected" << endl;
        cout << response.toStdString() << endl;
        return response.toStdString();
    }
