#include "adminpanel.h"
#include "ui_adminpanel.h"

AdminPanel::AdminPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPanel)
{
    ui->setupUi(this);
}

AdminPanel::~AdminPanel()
{
    delete ui;

}

void AdminPanel::on_pushButton_clicked()
{
    this->hide();
}