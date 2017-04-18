#include <QtWidgets/QFileDialog>
#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "PlayerConfigurationsHandler.h"

AdminPanel::AdminPanel(PlayerConfigurationsHandler* playerConfigurationsHandler, QWidget *parent) :
    QDialog(parent),
    pCH(playerConfigurationsHandler),
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
    QString file =
            QFileDialog::getOpenFileName(this, tr("Open file"),
                                         QDir::homePath(),
                                         tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;
    delete pCH;
    pCH = new PlayerConfigurationsHandler(file.toStdString());
    this->hide();
}
