#ifndef SERVER_COMMUNICATION_H
#define SERVER_COMMUNICATION_H

#include <QWidget>

namespace Ui {
class Server_communication;
}

class Server_communication : public QWidget
{
    Q_OBJECT

public:
    explicit Server_communication(QWidget *parent = 0);
    ~Server_communication();

private:
    Ui::Server_communication *ui;
};

#endif // SERVER_COMMUNICATION_H
