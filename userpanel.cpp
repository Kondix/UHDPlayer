#include "userpanel.h"
#include "ui_userpanel.h"

#include "videopanel.h"
#include "RawDataHandler.h"
#include "Types.h"
#include "ThreadsHandler.h"
#include "ImemOptionsHandler.h"
#include "Callbacks.h"


UserPanel::UserPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPanel)
{
    ui->setupUi(this);
    ui->startWidget->show();
    ui->ratingWidget->hide();
}

UserPanel::~UserPanel()
{
    delete ui;
}

void UserPanel::on_textEdit_textChanged()
{
  //  ui->textEdit->
}

void UserPanel::on_pushButton_clicked()
{
    ui->startWidget->hide();
    ui->ratingWidget->show();
    RawDataHandler rdh(sFileLocation);
    FramesHandler framesHandler;
    ThreadsHandler threadsHandler;

    if (bShouldPreloadCache)
        threadsHandler.PreloadCache(iMovieByteSize, &framesHandler, &rdh);
    else
        threadsHandler.CreateNFramesGetterThreads(2, &rdh, &framesHandler, iMovieByteSize);

    ImemOptionsHandler optionsHandler;
    optionsHandler.AddOption("--no-video-title-show");
    optionsHandler.AddOption("--imem-codec=I420");
    optionsHandler.AddOption("--imem-cookie=test");
    optionsHandler.AddOption("--imem-cat=2");
    optionsHandler.AddOption("--imem-fps=2");
    optionsHandler.AddOption("--verbose=2");

    char imemDataArg[256];
    sprintf(imemDataArg, "--imem-data=%p", &framesHandler);
    optionsHandler.AddOption(imemDataArg);

    char imemGetArg[256];
    sprintf(imemGetArg, "--imem-get=%#p", Callbacks::MyImemGetCallback);
    optionsHandler.AddOption(imemGetArg);

    char imemReleaseArg[256];
    sprintf(imemReleaseArg, "--imem-release=%#p", Callbacks::MyImemReleaseCallback);
    optionsHandler.AddOption(imemReleaseArg);

    char imemWidthArg[256];
    sprintf(imemWidthArg, "--imem-width=%d", iFrameW);
    optionsHandler.AddOption(imemWidthArg);

    char imemHeightArg[256];
    sprintf(imemHeightArg, "--imem-height=%d", iFrameH);
    optionsHandler.AddOption(imemHeightArg);

    char imemChannelsArg[256];
    sprintf(imemChannelsArg, "--imem-channels=%d", iFrameDepth);
    optionsHandler.AddOption(imemChannelsArg);

    Controler controler(optionsHandler.GetOptions());

    VideoPanel* video = new VideoPanel(controler.m_DisplayHandler->m_pMediaPlayer);

}
void UserPanel::on_five_toggled(bool checked)
{
    states[4] = checked;
}

void UserPanel::on_four_toggled(bool checked)
{
    states[3] = checked;
}

void UserPanel::on_three_toggled(bool checked)
{
    states[2] = checked;
}

void UserPanel::on_two_toggled(bool checked)
{
    states[1] = checked;
}

void UserPanel::on_one_toggled(bool checked)
{
    states[0] = checked;
}

void UserPanel::on_proccedButton_clicked()
{
    std::string addToFile = "";
    for(int i = 0; i<5; i++)
    {
        if(states[i])
        {
            addToFile += states[i];
        }
    }
    //procced with next video
}

