#include "videoplayer.h"
#include "ui_videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

void VideoPlayer::doYourStuff() {
    QMediaPlayer * player = new QMediaPlayer(); // i removed this everywhere
    // owned by PlaylistModel
    QMediaPlaylist * playlist = new QMediaPlaylist();
    player->setPlaylist(playlist);
    QUrl path = QUrl::fromLocalFile("/home/artemko/old videos/out.avi");
    playlist->addMedia(path);
    player->play();
}
