#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "data_storage.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QByteArray request;

    QString bufer;
};

#endif // MAINWINDOW_H
