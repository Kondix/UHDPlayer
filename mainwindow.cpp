#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    adminPanel = new AdminPanel(this);
    adminPanel->activateWindow();
    adminPanel->show();
    adminPanel->topLevelWidget();
    adminPanel->showFullScreen();
}

void MainWindow::on_pushButton_clicked()
{
    userPanel = new UserPanel(this);
    userPanel->activateWindow();
    userPanel->show();
    userPanel->topLevelWidget();
    userPanel->showFullScreen();
   //userPanel->();

}
