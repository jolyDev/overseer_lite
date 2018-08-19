#ifndef TIMESETDIALOG_H
#define TIMESETDIALOG_H

#include <QDialog>

namespace Ui {
class TimeSetDialog;
}

class TimeSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeSetDialog(QWidget *parent = 0, int time = 1000);
    ~TimeSetDialog();
    int getValue();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_buttonBox_accepted();

private:
    Ui::TimeSetDialog *ui;

    int time_intervals;
};

#endif // TIMESETDIALOG_H
