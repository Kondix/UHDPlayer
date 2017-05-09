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

    if(configurationsHandler->GetConfig() == 3) {
        mTimer = new QTimer(this);
        mTimer->setSingleShot(true);

        connect(mTimer, SIGNAL(timeout()), SLOT(StartPlayback()));
    }

    QDialog::showFullScreen();
    ui->startWidget->show();
    ui->ratingWidget->hide();
    ui->ratingWidget_2->hide();
    ui->chooseMovieWidget->hide();

    if(configurationsHandler->GetConfig() == 2)
    {
        for (int iMovie = 0; iMovie < configurationsHandler->GetMoviesCount(); ++iMovie) {
            ui->comboBox->addItem(QString::fromStdString(configurationsHandler->GetName(iMovie)) + QString::fromStdString("   ") + QString::fromStdString(std::to_string(configurationsHandler->GetRate(iMovie))));
        }
    }
}

UserPanel::~UserPanel()
{
    delete ui;
}

void UserPanel::on_textEdit_textChanged()
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
    int chosenRate = 0;
    bool checked = false;
    for(int i = 0; i < 5; i++)
    {
        if(states[i] == true)
        {
            chosenRate = 5-i;
            configurationsHandler->SetRate(iActualPlayedMovie, chosenRate);
            checked = true;
        }
    }
    if(!checked)
        return;

    //configurationsHandler->SetRate(iActualPlayedMovie, chosenRate);
    if(configurationsHandler->GetConfig() == 2)
    {
        ui->comboBox->clear();
        for (int iMovie = 0; iMovie < configurationsHandler->GetMoviesCount(); ++iMovie) {
            ui->comboBox->addItem(QString::fromStdString(configurationsHandler->GetName(iMovie)) + QString::fromStdString("   ") + QString::fromStdString(std::to_string(configurationsHandler->GetRate(iMovie))));
        }
    }
    else
    {
        std::string addToFile = std::to_string(configurationsHandler->GetRate(iActualPlayedMovie));
        testsOutputToFileString += addToFile + "\t";
    }
    //procced with next video
    if(configurationsHandler->GetConfig() != 2 && (iActualPlayedMovie+1) == configurationsHandler->GetMoviesCount())
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
        if(configurationsHandler->GetConfig() == 1)
        {
            iActualPlayedMovie++;
            StartPlayback();
        }
        else if(configurationsHandler->GetConfig() == 2)
        {
            ui->ratingWidget->hide();
            ui->chooseMovieWidget->show();
        }
    }
}


void UserPanel::on_pushButton_clicked()
{

    testsOutputToFileString += (ui->textEdit->toPlainText()).toStdString() + "\t";;
    ui->startWidget->hide();

    if(configurationsHandler->GetConfig() == 1) {
        ui->ratingWidget->show();
        StartPlayback();
    }
    else if(configurationsHandler->GetConfig() == 2)
    {
        ui->chooseMovieWidget->show();
    }
    else if(configurationsHandler->GetConfig() == 3)
    {
       // ui->ratingWidget_2->show();
        StartPlayback();
    }
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
    //std::string codec = "--imem-codec=" + configurationsHandler->GetCodec(iActualPlayedMovie);
    optionsHandler.AddOption("--imem-codec=I420" );
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
    if(configurationsHandler->GetConfig() == 1)
    {
        if ((iActualPlayedMovie+1) == configurationsHandler->GetMoviesCount()) {
            ui->proccedButton->setText("Zakończ Test");
        }
    }
    if(configurationsHandler->GetConfig() == 3)
    {
        if(iActualPlayedMovie %2 == 1)
        {
            ui->ratingWidget_2->show();
            iActualPlayedMovie++;
        }
        else
        {
            iActualPlayedMovie++;
            ui->ratingWidget_2->hide();
            mTimer->start(1000);
        }
      //  mTimer->setSingleShot(true);

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



void UserPanel::on_proccedButton_2_clicked()
{
    ui->ratingWidget->show();
    ui->chooseMovieWidget->hide();
    StartPlayback();
}

void UserPanel::on_proccedButton_3_clicked()
{
    for (int iMovie = 0; iMovie < configurationsHandler->GetMoviesCount(); ++iMovie)
    {
        testsOutputToFileString += std::to_string(configurationsHandler->GetRate(iMovie)) + "\t";
    }
    WriteToFile();
    delete this;
}

void UserPanel::on_comboBox_activated(const QString &arg1)
{

}

void UserPanel::on_comboBox_activated(int index)
{
    iActualPlayedMovie = index;
}

void UserPanel::on_comboBox_currentIndexChanged(int index)
{

}

void UserPanel::on_comboBox_highlighted(int index)
{

}

void UserPanel::on_one_2_toggled(bool checked)
{
    states2[0] = checked;
}

void UserPanel::on_two_2_toggled(bool checked)
{
    states2[1] = checked;
}

void UserPanel::on_three_2_toggled(bool checked)
{
    states2[2] = checked;
}

void UserPanel::on_four_2_toggled(bool checked)
{
    states2[3] = checked;
}

void UserPanel::on_five_2_toggled(bool checked)
{
    states2[4] = checked;
}

void UserPanel::on_six_2_toggled(bool checked)
{
    states2[5] = checked;
}

void UserPanel::on_seven_2_toggled(bool checked)
{
    states2[6] = checked;
}


void UserPanel::on_proccedButton_4_clicked()
{
    std::string addToFile = "";
    int chosenRate = 0;
    bool checked = false;
    for(int i = 0; i < 7; i++)
    {
        if(states2[i])
        {
            // += std::to_string(7-i);
            chosenRate = 7-i;
            checked = true;
        }
    }
    if(!checked)
        return;
    addToFile = std::to_string(chosenRate - 4);
    testsOutputToFileString += addToFile + "\t";

    //procced with next video
    if(iActualPlayedMovie == configurationsHandler->GetMoviesCount())
    {
        WriteToFile();
        delete this;
    }
    else
    {
        ui->one_2->setAutoExclusive(false);
        ui->two_2->setAutoExclusive(false);
        ui->three_2->setAutoExclusive(false);
        ui->four_2->setAutoExclusive(false);
        ui->five_2->setAutoExclusive(false);
        ui->six_2->setAutoExclusive(false);
        ui->seven_2->setAutoExclusive(false);

        ui->one_2->setChecked(false);
        ui->two_2->setChecked(false);
        ui->three_2->setChecked(false);
        ui->four_2->setChecked(false);
        ui->five_2->setChecked(false);
        ui->six_2->setChecked(false);
        ui->seven_2->setChecked(false);

        ui->one_2->setAutoExclusive(true);
        ui->two_2->setAutoExclusive(true);
        ui->three_2->setAutoExclusive(true);
        ui->four_2->setAutoExclusive(true);
        ui->five_2->setAutoExclusive(true);
        ui->six_2->setAutoExclusive(true);
        ui->seven_2->setAutoExclusive(true);

       StartPlayback();

    }
}
