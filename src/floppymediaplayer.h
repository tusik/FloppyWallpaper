#ifndef FLOPPYMEDIAPLAYER_H
#define FLOPPYMEDIAPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
QT_BEGIN_NAMESPACE
namespace Ui {
class FloppyMediaPlayer;
}
QT_END_NAMESPACE
class FloppyMediaPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit FloppyMediaPlayer(QWidget *parent = nullptr);

    bool addPlayFile(const QUrl url);
    void play();
    void stop();
    void pause();
    void changeIndex(int index);
    void resume();
    ~FloppyMediaPlayer();
signals:
    void mediaChanged(const QMediaContent &media);
private:
    QMediaPlayer *player;
    QVideoWidget *widget;
    QMediaPlaylist *play_list;

};

#endif // FLOPPYMEDIAPLAYER_H
