#include "userpanel.h"
#include "ui_userpanel.h"

#include "videopanel.h"
#include "ThreadsHandler.h"
#include "ImemOptionsHandler.h"
#include "Callbacks.h"




UserPanel::UserPanel(int w, int h, PlayerConfigurationsHandler* playerConfigurationsHandler, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPanel),
    configurationsHandler(playerConfigurationsHandler),
    height(h),
    width(w)
{
    ui->setupUi(this);

    QDialog::showFullScreen();
    ui->startWidget->show();
    ui->ratingWidget->hide();
}

UserPanel::~UserPanel()
{
    delete ui;
}

void UserPanel::on_textEdit_textChanged()
{
}

void UserPanel::on_pushButton_clicked()
{

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
    bool checked = false;
    for(int i = 0; i < 5; i++)
    {
        if(states[i])
        {
            addToFile += std::to_string(5-i);
            checked = true;
        }
    }
    if(!checked)
        return;
    testsOutputToFileString += addToFile + "\t";
    //procced with next video
    if(iActualPlayedMovie == configurationsHandler->GetMoviesCount())
    {
        WriteToFile();
        delete this;
    }
    else
    {
        ui->one->setAutoExclusive(false);
        ui->two->setAutoExclusive(false);
        ui->three->setAutoExclusive(false);
        ui->four->setAutoExclusive(false);
        ui->five->setAutoExclusive(false);
        ui->one->setChecked(false);
        ui->two->setChecked(false);
        ui->three->setChecked(false);
        ui->four->setChecked(false);
        ui->five->setChecked(false);
        ui->one->setAutoExclusive(true);
        ui->two->setAutoExclusive(true);
        ui->three->setAutoExclusive(true);
        ui->four->setAutoExclusive(true);
        ui->five->setAutoExclusive(true);
        StartPlayback();
    }
}


void UserPanel::on_pushButton_released()
{

    testsOutputToFileString += (ui->textEdit->toPlainText()).toStdString() + "\t";;
    ui->startWidget->hide();
    ui->ratingWidget->show();

    StartPlayback();

}
void UserPanel::StartPlayback()
{

    DisplayHandler::m_bDone = false;
    RawDataHandler rdh(configurationsHandler->GetPath(iActualPlayedMovie));
    FramesHandler framesHandler;
    ThreadsHandler threadsHandler;
    iFPS = configurationsHandler->GetFps(iActualPlayedMovie);

    int movieByteSize = configurationsHandler->GetWidth(iActualPlayedMovie)*configurationsHandler->GetHeight(iActualPlayedMovie)*configurationsHandler->GetFrameDepth(iActualPlayedMovie)/iBitByte;
    iMovieByteSize = movieByteSize;
    if (bShouldPreloadCache)
        threadsHandler.PreloadCache(movieByteSize, &framesHandler, &rdh);
    else
        threadsHandler.CreateNFramesGetterThreads(2, &rdh, &framesHandler, movieByteSize);

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
    sprintf(imemWidthArg, "--imem-width=%d", configurationsHandler->GetWidth(iActualPlayedMovie));
    optionsHandler.AddOption(imemWidthArg);

    char imemHeightArg[256];
    sprintf(imemHeightArg, "--imem-height=%d", configurationsHandler->GetHeight(iActualPlayedMovie));
    optionsHandler.AddOption(imemHeightArg);

    char imemChannelsArg[256];
    sprintf(imemChannelsArg, "--imem-channels=%d", configurationsHandler->GetFrameDepth(iActualPlayedMovie));
    optionsHandler.AddOption(imemChannelsArg);

    std::shared_ptr<Controler> controler(new Controler(optionsHandler.GetOptions()));

    VideoPanel* video = new VideoPanel(width, height, controler);
    video->setGeometry(0, 0, width, height);
    video->showFullScreen();

    controler->Run();
    iActualPlayedMovie++;
    if(iActualPlayedMovie == configurationsHandler->GetMoviesCount())
    {
       ui->proccedButton->setText("Zakończ Test");
    }
    threadsHandler.StopPlayBackThread(video, this);


   // delete video;
   // libvlc_media_player_stop(controler->m_DisplayHandler->m_pMediaPlayer);

}
void UserPanel::WriteToFile()
{
    std::fstream file;
    file.open("wyniki.txt", std::fstream::app);
    file << testsOutputToFileString + "\n";
    file.close();
}


