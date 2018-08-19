#include "server_communication.h"
#include "ui_server_communication.h"

Server_communication::Server_communication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server_communication)
{
    ui->setupUi(this);
}

Server_communication::~Server_communication()
{
    delete ui;
}
