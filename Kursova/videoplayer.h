#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

    void doYourStuff();
private:
    Ui::VideoPlayer *ui;

    QMediaPlayer *player;
};

#endif // VIDEOPLAYER_H
