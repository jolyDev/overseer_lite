#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

const int waitForConnection = 30000;

QString signal_recognizer(QString requestStr, Data_Storage * Base);

QString signal_recognizer(QString requestStr, Data_Storage * Base) {
    std::cout << requestStr.toStdString() << std::endl;
    QString strCode = requestStr.mid(0,4);
    QString data = requestStr.mid(4, requestStr.length());
    std::cout << strCode.toStdString() << std::endl;

    std::cout << data.mid(0, 20).toStdString() << std::endl;

    if (strCode.compare("dir ") == 0) {
        Base->curDir.mkpath("../..");
        return Base->addDir(data);
    }

    if (strCode.compare("foto") == 0)
        return Base->send_photo_dir_content(data) ? "saved" : "unsaved";

    if (strCode.compare("medi") == 0)
        return Base->send_video_dir_content(data) ? "saved" : "unsaved";

    return "failure";
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir Mother;
    Mother.mkdir("photo");
    Mother.mkdir("video");

    Data_Storage Base;

    // Server server(&a);
    QTcpServer server(this);
    const int PORT = 3001;
    if (!server.listen(QHostAddress::Any, PORT)) {
        cerr << "cant start" << endl;
        return ;
    }
    cout << "server started at port " << PORT << endl;
    for (int i = 0; true; i++) {
        if (i % 5 == 0)
        cout << endl; else cout << ".";
        if (server.waitForNewConnection(waitForConnection)) {
            QTcpSocket * client = server.nextPendingConnection();
            cout << "got new connection" << endl;
            if (client->waitForReadyRead(waitForConnection)) {
                bufer.append(QString(client->readAll()));
                while (!bufer.endsWith("~@$")) {
                    client->waitForReadyRead(waitForConnection);
                    bufer.append(QString(client->readAll()));
                }
                bufer.chop(3);
                QString responseStr = signal_recognizer(bufer, &Base);
                client->write(responseStr.toUtf8());
                client->flush();
                client->waitForBytesWritten(waitForConnection);
                cout << "response sent." << endl;
                bufer.clear();
            }
            client->close();

            request.clear();
            cout << endl << endl << "client disconnected" << endl;
        }
    }
    server.close();

}

MainWindow::~MainWindow()
{
    delete ui;
}
