#ifndef VIDEOPANEL_H
#define VIDEOPANEL_H

#include <QDialog>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include "Controler.h"


namespace Ui {
class VideoPanel;
}

class VideoPanel : public QDialog
{
    Q_OBJECT

public:
    explicit VideoPanel(libvlc_media_player_t* mp, QWidget *parent = 0);
    ~VideoPanel();

private slots:


    void on_video_destroyed();

private:
    Ui::VideoPanel *ui;
};

#endif // VIDEOPANEL_H
