#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDragEnterEvent>
#include <QMimeData>
#include <QMainWindow>
#include <QModelIndexList>
#include <QStandardItemModel>
#include "src/floppymediaplayer.h"
#include <functional>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum PlayingStatus{
    NO_MEDIA,PLAYING,PAUSE,RESET
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void wallpayer_play();

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void changing_index(int index);
    void stop_playing();
    void pause_playing();
    void resume_playing();

    std::function<void()> play_btn_action = std::bind(&MainWindow::wallpayer_play,this);
signals:
    void status_changed(PlayingStatus status);
private slots:
    void on_playBotton_clicked();

    void on_listView_indexesMoved(const QModelIndexList &indexes);

    void on_muteCheckBox_stateChanged(int arg1);

    void on_pushButton_clicked();

    void slot_status_changed(PlayingStatus status);
private:
    WId viewId;
    Ui::MainWindow *ui;
    QList<QUrl> file_urls;
    QStandardItemModel play_list_view;
    FloppyMediaPlayer *play_form = nullptr;
    int playing_index=-1;
    PlayingStatus current_playing_status = PlayingStatus::NO_MEDIA;
};
#endif // MAINWINDOW_H
