#include "videopanel.h"
#include "ui_videopanel.h"

VideoPanel::VideoPanel(int w, int h, std::shared_ptr<Controler> controler, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoPanel)
{



    ui->setupUi(this);
    ui->centralWidget->setGeometry(0, 0, w, h);
    ui->centralWidget->showFullScreen();

    ui->video->showFullScreen();
    ui->video->setGeometry(0, 0, w, h);

    libvlc_media_player_t* mp = controler->m_DisplayHandler->m_pMediaPlayer;
    int windid = ui->video->winId();
    libvlc_media_player_set_xwindow (mp, windid);
   // libvlc_media_player_play(mp);

}

VideoPanel::~VideoPanel()
{
    delete ui;
}

void VideoPlayerActivity(Controler* controler){




}

void VideoPanel::on_video_destroyed()
{

}
