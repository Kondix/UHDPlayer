#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include "PlayerConfigurationsHandler.h"


namespace Ui {
class AdminPanel;
}

class AdminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanel(PlayerConfigurationsHandler* playerConfigurationsHandler, QWidget *parent = 0);
    ~AdminPanel();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AdminPanel *ui;
    PlayerConfigurationsHandler* pCH;
};

#endif // ADMINPANEL_H
