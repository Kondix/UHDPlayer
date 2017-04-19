#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int w, int h, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    width(w),
    height(h)
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
    adminPanel->show();
    adminPanel->activateWindow();
    adminPanel->topLevelWidget();
}

void MainWindow::on_pushButton_clicked()
{
    if(playerConfigurationsHandler->CheckConfiguration())
    {
        userPanel = new UserPanel(width, height,playerConfigurationsHandler, this);
        userPanel->setGeometry(0,0, width, height);
        userPanel->activateWindow();
        userPanel->show();
        userPanel->topLevelWidget();
        userPanel->showFullScreen();
    }
   //userPanel->();

}
