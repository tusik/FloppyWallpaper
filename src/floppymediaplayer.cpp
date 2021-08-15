#include "floppymediaplayer.h"

FloppyMediaPlayer::FloppyMediaPlayer(QWidget *parent) : QWidget(parent)
{
    play_list = new QMediaPlaylist(this);
    widget = new QVideoWidget(this);
    player = new QMediaPlayer(this);
}

FloppyMediaPlayer::~FloppyMediaPlayer()
{
    this->stop();
    player->deleteLater();
    widget->deleteLater();
    play_list->deleteLater();
}

bool FloppyMediaPlayer::addPlayFile(const QUrl url)
{

    return play_list->addMedia(QMediaContent(url));
}

void FloppyMediaPlayer::play()
{

//    player->setMuted(true);
    connect(player,&QMediaPlayer::currentMediaChanged,this,&FloppyMediaPlayer::mediaChanged);
    player->setPlaylist(play_list);
    player->setVideoOutput(widget);
    widget->setGeometry(0,0,this->size().width(),this->size().height());
    widget->show();
    player->play();

}

void FloppyMediaPlayer::stop()
{
    player->stop();
    player->playlist()->clear();

//    player->deleteLater();
//    widget->deleteLater();
}

void FloppyMediaPlayer::pause()
{
    player->pause();
}

void FloppyMediaPlayer::changeIndex(int index)
{
    player->playlist()->setCurrentIndex(index);
}

void FloppyMediaPlayer::resume()
{
    player->play();
}
