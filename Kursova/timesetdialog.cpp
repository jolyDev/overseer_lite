#include "timesetdialog.h"
#include "ui_timesetdialog.h"

TimeSetDialog::TimeSetDialog(QWidget *parent, int time) :
    QDialog(parent),
    ui(new Ui::TimeSetDialog)
{
    ui->setupUi(this);
    time_intervals = time;
    ui->spinBox->setValue(time);
}

TimeSetDialog::~TimeSetDialog()
{
    delete ui;
}

void TimeSetDialog::on_radioButton_clicked()
{
    ui->spinBox->setValue(500);
}

void TimeSetDialog::on_radioButton_2_clicked()
{
   ui->spinBox->setValue(1000);
}

void TimeSetDialog::on_radioButton_3_clicked()
{
    ui->spinBox->setValue(2000);
}

void TimeSetDialog::on_radioButton_4_clicked()
{
    ui->spinBox->setValue(5000);
}

void TimeSetDialog::on_radioButton_5_clicked()
{
    ui->spinBox->setValue(10000);
}

void TimeSetDialog::on_buttonBox_accepted()
{
    time_intervals = ui->spinBox->value();
}

int TimeSetDialog::getValue() {
    return time_intervals;
}
