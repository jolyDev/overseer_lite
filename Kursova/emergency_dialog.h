#ifndef EMERGENCY_DIALOG_H
#define EMERGENCY_DIALOG_H

#include <QDialog>
#include <QSound>

namespace Ui {
class Emergency_Dialog;
}

class Emergency_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Emergency_Dialog(QWidget *parent = 0);
    ~Emergency_Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Emergency_Dialog *ui;
};

#endif // EMERGENCY_DIALOG_H
