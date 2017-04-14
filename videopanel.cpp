#include "videopanel.h"
#include "ui_videopanel.h"

VideoPanel::VideoPanel(libvlc_media_player_t* mp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoPanel)
{
    ui->setupUi(this);
    int windid = ui->video->winId();
    libvlc_media_player_set_xwindow (mp, windid);
    libvlc_media_player_play(mp);

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
