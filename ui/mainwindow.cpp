#include "mainwindow.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "src/utility/windowsutil.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);

    this->show();
    connect(this,&MainWindow::status_changed,this,&MainWindow::slot_status_changed);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(current_playing_status!=PlayingStatus::NO_MEDIA){
        stop_playing();
        play_form->deleteLater();
    }

}

void MainWindow::wallpayer_play()
{

    play_form = new FloppyMediaPlayer(this);

    connect(play_form,&FloppyMediaPlayer::mediaChanged,[&](const QMediaContent &media){
        changing_index(++playing_index);
        qDebug()<<playing_index;
    });
    for(auto i=0;i<file_urls.size();i++){
        play_form->addPlayFile(file_urls.at(i));

    }

    play_form->setWindowFlags(Qt::Window);
    play_form->showFullScreen();
    viewId = play_form->winId();
    HWND workerW =  WindowsUtil::GetWorkerW();
\
    SetParent((HWND)viewId,workerW);
    SetWindowPos((HWND)viewId,HWND_TOP,0,0,0,0,WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_RIGHTSCROLLBAR|WS_EX_NOACTIVATE);

    play_form->play();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    event->accept();
}



void MainWindow::dropEvent(QDropEvent *event)
{
    QStringList target_ext = {"mp4","mkv"};
    if(event->mimeData()->hasUrls()){
        for(auto& i:event->mimeData()->urls()){
            QString name = i.fileName();
            QString ext = name.split(".").last().toLower();
            if(target_ext.contains(ext)){
                play_list_view.appendRow(new QStandardItem(i.url()));
                file_urls.append(i.url());
                ui->listView->setModel(&play_list_view);
                qDebug()<<name;
            }
        }
    }

}

void MainWindow::changing_index(int index)
{
    playing_index=index;
//    auto playing_item = ui->listView->model()->index(index,0);
}

void MainWindow::stop_playing()
{
    play_form->stop();
}

void MainWindow::pause_playing()
{
    play_form->pause();
}

void MainWindow::resume_playing()
{
    play_form->resume();
}


void MainWindow::on_playBotton_clicked()
{
    if(file_urls.size()<=0){
        QMessageBox::information(NULL, tr("no play files"), tr("add media file first, accept drag files into windows"),
                                 QMessageBox::Yes , QMessageBox::Yes);
        return;

    }
    play_btn_action();
    emit status_changed(current_playing_status);
}


void MainWindow::on_listView_indexesMoved(const QModelIndexList &indexes)
{

}


void MainWindow::on_muteCheckBox_stateChanged(int arg1)
{

}


void MainWindow::on_pushButton_clicked()
{
    if(play_form!=nullptr){
        play_form->stop();
    }

    play_list_view.clear();
    file_urls.clear();
    emit status_changed(RESET);
}

void MainWindow::slot_status_changed(PlayingStatus status)
{
    switch (status){
    case NO_MEDIA:
        current_playing_status = PlayingStatus::PLAYING;
        play_btn_action = std::bind(&MainWindow::pause_playing,this);
        ui->playBotton->setStyleSheet("background-color: rgb(246,54,92);color: rgb(207,241,227);");
        ui->playBotton->setText(tr("pause"));
        break;
    case PLAYING:
        current_playing_status = PlayingStatus::PAUSE;
        play_btn_action = std::bind(&MainWindow::resume_playing,this);
        ui->playBotton->setStyleSheet("background-color: rgb(245,211,225);color: rgb(67,128,209);");
        ui->playBotton->setText(tr("resume"));
        break;
    case PAUSE:
        current_playing_status = PlayingStatus::PLAYING;
        play_btn_action = std::bind(&MainWindow::pause_playing,this);
        ui->playBotton->setStyleSheet("background-color: rgb(100,112,213);\ncolor: rgb(211,237,231);");
        ui->playBotton->setText(tr("pause"));
    break;
    case RESET:
        current_playing_status = PlayingStatus::NO_MEDIA;
        play_btn_action = std::bind(&MainWindow::wallpayer_play,this);
        ui->playBotton->setStyleSheet("background-color: rgb(100,112,213);\ncolor: rgb(211,237,231);");
        ui->playBotton->setText(tr("Play"));
        break;
    }
}

