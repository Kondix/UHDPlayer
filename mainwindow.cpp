#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::showFullScreen();
    playerConfigurationsHandler = new PlayerConfigurationsHandler();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    adminPanel = new AdminPanel(playerConfigurationsHandler, this);
    adminPanel->activateWindow();
    adminPanel->topLevelWidget();
    adminPanel->showFullScreen();
}

void MainWindow::on_pushButton_clicked()
{
    if(playerConfigurationsHandler->CheckConfiguration())
    {
        userPanel = new UserPanel(playerConfigurationsHandler, this);
        userPanel->activateWindow();
        userPanel->show();
        userPanel->topLevelWidget();
        userPanel->showFullScreen();
    }
   //userPanel->();

}
