#include "emergency_dialog.h"
#include "ui_emergency_dialog.h"

Emergency_Dialog::Emergency_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Emergency_Dialog)
{
    ui->setupUi(this);
    QSound::play("Icons/evac (copy).wav");
}

Emergency_Dialog::~Emergency_Dialog()
{
    delete ui;
}

void Emergency_Dialog::on_pushButton_clicked()
{
    if(ui->label->text().compare("This is just a test, no threds are available")){
        // this->parent()->
        this->close();
    }
}
